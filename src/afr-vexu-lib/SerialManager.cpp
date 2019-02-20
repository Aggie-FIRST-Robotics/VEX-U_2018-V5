
#include "SerialManager.h"

SerialManager* serial_manager;

SerialManager::SerialManager (const scheduled_update_t& update_period, error_t* result) : scheduled(update_period, result) {

	stream_in 		= fopen("/ser/sinp", "rb");
	stream_out 		= fopen("/ser/sout", "wb");

	serctl(SERCTL_DEACTIVATE, (void*)0x74756f73);
	serctl(SERCTL_DEACTIVATE, (void*)0x706e6973);
	serctl(SERCTL_DISABLE_COBS, NULL);

	read_buffer = new RingBuffer(4096);

	read.read_state = W;

	read_params.stream = stream_in;
	read_params.buffer = read_buffer;

	serial_read_task = pros::c::task_create(handle_serial_read, (void*)&read_params, TASK_PRIORITY_DEFAULT,
                             TASK_STACK_DEPTH_DEFAULT, "handle_serial_read");

}

SerialManager::~SerialManager () {
	pros::c::task_delete(serial_read_task);
	fclose(stream_in);
	fclose(stream_out);
}

bool SerialManager::enqueue_write (uint8_t dest, uint8_t addr, short data) {

	Packet::Frame curr( V5_ID, addr, data );
	if( dest == ODROID_ID ){
		odroid_queue.push(curr);
	}
	else if( dest == ARDUINO_ID ){
		arduino_queue.push(curr);
	}
	else{
		return false;
	}
	return true;
}

error_t update() {
	if(steady_clock_n::now() >= next_update_){
        next_update_ = steady_clock_n::now() + update_period_;
        return update_private(std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1>>>(
                steady_clock_n::now() - next_update_ + update_period_).count());
    }
    return SUCCESS;
}

void SerialManager::send_buffer (uint8_t dest) {

	if( dest == ODROID_ID ? odroid_queue.empty() : arduino_queue.empty() )
		return;

	Packet::Header packet_header(dest, static_cast<uint8_t>( dest == ODROID_ID ? odroid_queue.size() : arduino_queue.size() ));

	fputc((char)(packet_header.header[0]), stream_out);
	fputc((char)(packet_header.header[1]), stream_out);
	fputc((char)(packet_header.header[2]), stream_out);
	fputc((char)(packet_header.header[3]), stream_out);
	fputc((char)(packet_header.header[4]), stream_out);
	fputc((char)(packet_header.header[5]), stream_out);
	fputc((char)(packet_header.header[6]), stream_out);

	if ( dest == ODROID_ID ) {
		while(!odroid_queue.empty()){
			fputc((char)(odroid_queue.front().frame[0]), stream_out);
			fputc((char)(odroid_queue.front().frame[1]), stream_out);
			fputc((char)(odroid_queue.front().frame[2]), stream_out);
			fputc((char)(odroid_queue.front().frame[3]), stream_out);
			odroid_queue.pop();
		}
	}
	else {
		while(!arduino_queue.empty()){
			fputc((char)(arduino_queue.front().frame[0]), stream_out);
			fputc((char)(arduino_queue.front().frame[1]), stream_out);
			fputc((char)(arduino_queue.front().frame[2]), stream_out);
			fputc((char)(arduino_queue.front().frame[3]), stream_out);
			odroid_queue.pop();
		}
	}
	for(int i = 0; i < 8; i++)
		fputc((char)0, stream_out);
	fflush(stream_out);
}

void SerialManager::handle_read() {
	receive_buffer();
	sort_read_queue();
}

void SerialManager::receive_buffer () {
    char c;
	while(read_buffer->size() > 0)
	{	
		read_buffer->pop(c);
		switch(read.read_state)
		{
			case W :
				if( c == 'W' ) {
					read.read_state = H;
				}
		    	break;
			case H :	
				if( c == 'H' )
					read.read_state = O_1;
				else
					read.read_state = W;
		    	break;
	    	case O_1 :
	    		if( c == 'O' )
					read.read_state = O_2;
				else
					read.read_state = W;
		    	break;
	      	case O_2 :
	      		if( c == 'O')
					read.read_state = P;
				else
					read.read_state = W;
		    	break;
	    	case P : 		
		    	if( c == 'P' )
					read.read_state = H_Dest;
				else
					read.read_state = W;
		    	break;
	    	case H_Dest :
    			if( static_cast<uint8_t>(c) == V5_ID ){
					read.read_state = H_Len;
	    		}
	    		else
	    			read.read_state = W;
		    	break;
	    	case H_Len :
	    		if( static_cast<uint8_t>(c) > 0 ){
					read.rem = static_cast<uint8_t>(c);
					read.read_state = F_1;
	    		}
				else
					read.read_state = W;
		    	break;
	    	case F_1 :		      	
		      	read.frame[0] = c;
		      	read.read_state = F_2;
		    	break;
	    	case F_2 : 	
		      	read.frame[1] = c;
		      	read.read_state = F_3;
		    	break;
	    	case F_3 :
		      	read.frame[2] = c;
		      	read.read_state = F_4;
		    	break;
	    	case F_4 : {
		      	read.frame[3] = c;

		      	Packet::Frame next(read.frame);
		      	
		      	read_queue.push(next);

		      	read.rem--;
		      	if(read.rem > 0)
		      		read.read_state = F_1;
		      	else{
		      		read.read_state = W;
		      	}
		    	break;
		    }
		   	default :
		   		break;
		}
	}
}

void SerialManager::sort_read_queue () {
	while(!read_queue.empty()) {
		switch (read_queue.front().source){
			case ODROID_ID:
				odroid_table.update(read_queue.front());
				read_queue.pop();
				break;
			case ARDUINO_ID:
				arduino_table.update(read_queue.front());
				read_queue.pop();
				break;
			default:
				read_queue.pop();
		}
	}
}

void handle_serial_read(void* param) {
	task_params* data = static_cast<task_params*>(param);
	char c;
	while(true){
		c = fgetc(data->stream);
		data->buffer->push(c);
	}
}
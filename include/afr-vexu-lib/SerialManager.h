#ifndef SERIAL_MANAGER_H
#define SERIAL_MANAGER_H

#include <queue>

#include "afr-vexu-lib/comms/Packet.h"
#include "afr-vexu-lib/comms/RingBuffer.h"
#include "afr-vexu-lib/comms/DataTable.h"
#include "afr-vexu-lib/scheduled.h"
#include "afr-vexu-lib/nameable.h"

namespace AFR::VexU {

	//Device IDs
	constexpr static uint8_t V5_ID 			= 1;
	constexpr static uint8_t ODROID_ID 		= 2;
	constexpr static uint8_t ARDUINO_ID 	= 3;

	//V5 writes to the serial stream at this rate
	//in milliseconds
	constexpr static uint8_t WRITE_PERIOD 	= 5;

	//Read state machine states
	enum Read_Buffer_States { W, H, O_1, O_2, P, H_Dest, H_Len, F_1, F_2, F_3, F_4, Exit };

	//Maintains read state machine state and data
	struct BufferInfo {
		uint8_t 			rem = 0;
		char 				frame [FRAME_SIZE];
		Read_Buffer_States 	read_state;
	};

	//Holds parameters taken by the write task
	struct task_params {
		FILE* 			stream;
		RingBuffer* 	buffer;
	};

	//Manages buffers for serial communication
	class SerialManager : public scheduled, public nameable{
			
		public:

			//Public tables for data coming out of the serial stream
			DataTable 				odroid_table;
			DataTable				arduino_table;

			//Do not call constructor, serial manager is instanstiated
			//as a global pointer
			SerialManager (const scheduled_update_t& update_period);

			~SerialManager ();

			//Puts data into the write queue
			// '1' -> v5
			// '2' -> odroid
			// '3' -> arduino
			// addr [0-63]
			// returns false if destination is not 1 or 2
			bool enqueue_write (uint8_t dest, uint8_t addr, short data);

			//Sends the write queue into the write
			//buffer and manages the read buffer updates

		private:

			FILE* 						stream_in;
			FILE* 						stream_out;

			RingBuffer* 				read_buffer;

			std::queue <Packet::Frame> 	odroid_queue;
			std::queue <Packet::Frame> 	arduino_queue;
			std::queue <Packet::Frame> 	read_queue;

			BufferInfo read;

			pros::task_t 				serial_read_task;

			task_params 				read_params;

			void send_buffer (uint8_t destination);
			void handle_read ();
			void receive_buffer ();
			void sort_read_queue ();

			void update_private(const double& delta_seconds);

	};

	//Task function that updates the data table at a rate of 100 Hz
	void handle_serial_read (void* param);

}

#endif
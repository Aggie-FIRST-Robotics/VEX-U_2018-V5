
#include "afr-vexu-lib/comms/RingBuffer.h"

namespace AFR::VexU {

	RingBuffer::RingBuffer() {
		//cout << "Constructing Ring buffer" << endl;
		mutex = pros::c::mutex_create();
		pros::c::mutex_take(mutex, 10);
		_capacity = 1024;
		buf = new char [_capacity];
		head = 0;
		tail = 0;
		_size = 0;
		//cout << "Finished Buffer" << endl;
		pros::c::mutex_give(mutex);
	}
	RingBuffer::RingBuffer (unsigned int capacity) {
		//cout << "Constructing Ring buffer of size " << capacity << endl;
		mutex = pros::c::mutex_create();
		pros::c::mutex_take(mutex, 10);
		_capacity = capacity;
		buf = new char [_capacity];
		head = 0;
		tail = 0;
		_size = 0;
		//cout << "Finished Buffer" << endl;
		pros::c::mutex_give(mutex);
	}

	RingBuffer::~RingBuffer() {
		delete buf;
	}

	bool RingBuffer::push(char input) {
		//cout << "push char lock\t";
		pros::c::mutex_take(mutex, 10);
		if(full()){
			//cout << "push char unlock" << endl;
			pros::c::mutex_give(mutex);
			return false;
		}

		buf [tail] = input;

		tail = (tail+1) % _capacity;
		_size += 1;
		pros::c::mutex_give(mutex);
		//cout << "buffer size: " << size() << endl;
		return true;
	}

	bool RingBuffer::pop (char& c) {
		//cout << "pop char lock\t";
		pros::c::mutex_take(mutex, 10);
		if(empty()){
			//cout << "pop char unlock" << endl;
			pros::c::mutex_give(mutex);
			return false;
		}

		c = buf[head];
		head = (head + 1) % _capacity;

		_size--;

		pros::c::mutex_give(mutex);
		//cout << "buffer size: " << size() << endl;
		return true;
	}

	bool RingBuffer::front(char& c) {
		pros::c::mutex_take(mutex, 10);
		if(empty()){
			//cout << "pop char unlock" << endl;
			pros::c::mutex_give(mutex);
			return false;
		}

		c = buf[head];
		pros::c::mutex_give(mutex);
		return true;	
	}

	bool RingBuffer::empty() {
		return size() == 0;
	}

	bool RingBuffer::full() {
		return size() == capacity();
	}

	unsigned int RingBuffer::size() {
		return _size;
	}

	unsigned int RingBuffer::capacity() {
		return _capacity;
	}

	void RingBuffer::flush() {
		pros::c::mutex_take(mutex, 10);
		head = 0;
		tail = 0;
		_size = 0;
		pros::c::mutex_give(mutex);
	}

}
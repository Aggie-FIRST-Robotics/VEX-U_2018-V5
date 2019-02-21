#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "main.h"

namespace AFR::VexU {

	//Data container
	class RingBuffer {

		public:
			RingBuffer();

			RingBuffer(unsigned int capacity);

			~RingBuffer();

			//Insert into the buffer
			bool push(char input);

			//Remove frome the buffer
			bool pop(char&);

			//sets the input to the front value of the buffer
			//does not pop
			bool front(char&);

			//Returns true if the buffer is empty
			bool empty();

			//Retruns true if the buffer is full
			bool full();

			//Returns the number of elements in the buffer
			unsigned int size();

			//Returns the capacity of the buffer
			unsigned int capacity();

			//Clears the buffer
			void flush();

		private:

			unsigned int 	_capacity;
			unsigned int 	head;
			unsigned int 	tail;
			unsigned int 	_size;
			char* 			buf;

			pros::mutex_t mutex;
	};

}

#endif
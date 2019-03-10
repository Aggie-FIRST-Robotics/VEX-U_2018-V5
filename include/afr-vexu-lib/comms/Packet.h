#ifndef PACKET_H
#define PACKET_H

#include <iostream>

namespace AFR::VexU {

	//Number of bytes that each respective object takes in the stream
	constexpr static uint8_t FRAME_SIZE 	= 4;
	constexpr static uint8_t HEADER_SIZE 	= 7;

	namespace Packet {
		//Contains a frame along with its information
		class Frame {
		public:
			uint8_t 	source;
			uint8_t 	var_address;
			short 		data;
			char 		checksum;
			char 		frame [FRAME_SIZE];

			//Constructor creates a frame with given information
			Frame (uint8_t src, uint8_t addr, short data);

			//Constructor copies a frame from a character buffer
			Frame (char* buf);

			//Calculates an 8-bit checksum of the frame
			static char CRC8 (const char* data, int length);
			
			//Checks if the checksum in the frame is equal
			//to a calculated checksum of the frame
			bool is_valid ();

		};

		//The header of a packet
		class Header {
		public:
			uint8_t		 	num_frames;
			uint8_t 		destination;
			char 			header [HEADER_SIZE];

			//Constructor creates a packet header with given information
			Header (uint8_t dest, uint8_t length);
			Header (char* buf);

		};
	}

}

#endif
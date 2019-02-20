
#include "Packet.h"

Packet::Frame::Frame (uint8_t src, uint8_t addr, short data) {
	this->source 		= src;
	this->var_address 	= addr;
	this->data 			= data;

	frame [0] 			= static_cast<char>(((addr & 0x3F) << 2) | (src& 0x03));

	frame[1] = static_cast<char>(data & 0xFF);
	frame[2] = static_cast<char>(data >> 8);

	this->checksum 		= CRC8(frame,3);

	frame [3] 			= checksum;
}

Packet::Frame::Frame (char* buf) {
	this->source 		= static_cast<uint8_t>(buf [0] & 3);
	this->var_address 	= static_cast<uint8_t>(buf [0] >> 2);
	this->data			= static_cast<short>(buf[2]);
	this->data			= (data << 8) | static_cast<short>(buf[1]);
	this->checksum		= CRC8(buf,3);
	this->frame [0]		= buf [0];
	this->frame [1]		= buf [1];
	this->frame [2]		= buf [2];
	this->frame [3]		= buf [3];
}

char Packet::Frame::CRC8 (const char* data, int length) 
{
   char crc = 0x00;
   char extract;
   char sum;
   for(int i=0;i<length;i++)
   {
      extract = *data;
      for (char tempI = 8; tempI; tempI--) 
      {
         sum = (crc ^ extract) & 0x01;
         crc >>= 1;
         if (sum)
            crc ^= 0x8C;
         extract >>= 1;
      }
      data++;
   }
   return crc;
}

bool Packet::Frame::is_valid (void) {
	return checksum == frame [3];
}

Packet::Header::Header (uint8_t dest, uint8_t length) {
	this->num_frames 	= length;
	this->destination 	= dest;

	this->header [0]	= 'W';
	this->header [1]	= 'H';
	this->header [2]	= 'O';
	this->header [3]	= 'O';
	this->header [4]	= 'P';
	*reinterpret_cast<uint8_t*>	(&header [5]) = dest;
	*reinterpret_cast<uint8_t*>	(&header [6]) = length;
}

Packet::Header::Header (char* buf) {
	this->header [0]	= 'W';
	this->header [1]	= 'H';
	this->header [2]	= 'O';
	this->header [3]	= 'O';
	this->header [4]	= 'P';
	this->header [5]	= *reinterpret_cast<uint8_t*>(buf);
	this->header [6]	= *reinterpret_cast<uint8_t*>(buf + 1);

	this->destination 	= *reinterpret_cast<uint8_t*>(buf);
	this->num_frames	= *reinterpret_cast<uint8_t*>(buf + 1);
}
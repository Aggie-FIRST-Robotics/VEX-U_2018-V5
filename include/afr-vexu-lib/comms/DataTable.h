#ifndef DATA_TABLE_H
#define DATA_TABLE_H

#include "Packet.h"
#include "main.h"

using namespace std;

//pretty self explanatory
constexpr static uint8_t TABLE_SIZE = 64;

//Maintians the data read from the serial line
class DataTable {

public:

	//Data tables already instantiated in serial manager
	DataTable ();

	~DataTable ();

	//Updates a variable at an address
	//Returns false if address is not valid
	bool update(Packet::Frame a);

	//Ages all variables by a given period of time
	void age_by(unsigned long period);

	//Returns a constant reference to a variable
	short read(uint8_t addr);

	//Returns a constant reference to the age of a variable
	unsigned long card(uint8_t addr);

private:
	pros::mutex_t mutex;
	short 			variables [TABLE_SIZE];
	unsigned long 	age [TABLE_SIZE];

};

#endif

#include "DataTable.h"

DataTable::DataTable() {
	mutex = pros::c::mutex_create();
	pros::c::mutex_take(mutex, 10);
	for(int i = 0; i < TABLE_SIZE; i++) {
		variables[i] = 0;
		age[i] = 0;
	}
	pros::c::mutex_give(mutex);
}

DataTable::~DataTable () {
	
}

bool DataTable::update(Packet::Frame a) {
	pros::c::mutex_take(mutex, 10);
	if(!a.is_valid() ||  a.var_address >= TABLE_SIZE || a.var_address < 0 ){
		return false;
	}
	
	variables 	[a.var_address] = a.data;
	age 		[a.var_address] = 0;
	pros::c::mutex_give(mutex);
	return true;
}

void DataTable::age_by(unsigned long period) {
	pros::c::mutex_take(mutex, 10);
	for(uint8_t i = 0; i < TABLE_SIZE; i++)
		age [i] += period;
	pros::c::mutex_give(mutex);
}

short DataTable::read (uint8_t addr) {
	return variables[addr];
}

unsigned long DataTable::card (uint8_t addr) {
	return age[addr];
}
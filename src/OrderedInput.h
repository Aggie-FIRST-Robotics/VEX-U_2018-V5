#include "Readable.h"

class OrderedInput {
	public:
		OrderedInput(unsigned int order, Readable input);
		unsigned int getOrder();
		Readable& getInput();
	private:
		Readable _input;
		unsigned int _order;
};
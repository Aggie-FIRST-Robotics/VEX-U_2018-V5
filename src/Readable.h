#include "Scheduled.h"

template <typename T> class Readable : Scheduled {
	public:
		Readable();
		Readable(T initial_value);
		T& get_value();
		
	protected:
		virtual void update() = 0;;
	private:
		T curr_value;
};
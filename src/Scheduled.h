#include <chrono>

class Scheduled {
	public:
		Scheduled(unsigned int update_period);
		virtual void update() = 0;
	private:
		update_private(double delta_seconds);
		std::chrono::time_point next_update; //PLACEHOLDER TYPE
};
#include <unordered_map>
#include <string>
#include <any>
#include "State.h"
#include "defines.h"

class StateController {
	public:
        StateController();
		result_t updateCurrentState();
		result_t updateActions();
		State& getState(std::string id);
		Commandable& getCommandable(std::string id);
	private:
		std::unordered_map<std::string, State>& state_map;
		std::unordered_map<std::string, Commandable>& commandable_map;
		State& current_state;
};
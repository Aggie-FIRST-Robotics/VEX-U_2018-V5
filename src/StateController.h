#include <unordered_map>
#include <string>
#include "State.h"

class StateController {
	public:
		void updateCurrentState();
		void updateActions();
		State& getState(std::string id);
		Commandable& getCommandable(std::string id);
	private:
		std::unordered_map<std::string, State> states;
		std::unordered_map<std::string, Commandable<std::any>> commandables;
		State* currentState;
};
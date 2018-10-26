#include <unordered_map>
#include <string>
#include "OrderedInput.h"
#include "StateController.h"

class SubsystemController {
	public:
		SubsystemController();
		void updateInputs();
		void updateStates();
		void updateActions();
		OrderedInput& getInput(std::string id);
		StateController& getStateMachine(std::string id);
	private:
		std::unordered_map<std::string, OrderedInput> input_map;
		std::unordered_map<std::string, OrderedInput> state_map;
};
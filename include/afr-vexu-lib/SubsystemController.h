#include <unordered_map>
#include <string>
#include "OrderedInput.h"
#include "StateController.h"
#include "defines.h"

class SubsystemController {
	public:
		SubsystemController();
		result_t updateInputs();
		result_t updateStates();
		result_t updateActions();
		OrderedInput& getInput(std::string id);
		StateController& getStateMachine(std::string id);
	private:
		std::unordered_map<std::string, OrderedInput> &input_map;
        std::vector<Readable> ordered_inputs;
		std::unordered_map<std::string, StateController> &state_map;
};
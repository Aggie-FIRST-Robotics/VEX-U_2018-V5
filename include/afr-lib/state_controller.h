#ifndef VEX_U_2018_V5_STATE_CONTROLLER_H
#define VEX_U_2018_V5_STATE_CONTROLLER_H

#include <unordered_map>
#include <string>
#include <iostream>

#include "afr-lib/state.h"
#include "afr-lib/defines.h"
#include "afr-lib/nameable.h"
#include "afr-lib/scheduled.h"


namespace AFR::VexU{
    template<class MetaType>
    class state_controller : public scheduled {
    private:
        std::vector<state*> states_;
        state* current_state_;
        MetaType metadata_;
        bool maintain;

        /**
         * Calls update current state
         * @param delta_seconds from scheduled
         * @return error_t value if error encountered
         */
        void update_private(double delta_seconds) override{
            update_current_state();
        }

    public:
        /**
         * Creates a state controller
         * @param update_period passed to scheduled
         * @param states contains all states by string
         * @param commandables the map of commandables by string
         * @param initial_state the initial state by string within state_map
         * @param result error_t value if error encountered
         */
        state_controller(const scheduled_update_t& update_period, const MetaType& initial_metadata, const std::string& name) :
                nameable(name), scheduled(update_period, name), current_state_(nullptr), metadata_(initial_metadata), maintain(false){}

        void add_state(state* new_state) {
            states_.push_back(new_state);
        }
        
        void clear_states() {
            states_.clear();
        }

        void set_state(state* next_state){
            std::cout << "Set state called for" << get_name() << ": going to state " << next_state->get_name() << std::endl;
            if(next_state == nullptr){
                throw std::runtime_error{"Cannot have nullptr for state in " + get_name()};
            }
            if(current_state_ != nullptr){
                current_state_->on_state_exit(next_state);
            }
            maintain = false;
            state* prev_state = current_state_;
            current_state_ = next_state;
            current_state_->on_state_entry(prev_state);
        }

        void maintain_state(state* next_state) {
            std::cout << "Maintain state called for" << get_name() << ": going to state " << next_state->get_name() << std::endl;
            if(next_state == nullptr){
                throw std::runtime_error{"Cannot have nullptr for state in " + get_name()};
            }
            if(current_state_ != nullptr){
                std::cout << "Previous state was null" << std::endl;
                current_state_->on_state_exit(next_state);
            }
            maintain = true;
            state* prev_state = current_state_;
            current_state_ = next_state;
            std::cout << "Running the on state entry" << std::endl;
            current_state_->on_state_entry(prev_state);
        }

        void update_current_state(){
            if(current_state_ != nullptr){
                if(!maintain){
                    state* next = current_state_->get_next_state();
                    if(next != nullptr){
                        set_state(next);
                    }
                }
            }
            else{
                throw std::runtime_error{"Current state for " + get_name() + " is nullptr while updating current state"};
            }
        }

        std::vector<state*>& get_states(){
            return states_;
        }

        state* get_current_state(){
            return current_state_;
        }
        
        std::string get_current_state_name() {
            return current_state_->get_name();
        }

        MetaType& metadata(){
            return metadata_;
        }
    };
}

#endif //VEX_U_2018_V5_STATE_CONTROLLER_H
#ifndef VEX_U_2018_V5_STATE_CONTROLLER_H
#define VEX_U_2018_V5_STATE_CONTROLLER_H

#include <unordered_map>
#include <string>

#include "state.h"
#include "afr-lib/defines.h"
#include "afr-lib/nameable.h"
#include "afr-lib/scheduled.h"
#include "commandable.h"

namespace AFR::VexU{
    /**
     * Represents a state machine within a subsystem
     */
    template <class T>
    class state_controller : public scheduled {
    private:
        std::vector<state*> states_;
        std::vector<commandable<T>*> commandables_;
        state* current_state_;
        T metadata_;
        /**
         * Calls update current state
         * @param delta_seconds from scheduled
         * @return error_t value if error encountered
         */
        void update_private(const double& delta_seconds) override{
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
        state_controller(const scheduled_update_t& update_period, state* initial_state,
                                           const T& initial_metadata, const std::string& name) :
                scheduled(update_period, name),
                 current_state_(initial_state),
                 metadata_(initial_metadata){
            if(current_state_ != nullptr){
                current_state_->on_state_entry();
            }
        }

        void add_state(state* new_state) {
            states_.push_back(new_state);
        }
        
        void add_commandable(commandable<T>* new_commandable) {
            commandables_.push_back(new_commandable);
        }
        
        void clear_states() {
            states_.clear();
        }
        
        void clear_commandables() {
            commandables_.clear();
        }

        void set_state(state* next_state){
            current_state_->on_state_exit();
            current_state_ = next_state;
            current_state_->on_state_entry();      
        }

        void update_current_state(){
            if(current_state_ != nullptr){
                if(current_state_ != current_state_->get_next_state()){
                    set_state(current_state_->get_next_state());
                }          
            }
            else{
                throw std::runtime_error{"Current state for " + get_name() + " is nullptr while updating current state"};
            }
        }

        state* get_state(const std::string& name){
            for(auto state : states_){
                if(state->get_name() == name){
                    return state;
                }
            }
            return nullptr;
        }

        commandable<T>* get_commandable(const std::string& name){
            for(auto commandable : commandables_){
                if(commandable->get_name() == name){
                    return commandable;
                }
            }
            return nullptr;
        }

        std::vector<state*>& get_states(){
            return states_;
        }

        std::vector<commandable<T>*>& get_commandables(){
            return commandables_;
        }

        state* get_current_state(){
            return current_state_;
        }
        
        std::string get_current_state_name() {
            return current_state_->get_name();
        }
        
        T* metadata() {
            return &metadata_;
        }
    };
}

#endif //VEX_U_2018_V5_STATE_CONTROLLER_H
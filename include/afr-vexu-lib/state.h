//
// Created by HP on 10/26/2018.
//

#ifndef UNTITLED_STATE_H
#define UNTITLED_STATE_H

class state()

{
private:
public:
state(double &update_period_ms);

~

state() {}

void update_actions();

void on_state_entry();

action get_action(identifier_e &identifier);

vector <transition> *get_transitions();
}

class transition()

{
private:
state *next_state;
function<bool()> condition_function;
public:
transition(function<bool()>
condition_function,
state *next_state
);
~

transition() {}

bool change_state();

state *get_next_state();
}

#endif //UNTITLED_STATE_H

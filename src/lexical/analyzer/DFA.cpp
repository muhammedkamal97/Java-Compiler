//
// Created by khaled on 3/22/19.
//


#include "DFA.h"

DFA::DFA(int **transition_array, pair<int, int> transition_size, map<char, int> *input_map, int initial_state,
         set<int> acceptance_states)
         : transition_array(transition_array), transition_size(transition_size), input_map(input_map),
         acceptance_states(acceptance_states), initial_state(initial_state) {
    reset();
}

void DFA::move(char inp) {
    if (is_error()) throw "Error";
    int input_int = input_map->at(inp);
    current_state = transition_array[current_state][input_int];

    if (acceptance_states.count(current_state))
        last_acceptance_state = current_state;
}

bool DFA::is_error() {
    if (current_state < 0)
        return true;
    return false;
}

void DFA::reset() {
    current_state = initial_state;
    last_acceptance_state = -1;
}




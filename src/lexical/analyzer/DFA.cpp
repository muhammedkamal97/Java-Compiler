//
// Created by khaled on 3/22/19.
//


#include "DFA.h"

DFA::DFA(int **transition_array, MetaData meta_data, map<char, int> *input_map, set<int> acceptance_states)
        : transition_array(transition_array), meta_data(meta_data), input_map(input_map),
         acceptance_states(acceptance_states) {
    reset();
}

void DFA::move(char inp) {
    if (is_error()) throw "Error";
    if (input_map->find(inp) != input_map->end()) {
        int input_int = input_map->at(inp);
        current_state = transition_array[current_state][input_int];
    }
    else {
        current_state = meta_data.invalid_state_index;
    }
}

bool DFA::is_error() {
    if (current_state == meta_data.invalid_state_index)
        return true;
    return false;
}

void DFA::reset() {
    current_state = meta_data.init_state_index;
}

bool DFA::is_in_acceptance_state() {
    return acceptance_states.find(current_state) != acceptance_states.end();
}





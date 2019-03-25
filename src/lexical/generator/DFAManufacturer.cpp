//
// Created by mario_hunter on 3/23/19.
//

#include "DFAManufacturer.h"

DFAManufacturer::DFAManufacturer(vector<set<int> *> *nfa_transition_array) {
    transition_array = new vector<int *>();
    this->nfa = nfa_transition_array;
    this->input_number = 3; //TODO replace with variable from struct
    init_closures_array(nfa_transition_array->size());
}

void
DFAManufacturer::init_closures_array(unsigned long size) {
    epsilon_closures = new set<int> *[size];
    is_epsilon_cached = new bool[size];
    for (int i = 0; i < size; i++) {
        is_epsilon_cached[i] = false;
    }
}

/**
 * initially, e-closure(s0) is the only state in Dstates and it is unmarked;
 * while there is an unmarked state T in Dstates do begin
 *  mark T;
 *  for each input symbol a do begin
 *      U = e-closure(move(T,a));
 *      if U is not in Dstates then
 *          add U as an unmarked state to Dstates;
 *      Dtran[T,a] = U
 *  end
 * end
 */
void
DFAManufacturer::generate_dfa() {
    generate_epsilon_closures();
    int index = 0;
    int states_size = 1;
    map<int, dfa_state *> states_by_index;
    map<string, dfa_state *> states_by_originator;


    //initially the unmarked states contain the e-closure of the init state
    auto init_ep = this->nfa->at(0)[input_number - 1];
    auto init_label = make_label(&init_ep);
    auto init_ep_closure = new set(init_ep);
    init_ep_closure->merge(*epsilon_closure_of(&init_ep));
    auto init_state = dfa_state{init_label, init_ep_closure, 0};

    create_new_state(&states_by_index, &states_by_originator, 0, &init_state);

    while (index < states_size) {
        //process each unprocessed inserted state in the array
        auto curr_state = states_by_index.at(index);

        for (int j = 0; j < input_number - 1; j++) {
            auto new_state = next_state(new set<int>(*curr_state->complete_states), j);
            auto v = states_by_originator.find(new_state->originator_states);

            if (v != states_by_originator.end()) {
                //this state is already in the table, use its index in the transition array
                this->transition_array->at(index)[j] = v->second->index;
                continue;
            };

            //this state could not be found in the current table, thus we insert a new state
            new_state->index = states_size;
            create_new_state(&states_by_index, &states_by_originator, states_size, new_state);
            this->transition_array->at(index)[j] = states_size;
            states_size++;
        }
        index++;
    }
}

void
DFAManufacturer::create_new_state(map<int, dfa_state *> *states_by_index,
                                  map<string, dfa_state *> *states_by_originator, int index, dfa_state *new_state) {

    this->transition_array->emplace_back(new int[input_number - 1]);
    states_by_index->insert(pair<int, dfa_state *>(index, new_state));
    states_by_originator->insert(pair<string, dfa_state *>(new_state->originator_states, new_state));
}

dfa_state *
DFAManufacturer::next_state(set<int> *states, int input) {
    auto originator = new set<int>();
    auto complete_set = new set<int>();

    auto it = states->begin();
    while (it != states->end()) {
        auto next_states = this->nfa->at(*it)[input]; //get next states of this input for the current state
        auto epsilon_closure = epsilon_closure_of(&next_states);
        originator->merge(set<int>(next_states)); // the originator of the new state is the set of all the next states without their e-closure
        complete_set->merge(set<int>(next_states));
        complete_set->merge(set<int>(*epsilon_closure));
        it++;
    }
    auto label = make_label(originator); //label for fast indexing
    auto *ds = new dfa_state{label, complete_set}; //create the struct, the index is put later during the execution
    return ds;
}

/**
 * The label is used to create a string representation of the states. Thus, using the label the map can be indexed in logarithmic time
 * and searched for all the needed data.
 * The label is the concatination of the states names (the index) interleaved with dots to resolve any ambiguity (e.g. 101 could be 10 1 or 101).
 * The final form is [s0].[s1]. .. .[si]. .. [sn]. where [si] represents the number of the state (1,2,3 ..etc)
 * @param states
 * @return
 */
string
DFAManufacturer::make_label(set<int> *states) {
    auto it = states->begin();
    string label;
    while (it != states->end()) {
        label += to_string(*it);
        it++;
    }
    label += '.';
    return label;
}


set<int> *
DFAManufacturer::epsilon_closure_of(set<int> *states) {
    auto it = states->begin();
    auto closure = new set<int>();
    while (it != states->end()) {
        closure->merge(set<int>(*epsilon_closures[*it]));
        it++;
    }
    return closure;
}

set<int> **
DFAManufacturer::getEpsilon_closures() const {
    return epsilon_closures;
}

void
DFAManufacturer::generate_epsilon_closures() {
    for (int i = 0; i < nfa->size(); i++) {
        generate_epsilon_closure(i);
    }
}

/**
 * DFS-like algorithm. It visits each state only once to create its closure by going to its neighbors - its direct closure, recursively.
 * This stops when one state can't go any further or when reaching a cycle. The algorithm then traces back merging the closures along the way
 * and saving them in a table for caching. It can be viewed as a top-down dynamic programming approach.
 *
 * @param state
 * @return
 */
set<int> *
DFAManufacturer::generate_epsilon_closure(int state) {
    if (is_epsilon_cached[state]) return new set<int>(*epsilon_closures[state]);
    is_epsilon_cached[state] = true;
    set<int> *row = nfa->at(state);
    auto ep_closure = (row[input_number - 1]);
    auto *result = new set<int>(ep_closure);

    // Creating a iterator pointing to start of set
    auto it = ep_closure.begin();
    // Iterate till the end of set
    while (it != ep_closure.end()) {
        result->merge(*generate_epsilon_closure(*it));
        it++;
    }
    epsilon_closures[state] = new set<int>(*result);
    return result;
}







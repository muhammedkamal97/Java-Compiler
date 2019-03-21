//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_DFASIMULATOR_H
#define PROJECT_DFASIMULATOR_H

#include <map>
#include "DFA.h"

using namespace std;

enum operation_mode {
    NO_ERROR, RECOVERY
};
class DFASimulator {

private:
    DFA *automata;
    int last_acceptance_state;
    int index_at_last_accepted_input;

public:


    DFASimulator(int **transition_array, pair<int, int> transition_size, map<char, int> *input_map, fstream *input);

    void process_next_token();

    void is_error();


};


#endif //PROJECT_DFASIMULATOR_H

//
// Created by mostafa on 25/03/19.
//

#ifndef COMPILER_METADATA_H
#define COMPILER_METADATA_H

#include <utility>

using namespace std;


struct MetaData {
    pair <int, int > DFA_size;
    int invalid_state_index;
    int init_state_index;
    int epsilon_index;
    int number_of_inputs;

};
#endif //COMPILER_METADATA_H

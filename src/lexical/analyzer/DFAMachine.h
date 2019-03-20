//
// Created by mario_hunter on 3/20/19.
//

#ifndef PROJECT_DFAMACHINE_H
#define PROJECT_DFAMACHINE_H

#include <map>
#include <set>

using namespace std;

class DFAMachine {
public:
    DFAMachine(int **transition_map, pair<int, int> transition_size, map<char, int> *input_map,
               set<int> acceptance_states);

    void move(char inp);

    int get_state();

    bool is_error();

    int last_accepted_state();

    void reset();


};


#endif //PROJECT_DFAMACHINE_H

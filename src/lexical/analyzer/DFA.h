//
// Created by mario_hunter on 3/20/19.
//

#ifndef PROJECT_DFA_H
#define PROJECT_DFA_H

#include <map>
#include <set>

using namespace std;

class DFA {
public:
    DFA(int **transition_array, pair<int, int> transition_size, map<char, int> *input_map,
               set<int> acceptance_states);

    void move(char inp);

    int get_state();

    bool is_error();

    int last_accepted_state();

    void reset();


};


#endif //PROJECT_DFA_H

//
// Created by mario_hunter on 3/20/19.
//

#ifndef PROJECT_DFA_H
#define PROJECT_DFA_H

#include <map>
#include <set>
#include <lexical/MetaData.h>

using namespace std;

class DFA {
private:
    int **transition_array;
    MetaData meta_data;
    map<char, int> *input_map;
    set<int> acceptance_states;
    int current_state;
public:
    DFA(int **transition_array, MetaData meta_data, map<char, int> *input_map, set<int> acceptance_states);

    void move(char inp);
    int get_current_state() {
        return current_state;
    }
    bool is_error();
    bool is_in_acceptance_state();
    void reset();

};


#endif //PROJECT_DFA_H

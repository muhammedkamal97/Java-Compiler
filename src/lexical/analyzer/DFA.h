//
// Created by mario_hunter on 3/20/19.
//

#ifndef PROJECT_DFA_H
#define PROJECT_DFA_H

#include <map>
#include <set>

using namespace std;

class DFA {
private:
    int **transition_array;
    pair<int, int> transition_size;
    map<char, int> *input_map;
    set<int> acceptance_states;
    int initial_state;
    int current_state;
    int last_acceptance_state;
public:
    DFA(int **transition_array, pair<int, int> transition_size, map<char, int> *input_map, int initial_state,
               set<int> acceptance_states);

    void move(char inp);

    int get_current_state() {
        return current_state;
    }

    bool is_error();

    int get_last_accepted_state() {
        return last_acceptance_state;
    }

    void reset();

};


#endif //PROJECT_DFA_H

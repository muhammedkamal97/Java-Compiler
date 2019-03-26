//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_DFAMANUFACTURER_H
#define PROJECT_DFAMANUFACTURER_H

#include<map>
#include <vector>
#include <string>
#include <set>
#include <lexical/MetaData.h>

using namespace std;
struct dfa_state {
    string originator_states;
    set<int> *complete_states;
    int index;
};

class DFAManufacturer {
private:
    vector<int *> *transition_array;
    set<int> **epsilon_closures;
    bool *is_epsilon_cached;
    vector<set<int> *> *nfa;
    int input_number;
    MetaData *meta_data;

    void generate_epsilon_closures();

    set<int> *generate_epsilon_closure(int state);

    void init_closures_array(unsigned long i);

    set<int> *epsilon_closure_of(set<int> *states);

    dfa_state *next_state(set<int> *states, int input);

    string make_label(set<int> *states);

    void create_new_state(map<int, dfa_state *> *states_by_index, map<string,
            dfa_state *> *states_by_originator, int index, dfa_state *new_state);

public:
    explicit DFAManufacturer(vector<set<int> *> *nfa_transition_array, MetaData *meta_data);

    void generate_dfa();

    vector<int *> *getTransition_array() const {
        return transition_array;
    }

    set<int> **getEpsilon_closures() const;


};


#endif //PROJECT_DFAMANUFACTURER_H

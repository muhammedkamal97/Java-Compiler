//
// Created by Muhammed on 3/24/2019.
//

#ifndef COMPILER_NFA_H
#define COMPILER_NFA_H

#include <bits/stdc++.h>
#include "NFAstate.h"
#include <lexical/MetaData.h>

using namespace std;

class NFA {
private:
    int state_number;

    void label_nfa(NFAstate *state);

public:
    set<NFAstate *> accepted;
    set<NFAstate *> all_states;
    NFAstate *starting;
    NFAstate *ending;
    vector<vector<set<int>>> transition_array;
    map<int, pair<int, int>> *token_indexes;
    MetaData *metadata;

    NFA(NFAstate *starting, NFAstate *ending);

    NFA(char c);

    NFA(string word);
    NFA *copy();
    vector<vector<set<int>>> get_trasition_array(map<string, pair<int, int>> *tokens_priorities_map);

    static NFA *concatinate(NFA *s1, NFA *s2);

    static NFA *union_(NFA *s1, NFA *s2);

    static NFA *kleene_clouser(NFA *s);

    static NFA *positive_clouser(NFA *s);

    static NFA *range(NFA *n1, NFA *n2);

    static NFA *compine(vector<NFA *> patterns);

    set<int> *accepted_states_indices;
};


#endif //COMPILER_NFA_H

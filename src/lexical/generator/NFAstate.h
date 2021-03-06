//
// Created by Muhammed on 3/24/2019.
//

#ifndef COMPILER_NFASTATE_H
#define COMPILER_NFASTATE_H

#include <bits/stdc++.h>
#include <tokens/TokenType.h>


using namespace std;

class NFAstate {
public:
    int id;
    bool accept;
    int label;

    string accepted_pattern;
    TokenType *accepted_token_type;
    vector<pair<string,NFAstate*>> transition;
    static int count;

    NFAstate(bool accept);

    void make_transition(NFAstate *s,string input);
};


#endif //COMPILER_NFASTATE_H

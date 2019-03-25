//
// Created by Muhammed on 3/24/2019.
//

#include "NFAstate.h"

int NFAstate::count = 1;

NFAstate::NFAstate(bool accept) {
    this->id = count++;
    this->accept = accept;
    this->label = -1;
}

void NFAstate::make_transition(NFAstate *s,string input) {
    this->transition.push_back(make_pair(input,s));
}


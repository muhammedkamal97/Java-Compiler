//
// Created by mario_hunter on 4/19/19.
//

#include "PDTManufacturer.h"
#include "First.h"
#include "Follow.h"

PDTManufacturer::PDTManufacturer(map<string, vector<string> *> *productions,vector<string> * terminals) {
    this->productions = productions;
    this->first = compute_first(this->productions);
    this->follow = compute_follow(this->follow);
    this->terminals = terminals;
}

string **
PDTManufacturer::getPdt() const {
    return pdt;
}

map<string, int> *
PDTManufacturer::getNon_terminal_map() const {
    return non_terminal_map;
}

map<string, int> *
PDTManufacturer::getTerminal_map() const {
    return terminal_map;
}



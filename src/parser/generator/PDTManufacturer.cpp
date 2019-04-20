//
// Created by mario_hunter on 4/19/19.
//

#include "PDTManufacturer.h"
#include "First.h"
#include "Follow.h"

PDTManufacturer::PDTManufacturer(ProductionRules *productions,vector<string> * terminals) {
    this->productions = productions;
    this->first = compute_first(this->productions);
    this->follow = compute_follow(this->productions);
    this->terminals = terminals;
}

Production ***
PDTManufacturer::getPdt() const {
    return pdt;
}

unordered_map<string, int> *
PDTManufacturer::getNon_terminal_map() const {
    return non_terminal_map;
}

unordered_map<string, int> *
PDTManufacturer::getTerminal_map() const {
    return terminal_map;
}


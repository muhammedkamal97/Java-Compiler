//
// Created by mario_hunter on 4/19/19.
//

#include "parser/Production.h"
#include "PDTManufacturer.h"
#include "First.h"
#include "Follow.h"
#include <iostream>


using namespace std;
PDTManufacturer::PDTManufacturer(ProductionRules *production_rules, vector<string> *terminals) {
    this->production_rules = production_rules;
    this->first = compute_first(this->production_rules);
    this->follow = compute_follow(this->production_rules, this->first);
    this->terminals = clearTerminals(terminals);
    vector<string> temp(production_rules->non_terminals->begin(),
                        production_rules->non_terminals->end());
    this->non_terminals = temp;
    this->non_terminal_map = new unordered_map<string, int>();
    this->terminal_map = new unordered_map<string, int>();
    createPDT();
    printPDT();
}

vector<string> *PDTManufacturer::clearTerminals(vector<string> *terminals){
    set<string> temp;
    vector<string> *new_terminals = new vector<string>();
    for(int i = 0; i < terminals->size(); i++){
        temp.insert((*terminals)[i]);
    }
    set<string>::iterator it = temp.begin();
    while (it != temp.end()){
        new_terminals->push_back(*it);
        it++;
    }
    return new_terminals;
}


void
PDTManufacturer::createPDT() {
    constructNonTerminalMap();
    constructTerminalMap();
    initPDTTable();
    fillPDT();
}

void
PDTManufacturer::constructNonTerminalMap() {
    for (int i = 0; i < non_terminals.size(); i++) {
        non_terminal_map->insert({non_terminals[i], i});
    }
}

void
PDTManufacturer::constructTerminalMap() {
    for (int i = 0; i < terminals->size(); i++) {
        terminal_map->insert({(*terminals)[i], i});
    }
}

void
PDTManufacturer::initPDTTable() {
    int rows = production_rules->non_terminals->size();
    int cols = terminals->size() + 1;
    pdt = new Production **[rows];
    for (int i = 0; i < rows; i++) {
        pdt[i] = new Production *[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pdt[i][j] = NULL;
        }
    }
}


void
PDTManufacturer::fillPDT() {
    for (int i = 0; i < non_terminals.size(); i++) {
        int non_terminal_index = production_rules->production_rules_indexes->at(non_terminals[i]);
        fillPDTRow(i, non_terminal_index);
    }
}


void
PDTManufacturer::fillPDTRow(int row, int non_terminal_index) {
    bool is_follow_slots_filled = false;
    vector<vector<GrammarSymbol *> *> *single_production = production_rules->production_rules[non_terminal_index]->productions;
    string non_terminal = production_rules->production_rules[non_terminal_index]->name->value;
    for (int j = 0; j < single_production->size(); j++) {
        string symbol = (*single_production)[j]->at(0)->value;
        bool is_terminal = terminal_map->find(symbol) != terminal_map->end();
        if (is_terminal) {
            Production *production = getProduction(non_terminal_index, j, single_production, false, false);
            pdt[row][terminal_map->find(symbol)->second] = production;
        } else {
            addFirstTerminals(symbol, row, j, non_terminal_index, single_production);
        }
        if (!is_terminal && (containsEpsilon(first->find(symbol)->second))) {
            is_follow_slots_filled = true;
            addFollowTerminals(non_terminal, row, non_terminal_index, j, single_production, false);
        }
    }
    if (production_rules->production_rules[non_terminal_index]->has_epsilon) {
        addFollowTerminals(non_terminal, row, non_terminal_index, 0, single_production, true);
        is_follow_slots_filled = true;
    }
    if (!is_follow_slots_filled) {
        addSyncSlots(non_terminal, row, non_terminal_index, 0, single_production);
    }
}


void
PDTManufacturer::addSyncSlots(string symbol, int row, int non_terminal_index, int grammer_symbol_vector_index,
                              vector<vector<GrammarSymbol *> *> *single_production) {
    vector<string> *follow_terminals = follow->find(symbol)->second;
    for (int k = 0; k < follow_terminals->size(); k++) {
        Production *production = getProduction(non_terminal_index, grammer_symbol_vector_index, single_production,
                                               false, true);
        int i = row, j;
        if ((*follow_terminals)[k].compare("$") == 0) {
            j = terminal_map->size();
//            pdt[row][terminal_map->size()] = production;
        } else {
            j = terminal_map->find((*follow_terminals)[k])->second;
//            pdt[row][terminal_map->find((*follow_terminals)[k])->second] = production;
        }

        if (pdt[i][j] != nullptr) return;
        pdt[i][j] = production;
    }
}

Production *
PDTManufacturer::getProduction(int non_terminal_index, int grammer_symbol_vector_index,
                               vector<vector<GrammarSymbol *> *> *productions, bool epsilon, bool is_sync) {
    Production *old_production = (production_rules->production_rules[non_terminal_index]);
    Production *new_production = cloneProduction(old_production);
    if (epsilon) {
        new_production->has_epsilon = true;

    } else if (is_sync) {
        new_production->is_sync = true;
        new_production->has_epsilon = false;

    } else {
        vector<vector<GrammarSymbol *> *> *production_vector = new vector<vector<GrammarSymbol *> *>();
        vector<GrammarSymbol *> *grammerSymbols = (*productions)[grammer_symbol_vector_index];
        production_vector->push_back(grammerSymbols);
        new_production->productions = production_vector;
        new_production->has_epsilon = false;
    }
    return new_production;
}

Production *
PDTManufacturer::cloneProduction(Production *old_production) {
    //    Production(GrammarSymbol *name, bool has_epsilon, bool is_start_production) : name(name), has_epsilon(has_epsilon),
    //                                                                                  is_start_production(
    //                                                                                          is_start_production) {
    Production *new_production = new Production(old_production->name, old_production->has_epsilon,
                                                old_production->is_start_production);

    new_production->is_sync = old_production->is_sync;
    return new_production;
}

void
PDTManufacturer::addFirstTerminals(string symbol, int row, int grammer_symbol_vector_index, int non_terminal_index,
                                   vector<vector<GrammarSymbol *> *> *single_production) {
    vector<string> *first_terminals = first->find(symbol)->second;
    int k;
    if (containsEpsilon(first->find(symbol)->second)) {
        k = 1;
    } else {
        k = 0;
    }
    for (; k < first_terminals->size(); k++) {
        Production *production = getProduction(non_terminal_index, grammer_symbol_vector_index, single_production,
                                               false, false);
        int j = terminal_map->find((*first_terminals)[k])->second;
        if (pdt[row][j] != nullptr) throw std::runtime_error(std::string("This grammmar is not LL(1)"));
        pdt[row][j] = production;
    }
}

void
PDTManufacturer::addFollowTerminals(string symbol, int row, int non_terminal_index, int grammer_symbol_vector_index,
                                    vector<vector<GrammarSymbol *> *> *single_production, bool epsilon) {
    vector<string> *follow_terminals = follow->find(symbol)->second;

    for (int k = 0; k < follow_terminals->size(); k++) {
        int j;
        Production *production;
        if ((*follow_terminals)[k].compare("$") == 0) {
            production = getProduction(non_terminal_index, grammer_symbol_vector_index, single_production, epsilon,
                                       false);
//            pdt[row][terminals->size()] = production;
            j = terminals->size();
        } else {
            production = getProduction(non_terminal_index, grammer_symbol_vector_index, single_production, epsilon,
                                       false);
//            pdt[row][terminal_map->find((*follow_terminals)[k])->second] = production;
            j = terminal_map->find((*follow_terminals)[k])->second;
        }

        if (pdt[row][j] != nullptr) throw std::runtime_error(std::string("This grammmar is not LL(1)"));
        pdt[row][j] = production;
    }

}


bool
PDTManufacturer::containsEpsilon(vector<string> *first_terminals) {
    if ((*first_terminals)[0].compare("\\L") == 0) {
        return true;
    }
    return false;
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

void PDTManufacturer::printPDT(){
    unordered_map<int, string> reversed_terminals = getReversedMap(terminal_map);
    for (int i = 0; i < reversed_terminals.size(); i++) {
        cout<< "        " << reversed_terminals.at(i);
    }
    cout << "\n";
    unordered_map<int, string> reversed_non_terminals = getReversedMap(non_terminal_map);
    for(int i = 0; i < non_terminal_map->size(); i++){
        cout<<reversed_non_terminals.at(i)<<"       ";
        for(int j = 0; j <= terminal_map->size(); j++){
            if(pdt[i][j] == NULL){
                cout<<"error  ";
            } else {
                if (pdt[i][j]->has_epsilon) {
                    cout << "epsilon    ";
                } else if(pdt[i][j]->is_sync){
                    cout << "sync   ";
                }else {
                    for (int k = 0; k < (*pdt[i][j]->productions)[0]->size(); k++) {
                        cout << (*pdt[i][j]->productions)[0]->at(k)->value;
                    }

                }
            }
            cout << "      ";
        }
        cout <<"\n";
    }
}

unordered_map<int, string> PDTManufacturer::getReversedMap(unordered_map<string, int> *normal_map){
    unordered_map<int, string> new_map;
    for (unordered_map<string, int>::iterator itr = normal_map->begin(); itr != normal_map->end(); ++itr) {
        new_map.insert({itr->second, itr->first});
    }
    return new_map;
}

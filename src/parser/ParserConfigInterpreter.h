//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_PARSERCONFIGINTERPRETER_H
#define PROJECT_PARSERCONFIGINTERPRETER_H


#include <fstream>
#include <boost/algorithm/string.hpp>
#include <regex>
#include <vector>
#include <map>
#include "ProductionRules.h"

using namespace std;

class ParserConfigInterpreter {
private:
    fstream* config;
    vector<Production*>* productions_vector;
    ProductionRules* rules;

    static const regex prod_regex;
    static const regex terminal_regex;
    static const char* epsilon_string;

    void parse_prouction(string line);
public:
    ParserConfigInterpreter(std::fstream *config, bool cacheable = false);

    void generate_production_rules();

    ProductionRules *get_production_rules();

    vector<string> *
    getTerminals();
};


#endif //PROJECT_PARSERCONFIGINTERPRETER_H

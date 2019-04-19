//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_PARSERCONFIGINTERPRETER_H
#define PROJECT_PARSERCONFIGINTERPRETER_H


#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>

using namespace std;

class ParserConfigInterpreter {
private:
    fstream* config;
public:
    ParserConfigInterpreter(std::fstream *config, bool cacheable = false);

    void generate_production_rules();

    map<string, vector<string> *> *get_production_rules();

    vector<string> *
    getTerminals();
};


#endif //PROJECT_PARSERCONFIGINTERPRETER_H

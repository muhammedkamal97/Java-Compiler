//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_LEXICALCONFIGINTERPRETER_H
#define PROJECT_LEXICALCONFIGINTERPRETER_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class LexicalConfigInterpreter {
private:
    map<string, vector<string>> *lexical_rules;
public:
    LexicalConfigInterpreter(fstream *config, bool cacheable = false);

    void generate_rules_map();

    map<string, vector<string>> *get_rules();

};


#endif //PROJECT_LEXICALCONFIGINTERPRETER_H

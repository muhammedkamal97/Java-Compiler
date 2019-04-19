//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_PREDICTIVEPARSER_H
#define PROJECT_PREDICTIVEPARSER_H


#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>
#include <tokens/TokenType.h>
#include <stack>
#include <tokens/Token.h>

using namespace std;

class PredictiveParser {
private:
    string **pdt;
    map<string, int> *non_terminal_map;
    map<string, int> *terminal_map;
    stack<string> * productions_stack;


public:
    PredictiveParser(string **pdt, map<string, int> *non_terminal_map, map<string, int> *terminal_map);

    string next_production(Token* tkn);

    bool has_next_production();

};


#endif //PROJECT_PREDICTIVEPARSER_H

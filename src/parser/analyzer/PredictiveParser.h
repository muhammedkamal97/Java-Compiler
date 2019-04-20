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
#include <parser/Production.h>
#include <queue>
#include "parser/errors/ErrorRecoverer.h"
#include "errors/ErrorLogger.h"

using namespace std;

class PredictiveParser {
private:
    Production ***pdt;
    unordered_map<string, int> *non_terminal_map;
    unordered_map<string, int> *terminal_map;
    stack<GrammarSymbol *> *productions_stack;
    queue<Production *> * parse_tree;
    bool successfully_terminated = false;
    GrammarSymbol* start_symbol;
    ErrorLogger *error_logger;
    ErrorRecoverer *error_recoverer;

    void error(Token *tkn, Production *prod);

public:
    PredictiveParser(Production ***pdt, unordered_map<string, int> *non_terminal_map,
                     unordered_map<string, int> *terminal_map,GrammarSymbol* start_symbol);

    vector<Production *>*next_production(Token *tkn);

    bool has_next_production();

    void
    push_to_stack(Production *production);

    bool has_successfully_terminated() const;



};


#endif //PROJECT_PREDICTIVEPARSER_H

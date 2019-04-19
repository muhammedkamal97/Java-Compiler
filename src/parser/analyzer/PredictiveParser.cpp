//
// Created by mario_hunter on 4/19/19.
//

#include "PredictiveParser.h"

PredictiveParser::PredictiveParser(string **pdt, map<string, int> *non_terminal_map, map<string, int> *terminal_map)
        : pdt(pdt), non_terminal_map(non_terminal_map), terminal_map(terminal_map) {}

bool
PredictiveParser::has_next_production() {
    //TODO
    return false;
}

string
PredictiveParser::next_production(Token *tkn) {
    //TODO
    return std::__cxx11::string();
}

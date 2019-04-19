//
// Created by mario_hunter on 4/19/19.
//

#include "ParserConfigInterpreter.h"
#include "ProductionRules.h"

vector<string> *
ParserConfigInterpreter::getTerminals() {
    return nullptr;
}

ParserConfigInterpreter::ParserConfigInterpreter(std::fstream *config, bool cacheable) {
    this->config = config;

}

void
ParserConfigInterpreter::generate_production_rules() {
    //TODO

}

ProductionRules *
ParserConfigInterpreter::get_production_rules() {
    //TODO
    return nullptr;
}

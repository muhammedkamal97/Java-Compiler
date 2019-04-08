//
// Created by mario_hunter on 4/8/19.
//

#include <lexical/generator/NFAManufacturer.h>
#include <lexical/generator/DFAManufacturer.h>
#include <lexical/generator/DFAMinimizer.h>
#include "LexicalComponent.h"
#include "LexicalConfigInterpreter.h"

LexicalComponent::LexicalComponent(std::fstream *config, std::fstream *input) : Component(config, input) {
    this->config = config;
    this->input = input;
    build_component();
}


void *
LexicalComponent::process_next_input() {
    return nullptr;
}

fstream *
LexicalComponent::get_write_stream() {
    return this->out_stream;
}

void
LexicalComponent::notify() {

}

void
LexicalComponent::build_component() {
    auto interpreter = new LexicalConfigInterpreter(config);
    interpreter->generate_rules_map();
    auto rules = interpreter->get_rules();

    //TODO get rules to NFA module

    auto nfa = new NFAManufacturer(*rules);
    auto dfa = new DFAManufacturer(nfa->getTranisition_array());

}

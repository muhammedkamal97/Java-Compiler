//
// Created by mario_hunter on 4/19/19.
//

#include <tokens/Token.h>
#include <parser/generator/LL1GrammarManufacturer.h>
#include <parser/generator/PDTManufacturer.h>
#include <parser/analyzer/PredictiveParser.h>
#include "ParserComponent.h"
#include "ParserConfigInterpreter.h"

ParserComponent::ParserComponent(fstream *config, fstream *input)
        : Component(config, input) {
    this->config = config;
    build_component();

}

void
ParserComponent::build_component() {
    auto interpreter = new ParserConfigInterpreter(this->config);
    interpreter->generate_production_rules();
    vector<string>* terminals = interpreter->getTerminals();

    auto rules = interpreter->get_production_rules();
    auto start_symbol = interpreter->get_start_symbol();

    auto ll1_manufacturer = new LL1GrammarManufacturer(rules);
    rules = ll1_manufacturer->getProductions();

    auto pdt_manufacturer = new PDTManufacturer(rules, terminals);
    auto non_terminal_map = pdt_manufacturer->getNon_terminal_map();
    auto terminal_map = pdt_manufacturer->getTerminal_map();
    auto pdt = pdt_manufacturer->getPdt();

    pdt_parser = new PredictiveParser(pdt, non_terminal_map, terminal_map, start_symbol);

}

void *
ParserComponent::process_next_input() {
    auto tkn = (Token*) this->work_slave->process_next_input();
    if(tkn == nullptr) return tkn;
    if(pdt_parser->has_next_production()){
        auto prods = pdt_parser->next_production(tkn);
        return prods;
    }
    return nullptr;
}

fstream *
ParserComponent::get_write_stream() {
    return this->out_stream;
}

void
ParserComponent::notify(void *notification) {


}

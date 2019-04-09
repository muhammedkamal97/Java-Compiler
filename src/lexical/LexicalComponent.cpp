//
// Created by mario_hunter on 4/8/19.
//

#include <lexical/generator/NFAManufacturer.h>
#include <lexical/generator/DFAManufacturer.h>
#include <lexical/generator/DFAMinimizer.h>
#include <lexical/analyzer/DFA.h>
#include <lexical/analyzer/Tokenizer.h>
#include "LexicalComponent.h"
#include "LexicalConfigInterpreter.h"

LexicalComponent::LexicalComponent(std::fstream *config, std::fstream *input, SimpleSymbolTable *table) : Component(
        config, input) {
    this->table = table;
    this->config = config;
    this->input = input;
    build_component();
}


void *
LexicalComponent::process_next_input() {
    if (dfa->has_next_token()) {
        Token *tkn = (Token *) dfa->next_token();
        if (tkn->type->has_symbol_table_entry) {
            table->table->insert(make_pair(tkn->lexeme, nullptr));
        }
        return tkn;
    }
    return nullptr;
}

fstream *
LexicalComponent::get_write_stream() {
    return this->out_stream;
}

void
LexicalComponent::notify(void *notification) {

}

void
LexicalComponent::build_component() {
    auto interpreter = new LexicalConfigInterpreter(config);
    interpreter->generate_rules_map();

    auto nfa = new NFAManufacturer(*(interpreter->get_regex_map()),
                                   *(interpreter->get_regex_map()),
                                   *(interpreter->get_keywords()),
                                   *(interpreter->get_punctations()));

    auto **tokens = new TokenType *[nfa->tokens_vec->size()];
    for (int i = 0; i < nfa->tokens_vec->size(); i++) {
        tokens[i] = nfa->tokens_vec->at(i);
    };

    auto dfa_manufacturer = new DFAManufacturer(nfa->getTranisition_array(), nfa->nfa->token_indexes,
                                                nfa->nfa->metadata);
    dfa_manufacturer->generate_dfa();


    auto minimizer = new DFAMinimizer(*dfa_manufacturer->getTransition_array(),
                                      *dfa_manufacturer->getAccepted_states(),
                                      *dfa_manufacturer->getTokens_indexes(),
                                      tokens,
                                      *dfa_manufacturer->getMeta_data());

    minimizer->Minimize();
    std::map<int, int> acceptance_state_token = (minimizer->getToken_indexes());
    map<char, int> input_map;
    for (int i = 0; i < 256; i++) input_map[i] = i;
    dfa = new Tokenizer(minimizer->getTransition_array(), minimizer->getMeta_data(), &input_map,
                        minimizer->getAcceptanceStates(), &acceptance_state_token,
                        minimizer->getToken_types(), input);


}

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
    vector<pair<string, vector<string>>> regex_map = *(interpreter->get_regex_map());
    auto regdef_map = (interpreter->get_regdef_map());
    auto keywords = (interpreter->get_keywords());
    auto punctuations = (interpreter->get_punctations());
    auto nfa = new NFAManufacturer(regex_map, *regdef_map, *keywords, *punctuations);

    vector<set<int> *> *transition_array  = new vector<set<int>*>;
    for (int i = 0; i < nfa->transition_table.size(); i++) {
        set<int> *sets = new set<int>[256];
        for (int j = 0; j < 256; j++) {
            set<int> curr = nfa->transition_table[i][j];
            sets[j] = curr;
        }
        transition_array->push_back(sets);
    }

    auto **tokens = new TokenType *[nfa->tokens_vec->size()];
    for (int i = 0; i < nfa->tokens_vec->size(); i++) {
        tokens[i] = nfa->tokens_vec->at(i);
    };

    auto dfa_manufacturer = new DFAManufacturer(transition_array, nfa->nfa->token_indexes,
                                                nfa->nfa->metadata);
    dfa_manufacturer->generate_dfa();
//DFAMinimizer(vector<int *> input_transition_array, set<int> acceptance_states, , TokenType **token_type, MetaData meta_data){

    vector<int *> *input_transition_array = dfa_manufacturer->getTransition_array();
    set<int>* acceptance_states = dfa_manufacturer->getAccepted_states();
    map<int, int> *tokens_indexes = dfa_manufacturer->getTokens_indexes();
    TokenType **token_type = tokens;
    MetaData *meta_data = dfa_manufacturer->getMeta_data();
    auto minimizer = new DFAMinimizer(input_transition_array,
                                      acceptance_states,
                                      tokens_indexes,
                                      token_type,
                                      meta_data);


//    cout << "==============" << endl;
//    for (int i = 0; i < dfa_manufacturer->getMeta_data()->DFA_size.first; i++) {
//        cout << i << ": ";
//        for (int j = 0; j < dfa_manufacturer->getMeta_data()->DFA_size.second; j++) {
//            cout << dfa_manufacturer->getTransition_array()->at(i)[j] << " ";
//        }
//        cout << endl;
//    }
//    cout << "==============" << endl;

    minimizer->Minimize();

//    cout << "====== Minimized ========" << endl;
//    for (int i = 0; i < minimizer->getMeta_data().DFA_size.first; i++) {
//        cout << i << ": ";
//        for (int j = 0; j < minimizer->getMeta_data().DFA_size.second; j++) {
//            cout << minimizer->getTransition_array()[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << "==============" << endl;

    std::map<int, int> acceptance_state_token = (minimizer->getToken_indexes());
    map<char, int> input_map;
    for (int i = 0; i < 256; i++) input_map[i] = i;
    Tokenizer::static_acceptance_state_token = &acceptance_state_token;
    dfa = new Tokenizer(minimizer->getTransition_array(), minimizer->getMeta_data(), &input_map,
                        minimizer->getAcceptanceStates(), &acceptance_state_token,
                        minimizer->getToken_types(), input);



}

//
// Created by khaled on 3/26/19.
//

#include "Tokenizer.h"
#include "Token.h"

const set<char> Tokenizer::delimiters = {' ', '\n', '\t'};

Tokenizer::Tokenizer(int **transition_array, MetaData meta_data, map<char, int> *input_map, set<int> acceptance_states,
         map<int, int> *acceptance_state_token, TokenType** token_types, fstream *input) : meta_data(meta_data),
         acceptance_state_token(acceptance_state_token), token_types(token_types), input(input) {
    automata = new DFA(transition_array, meta_data, input_map, acceptance_states);
    current_pos = 0;
    current_line = 0;
    last_accepted_pos = 0;
    last_accepted_pos = -1;
    tokens_buffer[0] = process_following_token();
}

/**
 * Returns the buffered token and triggers processing of the following token
 */
Token* Tokenizer::next_token() {
    if (has_next_token()) {
        tokens_buffer[1] = tokens_buffer[0];
        tokens_buffer[0] = process_following_token();
    }

    return tokens_buffer[1];
}

Token* Tokenizer::process_following_token() {
    automata->reset();
    char c;
    streamoff start_pos = current_pos;
    string token_str = "";
    Token* token;

    while (delimiters.count(input->peek())) {
        input->get(c);
        if (c == '\n') {
            current_line++;
            last_newline_pos = input->tellg();
        }
    }
    while (input->get(c) && !delimiters.count(c) && !automata->is_error()) {
        automata->move(c);
        token_str += c;
        current_pos = input->tellg();
        if (automata->is_in_acceptance_state()) {
            last_acceptance_state = automata->get_current_state();
            last_accepted_pos = input->tellg();
        }
    }

    if (c == '\n') {
        current_line++;
        last_newline_pos = input->tellg();
    }

    if (input->peek() == EOF && start_pos == current_pos) {
        return nullptr;
    }

    if (automata->is_in_acceptance_state()) {

        int token_type_index = acceptance_state_token->at(automata->get_current_state());
        TokenType* token_type = token_types[token_type_index];
        token = new Token(token_type, token_str);
    }
    else if (last_acceptance_state != -1) {     // Passed through an acceptance state at some point
        streamoff rewind_offset = current_pos - last_accepted_pos;
        token_str = token_str.substr(0, token_str.length() - rewind_offset);

        int token_type_index = acceptance_state_token->at(last_acceptance_state);
        TokenType* token_type = token_types[token_type_index];
        token = new Token(token_type, token_str);

        rewind_stream(last_accepted_pos);
    }
    else {
        // Initiate error recovery
    }

    return token;
}

void Tokenizer::rewind_stream(streamoff offset) {
    input->clear();
    current_pos = offset;
    input->seekg(current_pos);
}

bool Tokenizer::has_next_token() {
    return tokens_buffer[0] != nullptr;
}

bool Tokenizer::is_error() {

}

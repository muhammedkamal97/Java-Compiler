//
// Created by khaled on 3/26/19.
//

#include "Tokenizer.h"
#include <iostream>
#include <lexical/errors/ErrorRecoverer.h>

const set<char> Tokenizer::delimiters = {' ', '\n', '\t'};

Tokenizer::Tokenizer(int **transition_array, MetaData meta_data, map<char, int> *input_map, set<int> acceptance_states,
        map<int, int> *acceptance_state_token, TokenType** token_types, fstream *input) : meta_data(meta_data),
        acceptance_state_token(acceptance_state_token), token_types(token_types), input(input) {
    automata = new DFA(transition_array, meta_data, input_map, acceptance_states);
    current_pos = 0;
    current_line = 0;
    last_newline_pos = 0;
    last_accepted_pos = 0;
    last_acceptance_state  = -1;
    errorLogger = new ErrorLogger();
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
    Token* token;
    bool panic_mode;
    do {
        automata->reset();
        last_acceptance_state = -1;
        char c;
        string token_str = "";
        streamoff start_pos = current_pos;
        while (delimiters.count(input->peek())) {
            input->get(c);
            if (c == '\n') {
                current_line++;
                last_newline_pos = input->tellg();
            }
        }
        while (!delimiters.count(input->peek()) && input->get(c) &&  !automata->is_error()) {
            automata->move(c);
            token_str += c;
            current_pos = input->tellg();
            if (automata->is_in_acceptance_state()) {
                last_acceptance_state = automata->get_current_state();
                last_accepted_pos = input->tellg();
            }
        }

        if (input->peek() == EOF && start_pos == current_pos) {
            return nullptr;
        }

        panic_mode = false;
        if (automata->is_in_acceptance_state()) {
            int token_type_index = acceptance_state_token->at(automata->get_current_state());
            TokenType *token_type = token_types[token_type_index];
            token = new Token(token_type, token_str);
        } else if (last_acceptance_state != -1) {     // Passed through an acceptance state at some point
            streamoff rewind_offset = current_pos - last_accepted_pos;
            token_str = token_str.substr(0, token_str.length() - rewind_offset);

            int token_type_index = acceptance_state_token->at(last_acceptance_state);
            TokenType *token_type = token_types[token_type_index];
            token = new Token(token_type, token_str);

            rewind_stream(last_accepted_pos);
        } else {
            panic_mode = true;
            ErrorRecoverer* errorRecoverer = new ErrorRecoverer(errorLogger, operation_mode::RECOVERY);
            errorRecoverer->recover(input, start_pos, current_line + 1, current_pos - last_newline_pos,
                    operation_mode::RECOVERY);
            errorRecoverer->report();
        }
    } while(panic_mode);

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

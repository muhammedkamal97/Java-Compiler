//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_TOKENIZER_H
#define PROJECT_TOKENIZER_H

#include <map>
#include <fstream>
#include <tokens/TokenType.h>
#include <tokens/Token.h>
#include "DFA.h"

using namespace std;

enum operation_mode {
    NO_ERROR, RECOVERY
};
class Tokenizer {

private:
    DFA *automata;
    MetaData meta_data;
    map<int, int>* acceptance_state_token;
    TokenType** token_types;
    Token* tokens_buffer[2];
    bool next_token_ready;
    fstream *input;
    streamoff current_pos;
    streamoff last_accepted_pos;
    streamoff last_newline_pos;
    int current_line;
    int last_acceptance_state;

    static const set<char> delimiters;

    Token* process_following_token();
    void rewind_stream(streamoff offset);
public:

    Tokenizer(int **transition_array, MetaData meta_data, map<char, int> *input_map, set<int> acceptance_states,
            map<int, int> *acceptance_state_token, TokenType** token_types, fstream *input);

    Token* next_token();

    bool has_next_token();

    bool is_error();


};


#endif //PROJECT_TOKENIZER_H

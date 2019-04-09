//
// Created by mario_hunter on 4/9/19.
//

#include <tokens/Token.h>
#include "LexicalBufferSlave.h"

using namespace std;

std::fstream *
LexicalBufferSlave::get_write_stream() {
    return write_buffer;
}

void
LexicalBufferSlave::notify(void *notification) {
    Token *token = (Token *) notification;
    if (write_buffer->is_open()) {
        string lex = token->lexeme;
        *write_buffer << lex << endl;
    }
//    write_buffer->close();
}

LexicalBufferSlave::LexicalBufferSlave(fstream *write_buffer) : write_buffer(write_buffer) {}

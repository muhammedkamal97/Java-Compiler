//
// Created by mario_hunter on 4/9/19.
//

#include <tokens/Token.h>
#include "LexicalBufferSlave.h"

std::fstream *
LexicalBufferSlave::get_write_stream() {
    return nullptr;
}

void
LexicalBufferSlave::notify(void *notification) {
    Token *token = (Token *) notification;
//    write_buffer->write(token->lexeme.c_str());
//TODO
}

LexicalBufferSlave::LexicalBufferSlave(fstream *write_buffer) : write_buffer(write_buffer) {}

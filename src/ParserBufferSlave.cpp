//
// Created by mario_hunter on 4/19/19.
//

#include <boost/algorithm/string.hpp>
#include <parser/Production.h>
#include "ParserBufferSlave.h"


using namespace std;

ParserBufferSlave::ParserBufferSlave(std::fstream *write_buffer) : write_buffer(write_buffer) {}

std::fstream *
ParserBufferSlave::get_write_stream() {
    return write_buffer;
}

void
ParserBufferSlave::notify(void *notification) {
    vector<Production*> *prods = (vector<Production*>  *) notification;
    if (write_buffer->is_open()) {
        for(Production* elem : *prods){
            for(GrammarSymbol* symbol : *elem->productions->at(0)){
                *write_buffer << symbol->value << " ";
            }
            *write_buffer << endl;

        }
    }
//    write_buffer->close();
}



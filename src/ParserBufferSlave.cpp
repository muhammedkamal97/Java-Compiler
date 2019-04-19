//
// Created by mario_hunter on 4/19/19.
//

#include <boost/algorithm/string.hpp>
#include "ParserBufferSlave.h"


using namespace std;

ParserBufferSlave::ParserBufferSlave(std::fstream *write_buffer) : write_buffer(write_buffer) {}

std::fstream *
ParserBufferSlave::get_write_stream() {
    return write_buffer;
}

void
ParserBufferSlave::notify(void *notification) {
    string *prod = (string *) notification;
    if (write_buffer->is_open()) {
        *write_buffer << prod << endl;
    }
//    write_buffer->close();
}



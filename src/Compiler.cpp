//
// Created by mario_hunter on 4/9/19.
//

#include <lexical/LexicalComponent.h>
#include "Compiler.h"
#include "LexicalBufferSlave.h"

void
Compiler::compile(fstream *input) {
    Component* lexical = new LexicalComponent(nullptr, input); //TODO provide config and input fstreams
    lexical->attach_to_master_channel(nullptr); // leave null
    lexical->attach_to_slave_port(new LexicalBufferSlave(nullptr)); //TODO provide out streams
    lexical->start_work_slaves();
}

Compiler::Compiler() :{
    table = new SimpleSymbolTable;
}

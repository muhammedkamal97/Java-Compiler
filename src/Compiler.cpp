//
// Created by mario_hunter on 4/9/19.
//

#include <lexical/LexicalComponent.h>
#include "Compiler.h"
#include "LexicalBufferSlave.h"

void
Compiler::compile(fstream *input) {
    fstream lex_config("lex_config.txt");
    fstream lex_out("lex_out.txt", ios::app);
    SimpleSymbolTable *table = new SimpleSymbolTable;
    Component *lexical = new LexicalComponent(&lex_config, input, table);
    lexical->attach_to_master_channel(nullptr); // leave null
    lexical->attach_to_slave_port(new LexicalBufferSlave(&lex_out));
    lexical->start_work_slaves();
}

Compiler::Compiler() {
    table = new SimpleSymbolTable;
}

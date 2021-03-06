//
// Created by mario_hunter on 4/9/19.
//
#include "ParserBufferSlave.h"

#include <lexical/LexicalComponent.h>
#include <parser/ParserComponent.h>
#include "Compiler.h"
#include "LexicalBufferSlave.h"


void
Compiler::compile(fstream *input) {
    fstream lex_config("config.txt");
    fstream parser_config("parser_config.txt");
    fstream lex_out("lex_out.txt", ios::app);
    fstream parser_out("parser_out.txt", ios::app);

    SimpleSymbolTable *table = new SimpleSymbolTable;


    Component *parser = new ParserComponent(&parser_config, nullptr);
    parser->attach_to_master_channel(nullptr); //leave null
    //TODO fix issue of buffer here
//    parser->attach_to_slave_port(new ParserBufferSlave(&parser_out));


    Component *lexical = new LexicalComponent(&lex_config, input, table);
    lexical->attach_to_master_channel(parser); // leave null
    lexical->attach_to_slave_port(new LexicalBufferSlave(&lex_out));

    parser->start_work_slaves();
}

Compiler::Compiler() {
    table = new SimpleSymbolTable;
}

#include <iostream>
#include <fstream>
#include <lexical/LexicalComponent.h>
#include "LexicalBufferSlave.h"
#include "Compiler.h"

int
main(int ac, char **av) {
    std::cout << "Hello, World!" << std::endl;
    fstream inp("test.txt");
    auto *compiler = new Compiler();
    compiler->compile(&inp);
    return 0;
}
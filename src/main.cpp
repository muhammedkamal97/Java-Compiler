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
    try {
        compiler->compile(&inp);
    }catch(exception e){
        std::cerr << "Your input is a hideous abomination " << endl;
    }


    return 0;
}
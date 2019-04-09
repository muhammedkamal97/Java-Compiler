#include <iostream>
#include <lexical/LexicalComponent.h>
#include "LexicalBufferSlave.h"

int
main() {
    std::cout << "Hello, World!" << std::endl;
    Component* lexical = new LexicalComponent(nullptr, nullptr); //TODO provide config and input fstreams
    lexical->attach_to_master_channel(nullptr); // leave null
    lexical->attach_to_slave_port(new LexicalBufferSlave(nullptr));
    lexical->start_work_slaves();
    return 0;
}
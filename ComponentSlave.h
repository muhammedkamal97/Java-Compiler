//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_COMPONENTSLAVE_H
#define PROJECT_COMPONENTSLAVE_H

#include <fstream>

class ComponentSlave {
    virtual std::fstream *get_write_stream() = 0;

    virtual void notify() = 0;
};


#endif //PROJECT_COMPONENTSLAVE_H

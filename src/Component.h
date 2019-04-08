//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_COMPONENT_H
#define PROJECT_COMPONENT_H


#include <ostream>
#include "ComponentSlave.h"
#include <vector>

using namespace std;

class Component : public ComponentSlave {
protected:
    Component *master;
    vector<Component *> slaves;

    bool has_slave(ComponentSlave *slave);

public:

    /* attach a new slave buffer to this component to write ouput to*/
    void
    attach_to_slave_port(ComponentSlave *slave) {
        if (has_slave(slave)) return;
        this->slaves.emplace_back(slave);
    }

    /* accept a new master to control the processing of input. Only one master can be accepted.
     * If the slave deems the master as acceptable -first to call, it will complete the handshake by calling the
     * handshake method on the master and passing itself to be controlled by the master.*/
    void
    attach_to_master_channel(Component *master) {
        if (this->master != nullptr) return;
        this->master = master;
        this->master->handshake_slave_channel(this);
    }

    /*handshake the slave after being accepted as master*/

    void
    handshake_slave_channel(ComponentSlave *slave) {
        this->attach_to_slave_port(slave);
    }


    virtual void *process_next_input() = 0;


    Component(std::fstream *config, std::fstream *input);

};

bool
Component::has_slave(ComponentSlave *slave) {
    auto it = this->slaves.begin();
    while (it != this->slaves.end()) {
        if (slave == *it) return slave;
        it++;
    }
    return false;
}


#endif //PROJECT_COMPONENT_H

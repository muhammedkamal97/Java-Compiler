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
    vector<ComponentSlave *> writes_slaves;
    Component * work_slave;
    bool has_write_slave(ComponentSlave *slave);

public:

    /* attach a new slave buffer to this component to write ouput to*/
    void
    attach_to_slave_port(ComponentSlave *slave) {
        if (has_write_slave(slave)) return;
        this->writes_slaves.emplace_back(slave);
    }

    /* accept a new master to control the processing of input. Only one master can be accepted.
     * If the slave deems the master as acceptable -first to call, it will complete the handshake by calling the
     * handshake method on the master and passing itself to be controlled by the master.*/
    void
    attach_to_master_channel(Component *master) {
        if (this->master != nullptr) return;
        if (this->master == nullptr) {
            this->master = this;
            return;
        }

        this->master = master;
        this->master->handshake_slave_channel(this);
    }

    /*handshake the slave after being accepted as master*/
    void
    handshake_slave_channel(Component *slave) {
        this->work_slave=slave;
    }

    void start_work_slaves(){
       while(true){
           void* result = work_slave->process_next_input();
           if(result == nullptr) break;

           for(int i = 0;i<writes_slaves.size();i++){
               writes_slaves[i]->notify(result);
           }
       }
    }

    virtual void *process_next_input() = 0;

    Component(std::fstream *config, std::fstream *input);

};

bool
Component::has_write_slave(ComponentSlave *slave) {
    auto it = this->writes_slaves.begin();
    while (it != this->writes_slaves.end()) {
        if (slave == *it) return slave;
        it++;
    }
    return false;
}


#endif //PROJECT_COMPONENT_H

//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_DFAMINIMIZER_H
#define PROJECT_DFAMINIMIZER_H

#include<map>
#include <vector>
#include <string>

using namespace std;

class DFAMinimizer {
private:
    int **transition_array;
    pair<int,int> *map_size;
public:
    DFAMinimizer(vector<int[]> *input_transition_array);
    void minimize();

    int **getTransition_array() const {
        return transition_array;
    }

    pair<int, int> *getMap_size() const {
        return map_size;
    }
};


#endif //PROJECT_DFAMINIMIZER_H

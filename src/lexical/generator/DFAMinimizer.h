//
// Created by mostafa on 22/03/19.
//

#ifndef TEST_DFAMINIMIZER_H
#define TEST_DFAMINIMIZER_H
#include<map>
#include <vector>
#include <string>
#include <set>

using namespace std;

class DFAMinimizer {
private:
    int **transition_array;
    pair<int,int> map_size;
    vector<int *> input_transition_array;
    set<int> acceptance_states;
    set<int> new_acceptance_states;
    pair<int, int> DFA_size;
    set<int> getNonAcceptanceStates(set<int> acceptance_states);
    vector<set<int>> partitionState(set<int> state);
    bool belongsTo(int state_1, int state_2);
    int getPartitionNumber(int state, vector<set<int>> partitions);
    vector<set<int>> partitioning();
    void initTransitionArray(int number_of_rows);
    void fillTransitionArray(vector<set<int>> final_states);
    bool checkGoingToStates(int state_1, int state_2);

public:
    DFAMinimizer(vector<int *> input_transition_array, set<int> acceptance_states, pair<int, int> DFA_size, int FAi_state){
        this->acceptance_states = acceptance_states;
        this->input_transition_array = input_transition_array;
        this->DFA_size = DFA_size;
    }
    void minimize();

    int **getTransition_array() const {
        return transition_array;
    }

    pair<int, int> getMap_size() const {
        return map_size;
    }
    set<int> getAcceptanceStates() const{
        return new_acceptance_states;
    }
};
#endif //TEST_DFAMINIMIZER_H

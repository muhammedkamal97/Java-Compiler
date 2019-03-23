//
// Created by mostafa on 22/03/19.
//

#include "DFAMinimizer.h"


using namespace std;


vector<set<int>> partitioned_states;

void DFAMinimizer::minimize(){
    vector<set<int>> final_states = partitioning();
    initTransitionArray(final_states.size());
    fillTransitionArray(final_states);
    (map_size).first = final_states.size();
    (map_size).second = DFA_size.second;
}



void DFAMinimizer::fillTransitionArray(vector<set<int>> final_states){
    for(int i = 0; i < final_states.size(); i++){
        auto old_state = final_states[i].begin();
        for (int j = 0; j < DFA_size.second; j++){
            transition_array[i][j] = getPartitionNumber(input_transition_array[*old_state][j], final_states);
        }
    }
}



void DFAMinimizer::initTransitionArray(int number_of_rows){
    transition_array = new int*[number_of_rows];
    for(int i = 0; i < number_of_rows; ++i)
        transition_array[i] = new int[DFA_size.second];
}

vector<set<int>> DFAMinimizer::partitioning(){
    vector<set<int>> final_states;
    partitioned_states.push_back(acceptance_states);
    partitioned_states.push_back(getNonAcceptanceStates(acceptance_states));
    while (partitioned_states.size() != 0){
        set<int> current_state = partitioned_states.back();
        vector<set<int>> new_partitions = partitionState(current_state);
        partitioned_states.pop_back();
        if(new_partitions.size() == 1){
            final_states.push_back(current_state);
        } else{
            for(int i = 0; i < new_partitions.size(); i++){
                partitioned_states.push_back(new_partitions[i]);
            }
        }
    }
    return final_states;
}




vector<set<int>> DFAMinimizer::partitionState(set<int> states){
    vector<set<int >> partitioned_state;
    vector<int> not_partitioned_states(states.begin(),states.end());
    while(not_partitioned_states.size() != 0){
        int state = not_partitioned_states.at(0);
        not_partitioned_states.erase(not_partitioned_states.begin());
        vector<int> selected_states_indexes;
        set<int> selected_states;
        selected_states.insert(state);
        for(int i = 0; i < not_partitioned_states.size(); i++){
            if(belongsTo(state, not_partitioned_states[i])){
                selected_states_indexes.push_back(i);
                selected_states.insert(not_partitioned_states[i]);
            }
        }
        for(int i = 0; i < selected_states_indexes.size(); i++){
            not_partitioned_states.erase(not_partitioned_states.begin()+selected_states_indexes[i]-i);
        }
        partitioned_state.push_back(selected_states);
    }
    return partitioned_state;
}


bool DFAMinimizer::belongsTo(int state_1, int state_2){
    if(checkGoingToStates(state_1, state_2))
        return true;
    return false;
}

bool DFAMinimizer::checkGoingToStates(int state_1, int state_2){
    for(int i = 0; i < DFA_size.second; i++){
        if(input_transition_array[state_1][i] == input_transition_array[state_2][i]){
            continue;
        }
        if(getPartitionNumber(input_transition_array[state_1][i], partitioned_states) !=
           getPartitionNumber(input_transition_array[state_2][i], partitioned_states)){
            return false;
        }
    }
    return true;
}
int DFAMinimizer::getPartitionNumber(int state, vector<set<int>> partitions){
    for(int i = 0; i < partitions.size(); i++){
        if(partitions[i].find(state) != partitions[i].end()){
            return i;
        }
    }
}

set<int> DFAMinimizer::getNonAcceptanceStates(set<int> acceptance_states){
    set<int> non_acceptance_states;
    for(int i = 0; i < (input_transition_array).size(); i++){
        non_acceptance_states.insert(i);
    }
    for (std::set<int>::iterator it=acceptance_states.begin(); it!=acceptance_states.end(); ++it){
        non_acceptance_states.erase(*it);
    }
    return non_acceptance_states;
}
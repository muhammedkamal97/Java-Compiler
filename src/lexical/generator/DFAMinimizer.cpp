//
// Created by mostafa on 22/03/19.
//

#include <cstring>
#include "DFAMinimizer.h"


using namespace std;


vector<set<int>> partitioned_states_stack;
vector<set<int>> final_states;
vector<set<int>> all_partitions;

void DFAMinimizer::Minimize(){
    PartitioningAcceptanceStates();
    PartitioningNonAcceptanceStates();
    InitTransitionArray(final_states.size());
    FillTransitionArray(final_states);
    (map_size).first = final_states.size();
    (map_size).second = data.DFA_size.second;
    data.DFA_size = map_size;
}



void DFAMinimizer::FillTransitionArray(vector<set<int>> final_states){
    for(int i = 0; i < final_states.size(); i++){
        auto old_state = final_states[i].begin();
        for (int j = 0; j < data.DFA_size.second; j++){
            transition_array[i][j] = GetPartitionNumber(input_transition_array[*old_state][j], final_states);
        }
    }
}

void DFAMinimizer::PartitioningAcceptanceStates(){
    vector<set<int>> new_accepted_states  = GetMinimumStates(acceptance_states, true);
    new_token_type = new TokenType[new_accepted_states.size()];
    for(int i = 0; i < new_accepted_states.size(); i++){
        final_states.push_back(new_accepted_states[i]);
        new_tokens_indexes.insert({i+1, i});
        new_token_type[i] = token_type[tokens_indexes.find(*new_accepted_states[i].begin())->second];
        this->new_acceptance_states.insert(i+1);
    }
}

void DFAMinimizer::PartitioningNonAcceptanceStates(){
    vector<set<int>> non_acceptance_states  = GetMinimumStates(GetNonAcceptanceStates(acceptance_states), false);
    for(int i = 0; i < non_acceptance_states.size(); i++){
        final_states.push_back(non_acceptance_states[i]);
    }
    for(int i = 0; i < final_states.size(); i++){
        if(final_states[i].find(0) != final_states[i].end()){
            set<int> temp = final_states[i];
            final_states.erase(final_states.begin()+i);
            final_states.insert(final_states.begin(),temp);
        }
    }
    for(int i = 0; i < final_states.size(); i++){
        if(final_states[i].find(data.invalid_state_index) != final_states[i].end()){
            data.invalid_state_index = i;
        }
    }
}


void DFAMinimizer::InitTransitionArray(int number_of_rows){
    transition_array = new int*[number_of_rows];
    for(int i = 0; i < number_of_rows; ++i)
        transition_array[i] = new int[data.DFA_size.second];
}

vector<set<int>> DFAMinimizer::GetMinimumStates(set<int> states, bool is_acceptance_states){
    vector<set<int>> final_states;
    partitioned_states_stack.push_back(states);
    all_partitions.push_back(states);

    while (partitioned_states_stack.size() != 0){
        set<int> current_partition = partitioned_states_stack.back();
        vector<set<int>> new_partitions = splitPartition(current_partition, is_acceptance_states);
        partitioned_states_stack.pop_back();
        all_partitions.pop_back();
        if(new_partitions.size() == 1){
            final_states.push_back(current_partition);
            all_partitions.push_back(current_partition);
        } else{
            for(int i = 0; i < new_partitions.size(); i++){
                partitioned_states_stack.push_back(new_partitions[i]);
                all_partitions.push_back(new_partitions[i]);
            }
        }
    }
    return final_states;
}




vector<set<int>> DFAMinimizer::splitPartition(set<int> states, bool is_acceptance_states){
    vector<set<int >> partitioned_state;
    vector<int> not_partitioned_states(states.begin(),states.end());
    vector<TokenType> new_token_type_vector;
    while(not_partitioned_states.size() != 0){
        int state = not_partitioned_states.at(0);
        not_partitioned_states.erase(not_partitioned_states.begin());
        vector<int> selected_states_indexes;
        set<int> selected_states;
        selected_states.insert(state);
        for(int i = 0; i < not_partitioned_states.size(); i++){
            if(CanBeMerged(state, not_partitioned_states[i], is_acceptance_states)){
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


bool DFAMinimizer::CanBeMerged(int state_1, int state_2, bool is_acceptance_states){
    if(GoingToSameStates(state_1, state_2)){
        if(is_acceptance_states){
            return IsCompatible(state_1, state_2);
        }
        return true;
    }
    return false;
}


bool DFAMinimizer::IsCompatible(int state_1, int state_2){
    string token_type_1 = token_type[tokens_indexes.find(state_1)->second].name;
    string token_type_2 = token_type[tokens_indexes.find(state_2)->second].name;
    if(token_type_1.compare(token_type_2)  == 0){
        return true;
    }
    return false;
}
bool DFAMinimizer::GoingToSameStates(int state_1, int state_2){
    for(int i = 0; i < data.DFA_size.second; i++){
        if(input_transition_array[state_1][i] == input_transition_array[state_2][i]){
            continue;
        }
        if(GetPartitionNumber(input_transition_array[state_1][i], all_partitions) !=
                GetPartitionNumber(input_transition_array[state_2][i], all_partitions)){
            return false;
        }
    }
    return true;
}
int DFAMinimizer::GetPartitionNumber(int state, vector<set<int>> partitions){
    for(int i = 0; i < partitions.size(); i++){
        if(partitions[i].find(state) != partitions[i].end()){
            return i;
        }
    }
}

set<int> DFAMinimizer::GetNonAcceptanceStates(set<int> acceptance_states){
    set<int> non_acceptance_states;
    for(int i = 0; i < (input_transition_array).size(); i++){
        non_acceptance_states.insert(i);
    }
    for (std::set<int>::iterator it=acceptance_states.begin(); it!=acceptance_states.end(); ++it){
        non_acceptance_states.erase(*it);
    }
    return non_acceptance_states;
}
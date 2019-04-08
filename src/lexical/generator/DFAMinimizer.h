//
// Created by mostafa on 22/03/19.
//

#ifndef TEST_DFAMINIMIZER_H
#define TEST_DFAMINIMIZER_H
#include<map>
#include <vector>
#include <string>
#include <set>
#include <lexical/MetaData.h>
#include <tokens/TokenType.h>

using namespace std;

class DFAMinimizer {
private:
    int **transition_array;
    pair<int,int> map_size;
    vector<int *> input_transition_array;
    set<int> acceptance_states;
    set<int> new_acceptance_states;
    map<int, int> tokens_indexes;
    TokenType *token_type;
    map<int, int> new_tokens_indexes;
    MetaData data;
    TokenType *new_token_type;
    set<int> GetNonAcceptanceStates(set<int> acceptance_states);
    vector<set<int>> splitPartition(set<int> states, bool is_acceptance_states);
    bool CanBeMerged(int state_1, int state_2, bool is_acceptance_states);
    int GetPartitionNumber(int state, vector<set<int>> partitions);
    vector<set<int>> GetMinimumStates(set<int> states, bool is_acceptance_states);
    void InitTransitionArray(int number_of_rows);
    void FillTransitionArray(vector<set<int>> final_states);
    bool GoingToSameStates(int state_1, int state_2);
    bool IsCompatible(int state_1, int state_2);
    void PartitioningAcceptanceStates();
    void PartitioningNonAcceptanceStates();

public:
    DFAMinimizer(vector<int *> input_transition_array, set<int> acceptance_states, map<int, int> tokens_indexes, TokenType *token_type, MetaData meta_data){
        this->acceptance_states = acceptance_states;
        this->input_transition_array = input_transition_array;
        this->tokens_indexes = tokens_indexes;
        this->token_type = token_type;
        this->data = meta_data;
    }
    void Minimize();

    int **getTransition_array() const {
        return transition_array;
    }

    pair<int, int> getMap_size() const {
        return map_size;
    }
    set<int> getAcceptanceStates() const{
        return new_acceptance_states;
    }

    MetaData getMeta_data() const {
        return this->data;
    }

    map<int, int> getToken_indexes() const {
        return this->new_tokens_indexes;
    }

    TokenType * getToken_types() const{
        return this->new_token_type;
    }

};
#endif //TEST_DFAMINIMIZER_H

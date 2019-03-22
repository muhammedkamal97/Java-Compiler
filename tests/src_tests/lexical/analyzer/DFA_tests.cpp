//
// Created by khaled on 3/22/19.
//

#include "gtest/gtest.h"
#include "DFA.h"

class DFATests : public ::testing::Test {

protected:
    void SetUp() {
        for (int i = 0; i < 5; ++i)
            transition_array[i] = new int[2] {array[i][0], array[i][1]};
        dfa = new DFA(transition_array, transition_size, &input_map, initial_state, acceptance_states);
        printf("%d", dfa->get_current_state());
    }
    int **transition_array = new int*[5];
    int array[5][2] = {
            {1, 2},
            {-1, 1},
            {3, -1},
            {4, -1},
            {4, -1}
    };
    pair<int, int> transition_size = {5, 2};
    map<char, int> input_map = {{'a', 0}, {'b', 1}};
    int initial_state = 0;
    set<int> acceptance_states = {1, 2, 4};

    DFA *dfa;
};

TEST_F(DFATests, startsAtInitialState) {
    ASSERT_EQ(dfa->get_current_state(), initial_state);
}

TEST_F(DFATests, correctTransitionSingleInput1) {
    dfa->move('a');
    ASSERT_EQ(dfa->get_current_state(), array[0][input_map.at('a')]);
}

TEST_F(DFATests, correctTransitionSingleInput2) {
    dfa->move('b');
    ASSERT_EQ(dfa->get_current_state(), array[0][input_map.at('b')]);
}

TEST_F(DFATests, correctTransitionMultipleInput1) {
    char input[3] = {'a', 'b', 'b'};
    for (int i = 0; i < 3; ++i) {
        dfa->move(input[i]);
    }
    ASSERT_EQ(dfa->get_current_state(), 1);
}

TEST_F(DFATests, correctTransitionMultipleInput2) {
    char input[2] = {'b', 'a'};
    for (int i = 0; i < 2; ++i) {
        dfa->move(input[i]);
    }
    ASSERT_EQ(dfa->get_current_state(), 3);
}

TEST_F(DFATests, correctLastAcceptanceStateSingleInput) {
    dfa->move('a');
    ASSERT_EQ(dfa->get_last_accepted_state(), 1);
}

TEST_F(DFATests, correctLastAcceptanceStateMultipleInput) {
    char input[2] = {'b', 'a'};
    for (int i = 0; i < 2; ++i) {
        dfa->move(input[i]);
    }
    ASSERT_EQ(dfa->get_last_accepted_state(), 2);
}
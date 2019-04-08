//
// Created by khaled on 3/22/19.
//

#include "gtest/gtest.h"
#include "DFA.h"

/*
 * Tests a machine that accepts the following sequences:
 * 'ab*', 'b' and 'baa+'
 */
class DFASanityTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        for (int i = 0; i < 5; ++i)
            transition_array[i] = new int[2] {array[i][0], array[i][1]};
        dfa = new DFA(transition_array, meta_data, &input_map, acceptance_states);
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
    MetaData meta_data = {pair<int, int>(5, 2), -1, 0};
    map<char, int> input_map = {{'a', 0}, {'b', 1}};
    set<int> acceptance_states = {1, 2, 4};

    DFA *dfa;
    
};

TEST_F(DFASanityTest, startsAtInitialState) {
    ASSERT_EQ(dfa->get_current_state(), meta_data.init_state_index);
}

TEST_F(DFASanityTest, correctTransitionSingleInput1) {
    dfa->move('a');
    ASSERT_EQ(dfa->get_current_state(), array[0][input_map.at('a')]);
}

TEST_F(DFASanityTest, correctTransitionSingleInput2) {
    dfa->move('b');
    ASSERT_EQ(dfa->get_current_state(), array[0][input_map.at('b')]);
}

TEST_F(DFASanityTest, correctTransitionMultipleInput1) {
    char input[3] = {'a', 'b', 'b'};
    for (int i = 0; i < 3; ++i) {
        dfa->move(input[i]);
    }
    ASSERT_EQ(dfa->get_current_state(), 1);
}

TEST_F(DFASanityTest, correctTransitionMultipleInput2) {
    char input[2] = {'b', 'a'};
    for (int i = 0; i < 2; ++i) {
        dfa->move(input[i]);
    }
    ASSERT_EQ(dfa->get_current_state(), 3);
}

TEST_F(DFASanityTest, invalidTransitionGiveError) {
    char input[2] = {'b', 'b'};
    for (int i = 0; i < 2; ++i) {
        dfa->move(input[i]);
    }
    ASSERT_TRUE(dfa->is_error());
}

TEST_F(DFASanityTest, resetWorks) {
    char input[2] = {'b', 'a'};
    for (int i = 0; i < 2; ++i) {
        dfa->move(input[i]);
    }
    dfa->reset();
    ASSERT_EQ(dfa->get_current_state(), 0);
}


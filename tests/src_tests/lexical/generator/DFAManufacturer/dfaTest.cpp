//
// Created by mario_hunter on 3/23/19.
//

#include "gtest/gtest.h"
#include "BasicSanityTest.cpp"
#include "../../util/compare.h"

TEST_F(BasicSanityTest, non_init_tranisition_array) {
    auto arr = manu->getTransition_array();
    ASSERT_EQ(arr->size(), 0) << "transition map is populated before generate command";
}

TEST_F(BasicSanityTest, simple_dfa_generation) {
    manu->generate_dfa();
    auto arr = manu->getTransition_array();
    auto *correct_dfa = new vector<int *>;
    int r0[] = {1, 0};
    int r1[] = {1, 2};
    int r2[] = {1, 3};
    int r3[] = {1, 0};
    correct_dfa->emplace_back(r0);
    correct_dfa->emplace_back(r1);
    correct_dfa->emplace_back(r2);
    correct_dfa->emplace_back(r3);
    compare_dfas(correct_dfa, arr);
}

TEST_F(BasicSanityTest, epsilon_closures) {
    manu->generate_dfa();
    set<int> *exp_closures[] = {
            new set<int>({1}),
            new set<int>(),
            new set<int>(),
            new set<int>(),
            new set<int>()
    };
    compare_closures(exp_closures, manu->getEpsilon_closures());
}
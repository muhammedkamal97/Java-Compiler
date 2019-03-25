//
// Created by mario_hunter on 3/23/19.
//

#include "gtest/gtest.h"
#include "BasicSanityTest2.cpp"
#include "../../util/compare.h"

TEST_F(BasicSanityTest2, non_init_tranisition_array) {
    auto arr = manu->getTransition_array();
    ASSERT_EQ(arr->size(), 0) << "transition map is populated before generate command";
}

TEST_F(BasicSanityTest2, simple_dfa_generation) {
    manu->generate_dfa();
    auto arr = manu->getTransition_array();
    auto *correct_dfa = new vector<int *>;
    int r0[] = {1, 2};
    int r1[] = {1, 3};
    int r2[] = {1, 2};
    int r3[] = {1, 4};
    int r4[] = {1, 2};
    correct_dfa->emplace_back(r0);
    correct_dfa->emplace_back(r1);
    correct_dfa->emplace_back(r2);
    correct_dfa->emplace_back(r3);
    correct_dfa->emplace_back(r4);
    compare_dfas(correct_dfa, arr);
}

TEST_F(BasicSanityTest2, epsilon_closures) {
    manu->generate_dfa();
    set<int> *exp_closures[] = {
            new set<int>({1,7,2,4}),
            new set<int>({2,4}),
            new set<int>(),
            new set<int>({6,1,7,2,4}),
            new set<int>(),
            new set<int>({6,1,7,2,4}),
            new set<int>({1,7,2,4}),
            new set<int>(),
            new set<int>(),
            new set<int>(),
            new set<int>()
    };
    compare_closures(exp_closures, manu->getEpsilon_closures());
}
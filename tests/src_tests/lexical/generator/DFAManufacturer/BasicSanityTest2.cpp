//
// Created by mario_hunter on 3/23/19.
//
#include "gtest/gtest.h"
#include "lexical/generator/DFAManufacturer.h"

class BasicSanityTest2 : public ::testing::Test {
protected:
    void
    create_data() {
        nfa = new vector<set<int> *>();
        auto *s0 = new set<int>[3];
        auto *s1 = new set<int>[3];
        auto *s2 = new set<int>[3];
        auto *s3 = new set<int>[3];
        auto *s4 = new set<int>[3];
        auto *s5 = new set<int>[3];
        auto *s6 = new set<int>[3];
        auto *s7 = new set<int>[3];
        auto *s8 = new set<int>[3];
        auto *s9 = new set<int>[3];
        auto *s10 = new set<int>[3];
        s0[0] = set<int>({}); s0[1]= set<int>({}); s0[2]= set<int>({1,7});
        s1[0] = set<int>({}); s1[1]= set<int>({}); s1[2]= set<int>({2,4});
        s2[0] = set<int>({3}); s2[1]= set<int>({}); s2[2]= set<int>({});
        s3[0] = set<int>({}); s3[1]= set<int>({}); s3[2]= set<int>({6});
        s4[0] = set<int>({}); s4[1]= set<int>({5}); s4[2]= set<int>({});
        s5[0] = set<int>({}); s5[1]= set<int>({}); s5[2]= set<int>({6});
        s6[0] = set<int>({}); s6[1]= set<int>({}); s6[2]= set<int>({1,7});
        s7[0] = set<int>({8}); s7[1]= set<int>({}); s7[2]= set<int>({});
        s8[0] = set<int>({}); s8[1]= set<int>({9}); s8[2]= set<int>({});
        s9[0] = set<int>({}); s9[1]= set<int>({10}); s9[2]= set<int>({});
        s10[0] = set<int>({}); s10[1]= set<int>({}); s10[2]= set<int>({});

        nfa->emplace_back(s0);
        nfa->emplace_back(s1);
        nfa->emplace_back(s2);
        nfa->emplace_back(s3);
        nfa->emplace_back(s4);
        nfa->emplace_back(s5);
        nfa->emplace_back(s6);
        nfa->emplace_back(s7);
        nfa->emplace_back(s8);
        nfa->emplace_back(s9);
        nfa->emplace_back(s10);
    }

    void SetUp() override {
        create_data();
        manu = new DFAManufacturer(this->nfa,new MetaData{pair<int,int>() ,-1,0,2,3});
    }

    DFAManufacturer *manu;
    vector<set<int> *> *nfa;
};

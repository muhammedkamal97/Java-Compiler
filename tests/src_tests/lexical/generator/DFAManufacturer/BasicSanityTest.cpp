//
// Created by mario_hunter on 3/23/19.
//
#include "gtest/gtest.h"
#include "lexical/generator/DFAManufacturer.h"

class BasicSanityTest : public ::testing::Test {
protected:
    void
    create_data() {
        nfa = new vector<set<int> *>();
        set<int> *sinit = new set<int>[3];
        set<int> *s0 = new set<int>[3];
        set<int> *s1 = new set<int>[3];
        set<int> *s2 = new set<int>[3];
        set<int> *s3 = new set<int>[3];
        sinit[0] = set<int>({}); sinit[1]= set<int>({}); sinit[2]= set<int>({1});
        s0[0] = set<int>({2, 1}); s0[1]= set<int>({1}); s0[2]= set<int>({});
        s1[0] = set<int>({}); s1[1]= set<int>({3}); s1[2]= set<int>({});
        s2[0] = set<int>({}); s2[1]= set<int>({4}); s2[2]= set<int>({});
        s3[0] = set<int>({}); s3[1]= set<int>({}); s3[2]= set<int>({});

        nfa->emplace_back(sinit);
        nfa->emplace_back(s0);
        nfa->emplace_back(s1);
        nfa->emplace_back(s2);
        nfa->emplace_back(s3);
    }

    void SetUp() override {
        create_data();
        manu = new DFAManufacturer(this->nfa, new MetaData{pair<int,int>() ,-1,0,2,3});
    }

    DFAManufacturer *manu;
    vector<set<int> *> *nfa;
};

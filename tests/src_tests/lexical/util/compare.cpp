//
// Created by mario_hunter on 3/23/19.
//


#include "compare.h"

void
compare_dfas(vector<int *> *exp, vector<int *> *act) {
    ASSERT_EQ(exp->size(), act->size()) << "Number of states mismatch between expected and actual";
    for (int i = 0; i < exp->size(); i++) {
        int *expRow = exp->at(i);
        int *actRow = act->at(i);
        int expSize = sizeof(expRow) / sizeof(expRow[0]);
        int actSize = sizeof(actRow) / sizeof(actRow[0]);
        ASSERT_EQ(expSize, actSize) << "Number of input transitions mismatch at state " << i;
        for (int j = 0; j < expSize; j++) {
            EXPECT_EQ(expRow[j], actRow[j]) << "Invalid transition for input " << j << " for state " << i;
        }
    }
}


void
compare_closures(set<int> **exp, set<int> **act) {
    int exp_size = sizeof(exp) / sizeof(exp[0]);
    int act_size = sizeof(act) / sizeof(act[0]);
    ASSERT_EQ(exp_size, act_size) << "Number of states mismatch between expected and actual";
    for(int i=0;i<exp_size;i++){
        EXPECT_TRUE(*(exp[i]) == *(act[i]));
    }

}

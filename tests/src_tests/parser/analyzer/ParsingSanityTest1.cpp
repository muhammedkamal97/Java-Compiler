//
// Created by mario_hunter on 4/20/19.
//

#include <gtest/gtest.h>
#include "ParsingSanityTestSetup.cpp"
#include "../util/util.h"
//#include "../util/util.h"


TEST_F(ParsingSanityTestSetup, simpleTest) {
    Token *tkn1, *tkn2, *tkn3, *tkn4;
    tkn1 = create_token(string("a"));
    tkn2 = create_token(string("b"));
    tkn3 = create_token(string("b"));
    tkn4 = create_token(string("a"));

    vector<Token *> *tokens = new vector<Token *>();
    tokens->push_back(tkn1);
    tokens->push_back(tkn2);
    tokens->push_back(tkn3);
    tokens->push_back(tkn4);
    tokens->push_back(nullptr);
    int index = 0;

    vector<Production *> *prods = new vector<Production *>();

    do {
        auto *res_prods = parser->next_production(tokens->at(index));
        if (res_prods != nullptr) prods->insert(prods->end(),res_prods->begin(),res_prods->end());
        index++;

    } while (parser->has_next_production());

    EXPECT_TRUE(parser->has_successfully_terminated());
    EXPECT_EQ(prods->size(), 4);
    EXPECT_EQ(prods->at(0), pdt[0][0]);
    EXPECT_EQ(prods->at(1), pdt[1][1]);
    EXPECT_EQ(prods->at(2), pdt[1][1]);
    EXPECT_EQ(prods->at(3), pdt[1][0]);


}


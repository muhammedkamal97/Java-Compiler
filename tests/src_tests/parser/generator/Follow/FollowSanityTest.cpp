//
// Created by khaled on 4/22/19.
//

#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include "ParserConfigInterpreter.h"
#include "Follow.h"

class FollowSanityTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        interpreter->generate_production_rules();
        rules = interpreter->get_production_rules();

        first_map = new map<string, vector<string> *>;
        first_map->insert(make_pair("F", new vector<string>{"(", "id"} ));
        first_map->insert(make_pair("T1", new vector<string>{"\\L", "*"} ));
        first_map->insert(make_pair("T", new vector<string>{"(", "id"} ));
        first_map->insert(make_pair("E1", new vector<string>{"\\L", "+"} ));
        first_map->insert(make_pair("E", new vector<string>{"(", "id"} ));
        follow_map = compute_follow(rules, first_map);
    }

    fstream* config = new fstream("../../tests/src_tests/parser/generator/Follow/SanityTestGrammar");
    ParserConfigInterpreter* interpreter = new ParserConfigInterpreter(this->config);
    ProductionRules* rules = interpreter->get_production_rules();
    map<string, vector<string> *> * follow_map;
    map<string, vector<string> *> * first_map;

};

TEST_F(FollowSanityTest, computesCorrectly) {
    ASSERT_THAT(*follow_map->at("E"), ::testing::ElementsAre("$", ")"));
    ASSERT_THAT(*follow_map->at("E1"), ::testing::ElementsAre("$", ")"));
    ASSERT_THAT(*follow_map->at("T"), ::testing::ElementsAre("$", ")", "+"));
    ASSERT_THAT(*follow_map->at("T1"), ::testing::ElementsAre("$", ")", "+"));
    ASSERT_THAT(*follow_map->at("F"), ::testing::ElementsAre("$", ")", "*", "+"));
}


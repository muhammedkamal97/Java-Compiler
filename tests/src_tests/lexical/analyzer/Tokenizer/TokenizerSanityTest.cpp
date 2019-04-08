//
// Created by khaled on 4/8/19.
//


#include <lexical/analyzer/Tokenizer.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"
#include "DFA.h"

/*
 * Tests that tokenizes the following string:
 * T1: ab* | b
 * T2: baa+
 */
class TokenizerSanityTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        for (int i = 0; i < 5; ++i)
            transition_array[i] = new int[2] {array[i][0], array[i][1]};

//        char s[101];
//        input.getline(s, 100);
//        std::cout << "HEEEEEEERE " << s << endl;
        tokenizer = new Tokenizer(transition_array, meta_data, &input_map, acceptance_states, &acceptance_state_token,
                (TokenType**)token_types, &input);
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
    TokenType* token_types[2] = {new TokenType("T1"), new TokenType("T2")};
    map<int, int> acceptance_state_token = {{1, 0}, {2, 0}, {4, 1}};

    fstream input = fstream("../../tests/src_tests/lexical/analyzer/Tokenizer/SanityTestProgram1");

    Tokenizer *tokenizer;



};

TEST_F(TokenizerSanityTest, checkHasInitialToken) {
    ASSERT_TRUE(tokenizer->has_next_token());
}

TEST_F(TokenizerSanityTest, checkProcessedTokenLexemes) {
    vector<string> token_strings;
    while(tokenizer->has_next_token()) {
        token_strings.push_back(tokenizer->next_token()->lexeme);
    }
    ASSERT_THAT(token_strings, ::testing::ElementsAre("ab", "a", "abbb", "a", "ab", "b", "baa", "abbbb", "a", "baaa"));
}

TEST_F(TokenizerSanityTest, checkProcessedTokenTypes) {
    vector<string> token_types;
    while(tokenizer->has_next_token()) {
        Token *token = tokenizer->next_token();
        token_types.push_back(token->type->name);
    }
    ASSERT_THAT(token_types, ::testing::ElementsAre("T1", "T1", "T1", "T1", "T1", "T1", "T2", "T1", "T1", "T2"));
}
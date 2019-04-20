//
// Created by mario_hunter on 4/20/19.
//

#include <gtest/gtest.h>
#include <parser/analyzer/PredictiveParser.h>

class ParsingSanityTestSetup : public ::testing::Test {
protected:
    PredictiveParser *parser;
    Production ***pdt;
    unordered_map<string, int> *non_terminal_map;
    unordered_map<string, int> *terminal_map;

    void
    create_data() {
        pdt = new Production **[2];
        for (int i = 0; i < 2; i++) {
            pdt[i] = new Production *[3];
            for (int j = 0; j < 3; j++) {
                pdt[i][j] = NULL;
            }
        }

        Production *prod1 = new Production;
        auto start_symbol =  new GrammarSymbol{ string("S"), NonTerminal};
        prod1->name = start_symbol;
        prod1->is_start_production = true;
        auto vec1 = new vector<GrammarSymbol *>();
        vec1->push_back(new GrammarSymbol{ string("a"), Terminal});
        vec1->push_back(new GrammarSymbol{ string("B"), NonTerminal});
        vec1->push_back(new GrammarSymbol{ string("a"), Terminal});
        auto vec2 = new vector<vector<GrammarSymbol *> *>();
        vec2->push_back(vec1);
        prod1->productions = vec2;

        Production *prod2 = new Production;
        prod2->name = new GrammarSymbol{ string("B"), NonTerminal};
        prod2->is_start_production = false;
        auto vec3 = new vector<GrammarSymbol *>();
        vec3->push_back(new GrammarSymbol{ string("b"), Terminal});
        vec3->push_back(new GrammarSymbol{ string("B"), NonTerminal});
        auto vec4 = new vector<vector<GrammarSymbol *> *>();
        vec4->push_back(vec3);
        prod2->productions = vec4;

        Production *prod3 = new Production;
        prod3->name = new GrammarSymbol{ string("B"), NonTerminal};
        prod3->is_start_production = false;
        prod3->has_epsilon = true;
        auto vec5 = new vector<GrammarSymbol *>();
        vec5->push_back(new GrammarSymbol{"", Terminal, true});
        auto vec6 = new vector<vector<GrammarSymbol *> *>();
        vec6->push_back(vec5);
        prod3->productions = vec6;

        pdt[0][0] = prod1;
        pdt[1][0] = prod3;
        pdt[1][1] = prod2;


        non_terminal_map = new unordered_map<string,int>();
        non_terminal_map->insert(make_pair(string("S"),0));
        non_terminal_map->insert(make_pair(string("B"),1));
        terminal_map = new unordered_map<string,int>();
        terminal_map->insert(make_pair(string("a"),0));
        terminal_map->insert(make_pair(string("b"),1));

        parser = new PredictiveParser(pdt,non_terminal_map,terminal_map,start_symbol);
    }

    void SetUp() override {
        create_data();
    }
};
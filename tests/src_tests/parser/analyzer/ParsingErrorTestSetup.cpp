//
// Created by mario_hunter on 4/20/19.
//

#include <gtest/gtest.h>
#include <parser/analyzer/PredictiveParser.h>

class ParsingErrorTestSetup : public ::testing::Test {
protected:
    PredictiveParser *parser;
    Production ***pdt;
    unordered_map<string, int> *non_terminal_map;
    unordered_map<string, int> *terminal_map;

    void
    create_data() {
        pdt = new Production **[2];
        for (int i = 0; i < 2; i++) {
            pdt[i] = new Production *[6];
            for (int j = 0; j < 6; j++) {
                pdt[i][j] = nullptr;
            }
        }

        Production *prod1 = new Production;
        auto start_symbol =  new GrammarSymbol{ string("S"), NonTerminal};
        prod1->name = start_symbol;
        prod1->is_start_production = true;

        auto vec10 = new vector<GrammarSymbol *>();
        vec10->push_back(new GrammarSymbol{ string("A"), NonTerminal});
        vec10->push_back(new GrammarSymbol{ string("b"), Terminal});
        vec10->push_back(new GrammarSymbol{ string("S"), NonTerminal});
        auto vec1 = new vector<vector<GrammarSymbol *> *>();
        vec1->push_back(vec10);
        prod1->productions = vec1;


        Production *prod2 = new Production;
        prod2->name = start_symbol;
        prod2->is_start_production = true;
        auto vec11 = new vector<GrammarSymbol *>();
        vec11->push_back(new GrammarSymbol{ string("e"), Terminal});
        auto vec3 = new vector<vector<GrammarSymbol *> *>();
        vec3->push_back(vec11);
        prod2->productions =vec3;

        Production *prod3 = new Production;
        prod3->name = start_symbol;
        prod3->is_start_production = true;
        auto vec12 = new vector<GrammarSymbol *>();
        vec12->push_back(new GrammarSymbol{"", Terminal, true});
        auto vec4 = new vector<vector<GrammarSymbol *> *>();
        vec4->push_back(vec12);
        prod3->productions =vec4;

        auto a_symbol = new GrammarSymbol{ string("A"), NonTerminal};
        Production *prod5 = new Production;
        prod5->name = a_symbol;
        prod5->is_start_production = false;
        auto vec30 = new vector<GrammarSymbol *>();
        vec30->push_back(new GrammarSymbol{ string("c"), Terminal});
        vec30->push_back(new GrammarSymbol{ string("A"), NonTerminal});
        vec30->push_back(new GrammarSymbol{ string("d"), Terminal});
        auto vec5 = new vector<vector<GrammarSymbol *> *>();
        vec5->push_back(vec30);
        prod5->productions = vec5;


        Production *prod6 = new Production;
        prod6->name = a_symbol;
        prod6->is_start_production = false;
        auto vec50 = new vector<GrammarSymbol *>();
        vec50->push_back(new GrammarSymbol{ string("a"), Terminal});
        auto vec6 = new vector<vector<GrammarSymbol *> *>();
        vec6->push_back(vec50);
        prod6->productions = vec6;


        Production *prod7 = new Production;
        prod7->name = new GrammarSymbol{ string(""), NonTerminal};
        prod7->is_start_production = false;
        prod7->is_sync = true;
        auto vec7 = new vector<vector<GrammarSymbol *> *>();
        prod7->productions = vec7;

        pdt[0][0] = prod1;
        pdt[0][2] = prod1;
        pdt[0][4] = prod2;
        pdt[0][5] = prod3;
        pdt[1][0] = prod6;
        pdt[1][1] = prod7;
        pdt[1][2] = prod5;
        pdt[1][3] = prod7;


        non_terminal_map = new unordered_map<string,int>();
        non_terminal_map->insert(make_pair(string("S"),0));
        non_terminal_map->insert(make_pair(string("A"),1));
        terminal_map = new unordered_map<string,int>();
        terminal_map->insert(make_pair(string("a"),0));
        terminal_map->insert(make_pair(string("b"),1));
        terminal_map->insert(make_pair(string("c"),2));
        terminal_map->insert(make_pair(string("d"),3));
        terminal_map->insert(make_pair(string("e"),4));
        terminal_map->insert(make_pair("$",5));

        parser = new PredictiveParser(pdt,non_terminal_map,terminal_map,start_symbol);
    }

    void SetUp() override {
        create_data();
    }
};
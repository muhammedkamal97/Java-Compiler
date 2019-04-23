//
// Created by mario_hunter on 4/19/19.
//

#include "ParserConfigInterpreter.h"
#include "ProductionRules.h"


#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <regex>

typedef boost::tokenizer<boost::char_separator<char>>tokenizer;

const regex ParserConfigInterpreter::prod_regex("^#\\s*\\w* = .+$");
const regex ParserConfigInterpreter::terminal_regex("^'.+?'$");
const char* ParserConfigInterpreter::epsilon_string = "\\L";

vector<string> *
ParserConfigInterpreter::getTerminals() {
    return terminals;
}

ParserConfigInterpreter::ParserConfigInterpreter(std::fstream *config, bool cacheable) {
    this->config = config;
    productions_vector = new vector<Production*>;
    terminals = new vector<string>();
}

void
ParserConfigInterpreter::generate_production_rules() {
    string x;
    while(getline(*config, x)) {
        while (config->peek() != '#' && !config->eof()) {
            string y;
            getline(*config, y);
            if (y.length() <= 0) continue;
            x += y;
        }
        if (x.length() <= 0) continue;

        if (regex_match(x, prod_regex))
            parse_prouction(x);
        else {
            // TODO: Handle invalid lines
        }
    }
    rules = new ProductionRules(productions_vector);
}

void
ParserConfigInterpreter::parse_prouction(string line) {
    line = line.substr(1);             // Remove #
    size_t equal_pos = line.find("="); //find location of RHS
    string name = line.substr(0, equal_pos);
    boost::algorithm::trim(name);

    Production* production = new Production(new GrammarSymbol(name, symbol_type::NonTerminal, false), false, false);
    production->productions->push_back(new vector< GrammarSymbol * >);

    line.erase(0,equal_pos+1); //delete everything prior to location found
    boost::algorithm::trim(line);

    boost::char_separator<char> sep(" ", "|");
    tokenizer tokens(line, sep);
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
        string token = *tok_iter;
        if (*tok_iter == "\\") {    // Merge with next character
            tok_iter++;
            token = "\\" + *tok_iter;
        }

        if (token == "|") {
            production->productions->push_back(new vector< GrammarSymbol * >);  // Add new production
        }
        else {
            GrammarSymbol* grammarSymbol;
            if (regex_match(token, terminal_regex)) {
                token = token.substr(1, token.length() - 2);
                grammarSymbol = new GrammarSymbol(token, symbol_type::Terminal);
                if (token == epsilon_string) {
                    production->has_epsilon = true;
                    grammarSymbol->is_epsilon = true;
                    production->productions->pop_back(); //TODO get a more elegant solution
                }else{
                    terminals->push_back(token);
                }
            }
            else {
                grammarSymbol = new GrammarSymbol(token, symbol_type::NonTerminal);
            }

            if(!grammarSymbol->is_epsilon) production->productions->back()->push_back(grammarSymbol);
        }
    }
    productions_vector->push_back(production);
}


ProductionRules *
ParserConfigInterpreter::get_production_rules() {
    return rules;
}

GrammarSymbol *
ParserConfigInterpreter::get_start_symbol() {
    return (rules->production_rules[0])->name;
}

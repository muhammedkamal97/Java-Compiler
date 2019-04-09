//
// Created by mario_hunter on 3/19/19.
//

#include "LexicalConfigInterpreter.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <regex>

typedef boost::tokenizer<boost::char_separator<char>>tokenizer;

const char* LexicalConfigInterpreter::secondary_delimiters = "-[]^$|?*+()\\";
const regex LexicalConfigInterpreter::punctuation_regex("^\\[.*\\]$");
const regex LexicalConfigInterpreter::keywords_regex("^\\{.*\\}$");
const regex LexicalConfigInterpreter::regdef_regex("^\\w+ = .*$");
const regex LexicalConfigInterpreter::regex_regex("^\\w+: .*$");

LexicalConfigInterpreter::LexicalConfigInterpreter(fstream *config, bool cacheable) : config(config) {
    punctuations = new vector<string>;
    keywords = new vector<string>;
    regdefs = new vector<string>;
    regdef_map = new vector<pair<string, vector<string>>>;
    regexes = new vector<string>;
    regex_map = new vector<pair<string, vector<string>>>;
}

void LexicalConfigInterpreter::generate_rules_map() {

    string line;
    while(getline(*config, line)) {
        if (line.length() <= 0) continue;

        if (regex_match(line, punctuation_regex))
            parse_punctations(line);
        else if (regex_match(line, keywords_regex))
            parse_keywords(line);
        else if (regex_match(line, regdef_regex))
            parse_regdef(line);
        else if (regex_match(line, regex_regex))
            parse_regex(line);
        else {
            // TODO: Handle invalid line
        }
    }
}

void LexicalConfigInterpreter::parse_punctations(string line) {
    line = line.substr(1, line.length() - 2);       // Remove surrounding curly braces

    vector<string> v;
    boost::char_separator<char> sep;
    tokenizer tokens(line, sep);
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
        string token = *tok_iter;
        if (*tok_iter == "\\") {    // Merge with next character
            tok_iter++;
            token = "\\" + *tok_iter;
        }
        punctuations->push_back(token);
    }
}

void LexicalConfigInterpreter::parse_keywords(string line) {
    line = line.substr(1, line.length() - 2);       // Remove surrounding brackets

    vector<string> v;
    boost::char_separator<char> sep;
    tokenizer tokens(line, sep);
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
        string token = *tok_iter;
        if (*tok_iter == "\\") {    // Merge with next character
            tok_iter++;
            token = "\\" + *tok_iter;
        }
        keywords->push_back(token);
    }
}

void LexicalConfigInterpreter::parse_regdef(string line) {
    size_t equal_pos = line.find("="); //find location of word
    string name = line.substr(0, equal_pos);
    boost::algorithm::trim(name);

    line.erase(0,equal_pos+1); //delete everything prior to location found
    boost::algorithm::trim(name);

    vector<string> tokens_vector;
    boost::char_separator<char> sep(" ", secondary_delimiters);
    tokenizer tokens(line, sep);
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
        string token = *tok_iter;
        if (*tok_iter == "\\") {    // Merge with next character
            tok_iter++;
            token = "\\" + *tok_iter;
        }
        tokens_vector.push_back(token);
    }
    regdefs->push_back(name);
    regdef_map->emplace_back(pair<string, vector<string>>(name, tokens_vector));
}


void LexicalConfigInterpreter::parse_regex(string line) {
    size_t equal_pos = line.find(":"); //find location of word
    string name = line.substr(0, equal_pos);
    boost::algorithm::trim(name);

    line.erase(0,equal_pos+1); //delete everything prior to location found
    boost::algorithm::trim(name);

    vector<string> tokens_vector;
    boost::char_separator<char> sep(" ", secondary_delimiters);
    tokenizer tokens(line, sep);
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
        string token = *tok_iter;
        if (*tok_iter == "\\") {    // Merge backslash with the espcaed character
            tok_iter++;
            token = "\\" + *tok_iter;
        }
        tokens_vector.push_back(token);
    }
    regexes->push_back(name);
    regex_map->emplace_back(pair<string, vector<string>>(name, tokens_vector));
}
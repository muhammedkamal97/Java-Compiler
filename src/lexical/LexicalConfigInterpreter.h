//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_LEXICALCONFIGINTERPRETER_H
#define PROJECT_LEXICALCONFIGINTERPRETER_H

#include <map>
#include <vector>
#include <string>
#include <regex>
#include <vector>

using namespace std;

class LexicalConfigInterpreter {
private:
    map<string, vector<string>> *lexical_rules;
    fstream *config;

    vector<string>* punctuations;
    vector<string>* keywords;
    vector<string>* regdefs;
    // Maps regular definition by its name in regdefs to its sequence of symbols
    map<string, vector<string>>* regdef_map;
    vector<string>* regexes;
    // Maps regular expression by its token name in regexes to its sequence of symbols
    map<string, vector<string>>* regex_map;

    static const char* secondary_delimiters;
    static const regex punctuation_regex;
    static const regex keywords_regex;
    static const regex regdef_regex;
    static const regex regex_regex;

    void parse_punctations(string line);
    void parse_keywords(string line);
    void parse_regdef(string line);
    void parse_regex(string line);
public:
    LexicalConfigInterpreter(fstream *config, bool cacheable = false);

    void generate_rules_map();

    vector<string>* get_punctations() { return punctuations; };
    vector<string>* get_keywords() { return keywords; };
    vector<string>* get_regdefs() { return regdefs; };
    map<string, vector<string>>* get_regdef_map() { return regdef_map; };
    vector<string>* get_regexes() { return regexes; };
    map<string, vector<string>>* get_regex_map() { return regex_map; };

};


#endif //PROJECT_LEXICALCONFIGINTERPRETER_H

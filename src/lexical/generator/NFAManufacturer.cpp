//
// Created by Muhammed on 3/24/2019.
//

#include "NFAManufacturer.h"



void NFAManufacturer::NFAManufacturers(vector<pair<string,vector<string>>> expressions,
        vector<pair<string,vector<string>>> definations,
        vector<string> key_words,
        vector<string> punctuations) {

    this->punctuations = punctuations;
    transition_array = new vector<set<int>*>();
    definations.resize(definations.size());
    expressions.resize(expressions.size());
    NFA* def_nfa;
    auto tokens_priorities_map = new map<string, pair<int, int>>();
    int tokens_priority = 0;
    for (int i = 0; i < definations.size(); ++i) {
        string def = definations[i].first;
        vector<string> regex = regex_to_postfix(definations[i].second);
        this->definitions[def] = regex;
    }

    vector<NFA *> nfa_expressions;
    NFA *temp;
    tokens_vec = new vector<TokenType *>();


    for (int i = 0; i < key_words.size(); ++i) {
        string curr = key_words[i];
        temp = new NFA(&curr);
        temp->ending->accepted_pattern = key_words[i];

        auto token = new TokenType{key_words[i], true}; //TODO keywords in symbol table?
        temp->ending->accepted_token_type = token;
        tokens_vec->emplace_back(token);
        tokens_priorities_map->insert(make_pair(key_words[i], make_pair(tokens_priority, tokens_priority)));
        tokens_priority++;

        nfa_expressions.push_back(temp);
    }

    for (int i = 0; i < punctuations.size(); ++i) {
        string curr = punctuations[i];
        temp = new NFA(&curr);
        temp->ending->accepted_pattern = punctuations[i];

        auto token = new TokenType{punctuations[i], false};
        temp->ending->accepted_token_type = token;
        tokens_vec->emplace_back(token);
        tokens_priorities_map->insert(make_pair(punctuations[i], make_pair(tokens_priority, tokens_priority)));
        tokens_priority++;

        nfa_expressions.push_back(temp);
    }


    for (int i = 0; i < expressions.size(); ++i) {
        vector<string> regex = expressions[i].second;
        temp = evaluate_postfix(regex_to_postfix(regex));
        temp->ending->accepted_pattern = expressions[i].first;

        auto token = new TokenType{expressions[i].first, expressions[i].first == "id"}; //TODO keywords in symbol table?
        temp->ending->accepted_token_type = token;
        tokens_vec->emplace_back(token);
        tokens_priorities_map->insert(make_pair(expressions[i].first, make_pair(tokens_priority, tokens_priority)));
        tokens_priority++;

        nfa_expressions.push_back(temp);
    }

    nfa = NFA::compine(nfa_expressions);

    transition_table = nfa->get_trasition_array(tokens_priorities_map);

    //for (int i = 0; i < transition_table.size(); i++) {
      //  transition_array->push_back(&transition_table[i][0]);
    //}

//    for (int i = 0; i < transition_table.size() ; ++i) {
//        cout<< "state "<< i<<":";
//        for (int j = 0; j < transition_table[i].size() ; ++j) {
//            if(!transition_table[i][j].empty()){
//                printf(" %c ",j);
//                if(j < 0) printf("error");
//                cout<<"{ ";
//                for (auto k : transition_table[i][j]) {
//                    cout<< k<< " ";
//                }
//                cout<<"}";
//            }
//        }
//        cout<<endl;
//    }

}

void
NFAManufacturer::generate_diagram() {

}


NFA *
NFAManufacturer::evaluate_postfix(vector<string> postfix) {
    //get first definition or character
    stack<NFA*> eval;
    NFA* t;
    NFA* s;
    for (int i = 0; i < postfix.size(); ++i) {
        if (is_operator(postfix[i])) {
            switch (postfix[i][0]) {
                case '*':
                    t = eval.top();
                    eval.pop();
                    eval.push(NFA::kleene_clouser(t));
                    break;
                case '+':
                    t = eval.top();
                    eval.pop();
                    eval.push(NFA::positive_clouser(t));
                    break;
                case '|':
                    t = eval.top();
                    eval.pop();
                    s = eval.top();
                    eval.pop();
                    eval.push(NFA::union_(t, s));
                    break;
                case '$':
                    t = eval.top();
                    eval.pop();
                    s = eval.top();
                    eval.pop();
                    eval.push(NFA::concatinate(s, t));
                    break;
                case '-':
                    t = eval.top();
                    eval.pop();
                    s = eval.top();
                    eval.pop();
                    eval.push(NFA::range(s, t));
                    break;
            }
        } else {
            //create NFA for character and definitions
            if (is_definition(postfix[i])) {
                eval.push(evaluate_postfix(this->definitions[postfix[i]]));
            } else {
                eval.push(new NFA(&postfix[i]));
            }
        }
    }
    return eval.top();
}


vector<string>
NFAManufacturer::regex_to_postfix(vector<string> expression) {
    vector<string> postfix;
    stack<string> operations;
    vector<string> temp;
    temp.push_back(expression[0]);
    for (int j = 1; j < expression.size(); ++j) {
        if (!is_operator(expression[j - 1]) && !is_operator(expression[j])) {
            temp.push_back("$");
        }else if(!is_operator(expression[j - 1]) && expression[j] == "("){
            temp.push_back("$");
        }else if(expression[j-1] ==")" && !is_operator(expression[j])){
            temp.push_back("$");
        }else if(unary_operator(expression[j - 1])&&!is_operator(expression[j])){
            temp.push_back("$");
        }
        temp.push_back(expression[j]);
    }

    for (int i = 0; i < temp.size(); ++i) {
        if (is_operator(temp[i])) {
            switch (temp[i][0]) {
                case '(':
                    operations.push(temp[i]);
                    break;
                case ')':
                    while (!operations.empty() && operations.top() != "(") {
                        postfix.push_back(operations.top());
                        operations.pop();
                    }
                    operations.pop();
                    break;
                case '-':
                    if (check_range(i, temp)) {
                        postfix.push_back(temp[i + 1]);
                        postfix.push_back(temp[i]);
                        i++;
                    }
                    break;
                default:
                    while (!operations.empty()) {
                        string op = operations.top();
                        if (operator_priority(op[0]) >= operator_priority(temp[i][0])) {
                            postfix.push_back(op);
                            operations.pop();
                            continue;
                        }
                        break;
                    }
                    operations.push(temp[i]);
            }
        } else {
            postfix.push_back(temp[i]);
        }
    }
    while (!operations.empty()) {
        postfix.push_back(operations.top());
        operations.pop();
    }
    return postfix;
}


bool
NFAManufacturer::is_definition(string str) {
    return definitions.find(str) != definitions.end();
}

bool
NFAManufacturer::is_operator(string str) {
    return str == "+" || str == "*" ||
           str == "|" ||
           str == "(" || str == ")" ||
           str == "-" || str == "$"; // "$" indication for concatenation
}

bool NFAManufacturer::unary_operator(string op) {
    return op == "+" || op == "*";
}


int
NFAManufacturer::operator_priority(char c) {
    switch (c) {
        case '*':
        case '+':
            return 3;
        case '$':
            return 2;
        case '|':
            return 1;
        default:
            return 0;
    }
}

bool
NFAManufacturer::check_range(int i, vector<string> temp) {
    return i > 0 && i < (temp.size() - 1) &&
           !is_operator(temp[i - 1]) && !is_operator(temp[i + 1]) &&
           !is_definition(temp[i - 1]) && !is_definition(temp[i + 1]);
}


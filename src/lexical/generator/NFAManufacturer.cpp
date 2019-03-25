//
// Created by Muhammed on 3/24/2019.
//

#include "NFAManufacturer.h"

NFAManufacturer::NFAManufacturer(map<string, vector<string>> rules) {}

void NFAManufacturer::generate_diagram() {}


NFA* NFAManufacturer::evaluate_postfix(vector<string> postfix) {
    //get first definition or character
    stack<NFA*> eval;
    stack<char> range;
    NFA* t;
    NFA* s;
    for (int i = 0; i < postfix.size(); ++i) {
        if(is_operator(postfix[i])){
            switch(postfix[i][0]){
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
                    eval.push(NFA::union_(t,s));
                    break;
                case '$':
                    t = eval.top();
                    eval.pop();
                    s = eval.top();
                    eval.pop();
                    eval.push(NFA::concatinate(s,t));
                    break;
                case '-':
                    t = eval.top();eval.pop();
                    s = eval.top();eval.pop();
                    eval.push(NFA::range(s,t));
                    break;
            }
        }else{
            //create NFA for character and definitions
            if(is_definition(postfix[i])){
                eval.push(this->definitions[postfix[i]]);
            }else{
                eval.push(new NFA(postfix[i]));
            }
        }
    }
    return eval.top();
}




vector<string> NFAManufacturer::regex_to_postfix(vector<string> expression) {
    vector<string> postfix;
    stack<string> operations;
    vector<string> temp;
    temp.push_back(expression[0]);
    for (int j = 1; j < expression.size(); ++j) {
        if(!is_operator(expression[j-1]) && !is_operator(expression[j])){
            temp.push_back("$");
        }
        temp.push_back(expression[j]);
    }

    for (int i = 0; i < temp.size(); ++i) {
        if(is_operator(temp[i])){
            switch (temp[i][0]){
                case '(':operations.push(temp[i]);break;
                case ')':
                    while(!operations.empty() && operations.top() != "("){
                        postfix.push_back(operations.top());
                        operations.pop();
                    }
                    operations.pop();
                    break;
                case '-':
                    if(check_range(i,temp)){
                        postfix.push_back(temp[i+1]);
                        postfix.push_back(temp[i]);
                        i++;
                    }
                    break;
                default:
                    while(!operations.empty()){
                        string op = operations.top();
                        if(operator_priority(op[0]) >= operator_priority(temp[i][0])){
                            postfix.push_back(op);
                            operations.pop();
                            continue;
                        }
                        break;
                    }
                    operations.push(temp[i]);
            }
        }else {
            postfix.push_back(temp[i]);
        }
    }
    while(!operations.empty())
    {
        postfix.push_back(operations.top());
        operations.pop();
    }
    return postfix;
}


bool NFAManufacturer::is_definition(string str) {
    return definitions.find(str) != definitions.end();
}

bool NFAManufacturer::is_operator(string str) {
    return  str == "+"|| str == "*" ||
            str == "|" ||
            str == "(" || str == ")" ||
            str == "-" || str == "$"; // "$" indication for concatenation
}


int NFAManufacturer::operator_priority(char c){
    switch(c){
        case '*':
        case '+': return 3;
        case '$': return 2;
        case '|': return 1;
        default:  return 0;
    }
}

bool NFAManufacturer::check_range(int i, vector<string> temp){
    return i > 0 && i < (temp.size() - 1) &&
           !is_operator(temp[i-1]) && !is_operator(temp[i+1]) &&
           !is_definition(temp[i-1]) && !is_definition(temp[i+1]);
}


//
// Created by Muhammed on 3/24/2019.
//

#include "NFA.h"

static string epsilon = "";

NFA::NFA(char c) {
    NFAstate* start = new NFAstate(false);
    NFAstate* end = new NFAstate(true);
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    start->make_transition(end,s);
    this->starting = start;
    this->ending = end;
    this->accepted.insert(end);
    this->all_states.insert(start);
    this->all_states.insert(end);
}


NFA::NFA(NFAstate *starting, NFAstate *ending) {
    this->starting = starting;
    this->ending = ending;
}

NFA* NFA::concatinate(NFA *s1, NFA *s2) {
    s1->ending->accept = false;

    s1->ending->make_transition(s2->starting,epsilon);

    NFA* result = new NFA(s1->starting,s2->ending);
    result->all_states.insert(s1->all_states.begin(),s1->all_states.end());
    result->all_states.insert(s2->all_states.begin(),s2->all_states.end());
    result->accepted.insert(s2->ending);

    return result;
}

NFA* NFA::union_(NFA *s1, NFA *s2) {
    s1->ending->accept = false;
    s2->ending->accept = false;

    NFAstate* start = new NFAstate(false);
    NFAstate* end = new NFAstate(true);

    start->make_transition(s1->starting,epsilon);
    start->make_transition(s2->starting,epsilon);

    s1->ending->make_transition(end,epsilon);
    s2->ending->make_transition(end,epsilon);

    NFA* result = new NFA(start,end);
    result->all_states.insert(s1->all_states.begin(),s1->all_states.end());
    result->all_states.insert(s2->all_states.begin(),s2->all_states.end());
    result->all_states.insert(start);
    result->all_states.insert(end);
    result->accepted.insert(end);

    return result;
}


NFA* NFA::kleene_clouser(NFA *s) {
    s->ending->accept = false;
    NFAstate* start = new NFAstate(false);
    NFAstate* end = new NFAstate(true);

    start->make_transition(s->starting,epsilon);
    start->make_transition(end,epsilon);
    s->ending->make_transition(end,epsilon);
    s->ending->make_transition(start,epsilon);

    NFA* result = new NFA(start,end);
    result->all_states.insert(s->all_states.begin(),s->all_states.end());
    result->all_states.insert(start);
    result->all_states.insert(end);
    result->accepted.insert(end);

    return result;
}

NFA* NFA::positive_clouser(NFA *s) {
    return concatinate(s,kleene_clouser(s));
}

NFA* NFA::range(char c1, char c2) {
    NFAstate* start = new NFAstate(false);
    NFAstate* end = new NFAstate(true);
    for (char i = c1; i <= c2; ++i) {
        stringstream ss;
        string s;
        char c = i;
        ss << c;
        ss >> s;
        start->make_transition(end,s);
    }
    NFA* result = new NFA(start,end);
    result->all_states.insert(start);
    result->all_states.insert(end);
    result->accepted.insert(end);

    return result;
}

vector<vector<set<int>>> NFA::get_trasition_array() {
    transition_array.resize(all_states.size());
    for (int i = 0; i < transition_array.size(); ++i) {
        transition_array[i].resize(260);
    }

    label_nfa(starting);
    set<NFAstate*>::iterator it1 = all_states.begin();
    int index = 0;
    char input;
    while(it1 != all_states.end()){
        index = (*it1)->label;
        for (int i = 0; i < (*it1)->transition.size(); ++i) {
            input = (*it1)->transition[i].first[0];
            transition_array[index][input].insert((*it1)->transition[i].second->label);
        }
        it1++;
    }
    return transition_array;
}

void NFA::label_nfa(NFAstate* state) {
    set<NFAstate*>::iterator it = all_states.begin();
    state_number = 0;
    while(it != all_states.end()){
        if((*it)->label == -1) {
            (*it)->label = state_number++;
        }
        it++;
    }
}
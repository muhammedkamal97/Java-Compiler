//
// Created by Muhammed on 3/24/2019.
//

#include "NFA.h"

static string epsilon = "";

NFA::NFA(char c) {
    NFAstate* start = new NFAstate(false);
    NFAstate* end = new NFAstate(true);
    start->make_transition(end,string(1,c));
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
        start->make_transition(end,string(1,i));
    }
    NFA* result = new NFA(start,end);
    result->all_states.insert(start);
    result->all_states.insert(end);
    result->accepted.insert(end);

    return result;
}

vector<vector<set<int>>> NFA::get_trasition_array() {
    set<NFAstate*>::iterator it1 = this->all_states.begin();
    vector<vector<set<int>>> result(this->all_states.size());
    for (int i = 0; i < result.size() ; ++i) {
        result[i].resize(260);
    }
    int index = 0;
    while(it1 != this->all_states.end()){
        map<string,int>::iterator it2 = (*it1)->transition.begin();
        while(it2 != (*it1)->transition.end()){
            int input = it2->first[0];
            result[index][input].insert(it2->second);
            it2++;
        }
        it1++;
        index++;
    }
    return result;
}

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

NFA::NFA(string word) {
    this->starting = new NFAstate(false);
    NFAstate* prev = starting;
    NFAstate* curr;
    all_states.insert(starting);
    for (int i = 0; i < word.size() ; ++i) {
        if(word[i] != '\\') {
            curr = new NFAstate(false);
            all_states.insert(curr);
            stringstream ss;
            string s;
            ss << word[i];
            ss >> s;
            prev->make_transition(curr, s);
            prev = curr;
        }
    }
    curr->accept = true;
    accepted.insert(curr);
    this->ending = curr;
}



NFA::NFA(NFAstate *starting, NFAstate *ending) {
    this->starting = starting;
    this->ending = ending;
    all_states.insert(starting);

    if (ending != nullptr) {
        all_states.insert(ending);
        accepted.insert(ending);
    }

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

NFA* NFA::range(NFA* n1, NFA*n2) {
    NFAstate* start = new NFAstate(false);
    NFAstate* end = new NFAstate(true);
    char c1 = n1->starting->transition[0].first[0];
    char c2 = n2->starting->transition[0].first[0];
    for(char c = c1; c <= c2;c++){
        stringstream ss;
        string s;
        ss << c;
        ss >> s;
        start->make_transition(end,s);
    }
    NFA* result = new NFA(start,end);

    return result;
}



NFA* NFA::compine(vector<NFA *> patterns) {
    NFAstate* start = new NFAstate(false);
    NFA* result = new NFA(start, nullptr);
    for (int i = 0; i < patterns.size() ; ++i) {
        start->make_transition(patterns[i]->starting,epsilon);
        result->all_states.insert(patterns[i]->all_states.begin(),patterns[i]->all_states.end());
        result->accepted.insert(patterns[i]->accepted.begin(),patterns[i]->accepted.end());
    }
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
    MetaData meta = {make_pair(all_states.size(),260),
                     0,0,0,260};
    map<int,int> accepted_patterens;
    it1 = accepted.begin();
    while(it1!=accepted.end()){
        //accepted_patterens[(*it1)->label] = index;//TODO index of the tokenType in the array of Token.
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
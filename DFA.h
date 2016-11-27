//
// Created by 王若璇 on 16/11/20.
//

#ifndef REGEX_DFA_H
#define REGEX_DFA_H

#include <set>
#include <iostream>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include "NFA.h"
#include "Transition.h"

using namespace std;

class DFAtransition;
class DFAstate {
public:
    static int tolDFAstateNum;
    int DFAstateID;
    set<char> charSet;
    vector<DFAtransition*> nextDFAstates;
    bool matched;
private:
    set<State *> stateSet;
public:



    const set<State *> &getStateSet() const {
        return stateSet;
    }

    void setStateSet(const set<State *> &stateSet) {
        DFAstate::stateSet = stateSet;
    }


public:
    DFAstate() {
        stateSet.clear();
        matched = false;
        charSet.clear();
        tolDFAstateNum++;
        nextDFAstates.clear();

    }
    ///@todo to think the relationship between default constructor and user defined constructor
    DFAstate(int DFAstateID) : DFAstateID(DFAstateID) {
        stateSet.clear();
        charSet.clear();
        nextDFAstates.clear();
        tolDFAstateNum++;

    }
    void addState(State* state){
        stateSet.insert(state);
    }
    void addDFAtransition(DFAtransition* transition){
        nextDFAstates.push_back(transition);
    }
    bool empty(){
        return stateSet.empty();
    }
};

class DFAgraph {

public:
    void init() {

    }

public:


};

class DFAtransition {
public:
    static int tolDFAtransitionNum;

public:
    int DFAtransitionID;
    char inaccept;
    DFAstate* nextDFAstate;

public:
    DFAtransition(int DFAtransitionID,char inaccept,DFAstate* next):
            DFAtransitionID(DFAtransitionID),inaccept(inaccept),nextDFAstate(next){}

};

class DFA {
private:
    NFA nfa;
    multimap<pair<char,State*>,State*> NFAmove;
    DFAgraph dfa;
    set<DFAstate*> DFAstateSet;
    string regex;
    DFAstate* initRoot;
    DFAstate* final;
private:
    void initNFAmove();
    void findFinal();
    set<State*> nfaMove(set<State*> states,char inputChar);
    set<State*> nfaMove(State* state,char inputChar);
    void NFAinit();
    DFAstate *eClosure(State *state);
    DFAstate *eClosure(set<State*> states);

public:
    explicit DFA(){}
    explicit DFA(string string):regex(string){
        init(string);
    }
    void init(const string& regex);
    void subsetConstruction();
    void showDFA();


};


#endif //REGEX_DFA_H

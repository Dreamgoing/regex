//
// Created by 王若璇 on 16/11/20.
//

#ifndef REGEX_DFA_H
#define REGEX_DFA_H

//#define DEBUG_SHOW_ECLOSURE_CHANGE

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
class DFAstate;
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
class DFAstate {
public:
    static int tolDFAstateNum;
    int DFAstateID;
    set<char> charSet;
    vector<DFAtransition*> nextDFAstates;
    bool matched;
    bool start;
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
    ~DFAstate(){
        tolDFAstateNum--;
        tolDFAstateNum = max(0,tolDFAstateNum);
    }
    bool exist(State* state){
        return stateSet.find(state)!=stateSet.end();
    }
    void addState(State* state){
        stateSet.insert(state);
    }
    void addDFAtransition(DFAtransition* transition){
        nextDFAstates.push_back(transition);
    }
    void showDetail(){
        cout<<"DFAstate ID "<<this->DFAstateID;
        if(start){
            cout<<" <initState> ";
        }
        if(matched){
            cout<<" <endState> ";
        }
        cout<<'\n'<<"nfa states: [ ";
        for(auto it:stateSet){
            cout<<it->stateID<<" ";
        }
        cout<<"] "<<endl;
        for(auto it:nextDFAstates){
            cout<<"dfaState "<<DFAstateID<<" => "<<it->inaccept<<" => "<<it->nextDFAstate->DFAstateID<<endl;
            cout<<'\n';
        }
        cout<<'\n';
    }
    bool empty(){
        return stateSet.empty();
    }

    bool operator < (const DFAstate& lhs)const{
        return DFAstateID<lhs.DFAstateID;
    }
    bool operator < (DFAstate* lhs)const{
        return this->DFAstateID<lhs->DFAstateID;
    }
    bool operator == (const DFAstate& lhs)const{
        if(this->getStateSet().size()!=lhs.getStateSet().size()){
            return false;
        }
        vector<int> tmplhs;
        tmplhs.clear();
        for(auto it:lhs.getStateSet()){
            tmplhs.push_back(it->stateID);
        }
        vector<int> tmpthis;
        tmpthis.clear();
        for(auto it:this->getStateSet()){
            tmpthis.push_back(it->stateID);
        }
        sort(tmplhs.begin(),tmplhs.end());
        sort(tmpthis.begin(),tmpthis.end());
        return tmplhs==tmpthis;
        ///@todo use vector operator ==

    }
};

class DFAgraph {

public:
    void init() {

    }

public:


};



class DFA {
private:
    NFA nfa;
public:
    const NFA &getNfa() const;

    void setNfa(const NFA &nfa);

    const multimap<pair<char, State *>, State *> &getNFAmove() const;

    void setNFAmove(const multimap<pair<char, State *>, State *> &NFAmove);

    const set<DFAstate *> &getDFAstateSet() const;

    void setDFAstateSet(const set<DFAstate *> &DFAstateSet);

    const string &getRegex() const;

    void setRegex(const string &regex);

    DFAstate *getInitRoot() const;

    void setInitRoot(DFAstate *initRoot);

    DFAstate *getFinal() const;

    void setFinal(DFAstate *final) {
        this->final = final;
    }


private:
    multimap<pair<char,State*>,State*> NFAmove;
//    DFAgraph dfa;
    set<DFAstate*> DFAstateSet;
    vector<vector<int> >DFAIDset;
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
    bool lesser(State* lhs,State* rhs);
    bool existDFAstate(DFAstate* rhs);
    DFAstate* solveEclosure(DFAstate* dfAstate);


public:
    explicit DFA(){}
    explicit DFA(string string):regex(string){
        init(string);
    }
    void init(const string& regex);
    void subsetConstruction();
    void minizeDFA();
    void showDFA();
    void cleanUp();


};


#endif //REGEX_DFA_H

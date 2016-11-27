//
// Created by 王若璇 on 16/11/20.
//

#include "DFA.h"

///@note initNFAmove need to be changed.
void DFA::initNFAmove() {
    NFAmove.clear();
    const int max_n = 110000;
    bool vis[max_n] = {0};
    queue<State *> stateQueue;
    stateQueue.push(nfa.getInitRoot());
    while (!stateQueue.empty()) {
        State *now = stateQueue.front();
        stateQueue.pop();
        if (!vis[now->stateID]) {
            vis[now->stateID] = true;
            for (auto to:now->nextStates) {
                NFAmove.insert(make_pair(make_pair(to->inAccept,now),to));
                stateQueue.push(to->nextState);
            }
        }
    }
}

void DFA::NFAinit() {
    ///@todo initNFA before DFA

}

void DFA::subsetConstruction() {
    dfa.init();
    DFAstate* now = eClosure(nfa.getInitRoot());
    ///get DFA initRoot.
    initRoot = now;
    DFAstateSet.insert(now);
    DFAstate* nextState;
    queue<DFAstate*> DFAstateQueue;
    const int max_n = 110000;
    bool vis[max_n]={0};
    DFAstateQueue.push(now);
    while (!DFAstateQueue.empty()){
        now = DFAstateQueue.front();
        DFAstateQueue.pop();
        if(!vis[now->DFAstateID]){
            vis[now->DFAstateID] = true;
            for(auto c:nfa.getCharSet()){
                nextState = eClosure(nfaMove(now->getStateSet(),c));
                if(!nextState->empty()&&DFAstateSet.find(nextState)==DFAstateSet.end()){
                    DFAstateSet.insert(nextState);
                    DFAstateQueue.push(nextState);
                }

                ///@note add an edge from now to nextState (DFAstate).
                ///@bug nextState is empty.
                now->addDFAtransition(new DFAtransition(DFAtransition::tolDFAtransitionNum,c,nextState));
            }
        }
    }
    findFinal();




}

DFAstate *DFA::eClosure(State *state) {
    DFAstate *res = new DFAstate(DFAstate::tolDFAstateNum);
    for(auto it:state->nextStates){
        if(it->inAccept=='~'){
            res->addState(it->nextState);
        }
    }
    return res;
}

DFAstate *DFA::eClosure(set<State *> states) {
    DFAstate *res = new DFAstate(DFAstate::tolDFAstateNum);
    for(auto itState:states){
        for(auto itNext:itState->nextStates){
            if(itNext->inAccept=='~'){
                res->addState(itNext->nextState);
            }
        }
    }
    return res;

}

set<State *> DFA::nfaMove(set<State *> states, char inputChar) {
    set<State*> res;
    res.clear();
    for(auto it:states){
        set<State*> tmpSet = nfaMove(it,inputChar);
        set_union(res.begin(),res.end(),tmpSet.begin(),tmpSet.end(),res);
    }
    return res;
}

set<State *> DFA::nfaMove(State *state, char inputChar) {
    set<State*> res;
    res = {NFAmove.find(make_pair(char,state))};
    return res;
}

void DFA::init(const string& regex) {
    nfa.init();
    nfa.regExToPostfix(regex);
    this->subsetConstruction();
}

void DFA::showDFA() {
    ///@todo to finish show graph function.

}

void DFA::findFinal() {
    for(auto it:DFAstateSet){
        for(auto subIt:it->getStateSet()){
            if(subIt->matched){
                it->matched = true;
                final = it;
                return;
            }
        }
    }
}



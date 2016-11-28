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
                NFAmove.insert({make_pair(to->inAccept,now),to->nextState});
            }
        }
    }
}

void DFA::NFAinit() {
    ///@todo initNFA before DFA
}

void DFA::subsetConstruction() {
    ///@not not dfa.init()
    //dfa.init();

    ///@note nfa.initRoot != nullptr
    assert(nfa.getInitRoot()!= nullptr);
    DFAstate* now = eClosure(nfa.getInitRoot());
   // now->showDetail();
    ///get DFA initRoot.
    initRoot = now;
    initRoot->start = true;
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
                if(c=='~')
                    continue;
                //cout<<c<<" ";
                nextState = eClosure(nfaMove(now->getStateSet(),c));
                ///nextState->showDetail();
                if(!nextState->empty()&&DFAstateSet.find(nextState)==DFAstateSet.end()){
                    DFAstateSet.insert(nextState);
                    DFAstateQueue.push(nextState);
                }

                ///@note add an edge from now to nextState (DFAstate).
                ///@bug nextState is empty.
                if(!nextState->empty()){
                    now->addDFAtransition(new DFAtransition(DFAtransition::tolDFAtransitionNum,c,nextState));
                } else{
                    delete nextState;

                }

            }
        }
    }
    findFinal();


}

DFAstate *DFA::eClosure(State *state) {
    DFAstate *res = new DFAstate(DFAstate::tolDFAstateNum);
    for(auto it:state->nextStates){
        //it->showDetail();
        if(it->inAccept=='~'){
            res->addState(it->nextState);
        }
    }
    res->addState(state);
    return res;
}

DFAstate *DFA::eClosure(set<State *> states) {
    DFAstate *res = new DFAstate(DFAstate::tolDFAstateNum);
    for(auto itState:states){
        res->addState(itState);
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
    //cout<<inputChar<<endl;
    for(auto it:states){
        set<State*> tmpSet = nfaMove(it,inputChar);
        ///@bug set_union isn't ok
        for(auto subit:tmpSet){
            res.insert(subit);
        }
    }
    //assert(res.size()!=0);
    return res;
}

set<State *> DFA::nfaMove(State *state, char inputChar) {
    set<State*> res;
    res.clear();
    for(auto it:state->nextStates){
        if(it->inAccept==inputChar){
            res.insert(it->nextState);
        }
    }
    return res;
}

void DFA::init(const string& regex) {
    DFAstate::tolDFAstateNum = 0;
    nfa.init();
    nfa.regExToPostfix(regex);
    nfa.ThompsonNFA();
    //this->subsetConstruction();
}

void DFA::showDFA() {
    ///@note maxSize is 11000
    const int max_n = 11000;
    bool vis[max_n] = {0};
    queue<DFAstate*> DFAqueue;
    while (!DFAqueue.empty()){
        DFAqueue.pop();
    }
    DFAqueue.push(initRoot);
    while (!DFAqueue.empty()){
        DFAstate* now = DFAqueue.front();
        DFAqueue.pop();
        if(!vis[now->DFAstateID]){
            vis[now->DFAstateID] = true;
            now->showDetail();
            for(auto it:now->nextDFAstates){
                DFAqueue.push(it->nextDFAstate);
            }
        }
    }

}

void DFA::findFinal() {
    for(auto it:DFAstateSet){
        for(auto subIt:it->getStateSet()){
            if(subIt->matched){
                it->matched = true;
                break;
            }
        }
    }
}

const NFA &DFA::getNfa() const {
    return nfa;
}

void DFA::setNfa(const NFA &nfa) {
    DFA::nfa = nfa;
}

const multimap<pair<char, State *>, State *> &DFA::getNFAmove() const {
    return NFAmove;
}

void DFA::setNFAmove(const multimap<pair<char, State *>, State *> &NFAmove) {
    DFA::NFAmove = NFAmove;
}

const set<DFAstate *> &DFA::getDFAstateSet() const {
    return DFAstateSet;
}

void DFA::setDFAstateSet(const set<DFAstate *> &DFAstateSet) {
    DFA::DFAstateSet = DFAstateSet;
}

const string &DFA::getRegex() const {
    return regex;
}

void DFA::setRegex(const string &regex) {
    DFA::regex = regex;
}

DFAstate *DFA::getInitRoot() const {
    return initRoot;
}

void DFA::setInitRoot(DFAstate *initRoot) {
    DFA::initRoot = initRoot;
}

DFAstate *DFA::getFinal() const {
    return final;
}

bool DFA::lesser(State *lhs, State *rhs) {
    return lhs->stateID<rhs->stateID;
}



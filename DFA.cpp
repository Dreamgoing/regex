//
// Created by 王若璇 on 16/11/20.
//

#include "DFA.h"

//@note initNFAmove need to be changed.
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

///@note set<pointer> use find don't work well.
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
                nextState = eClosure(nfaMove(now->getStateSet(),c));
                nextState = solveEclosure(nextState);
#ifdef DEBUG_SHOW_ECLOSURE_CHANGE
                //cout<<c<<" ";
                cerr<<"debug ";
                now->showDetail();
                nextState->showDetail();
                cout<<DFAstateSet.size();
#endif
                if(!nextState->empty()&&!existDFAstate(nextState)){
                    DFAstateSet.insert(nextState);
                    //cout<<"ok"<<endl;
//                    assert(existDFAstate(nextState));
//                    assert(DFAstateSet.find(nextState)!=DFAstateSet.end());
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
    queue<State*> stateQueue;
    stateQueue.push(state);
    State* now;
    while (!stateQueue.empty()){
        now = stateQueue.front();
        stateQueue.pop();
        if(!res->exist(now)){
            res->addState(now);
            for(auto it:now->nextStates){
                if(it->inAccept=='~'){
                    stateQueue.push(it->nextState);
                }
            }
        }
    }
    return res;
}

///use dfs to find all eClosure.
DFAstate *DFA::eClosure(set<State *> states) {
    DFAstate *res = new DFAstate(DFAstate::tolDFAstateNum);
    queue<State*> stateQueue;
    for(auto it:states){
        stateQueue.push(it);
    }
    State* now;
    while (!stateQueue.empty()){
        now = stateQueue.front();
        stateQueue.pop();
        if(!res->exist(now)){
            //cout<<"ok"<<endl;
            res->addState(now);
            for(auto it:now->nextStates){
                if(it->inAccept=='~'){
                    stateQueue.push(it->nextState);
                }
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
    DFAIDset.clear();
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

///@parblock setter and gettter

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

///@endparblock

bool DFA::lesser(State *lhs, State *rhs) {
    return lhs->stateID<rhs->stateID;
}


/**@brief use Hopcroft's Algorithm
 * Merge states if at all possible.
 * @parm none
 * @note Partitioning a set : breaks the set into non-overlapping subsets.
 */

/**@brief
 * 1. Partition it
 *      + Final State
 *      + All Other State
 * 2. Repeatedly "refine" the partioning.
 *      + Two states will be placed in different groups,if they can be "distinguished".
 * 3. Repeat until no group contains states that can be distinguished.
 * 4. Each group in the partitioning becomes one state in a newly constucted DFA.
 *
 *
 */
void DFA::minizeDFA() {
    ///@todo implement this function

}

bool DFA::existDFAstate(DFAstate *rhs) {
    vector<int> rhsIDstates;
    rhsIDstates.clear();
    for(auto it:rhs->getStateSet()){
        rhsIDstates.push_back(it->stateID);
    }
    for(auto it:DFAIDset){
        if(it==rhsIDstates){
            return true;
        }
    }
    DFAIDset.push_back(rhsIDstates);
    return false;
}

DFAstate* DFA::solveEclosure(DFAstate *dfAstate) {
    for(auto it:DFAstateSet){
        if(*it==*dfAstate){
            delete dfAstate;
            return it;
        }
    }
    return dfAstate;

}

void DFA::cleanUp() {
    nfa.init();
    regex.clear();
    DFAstateSet.clear();
    DFAIDset.clear();
    NFAmove.clear();

}



//
// Created by 王若璇 on 16/11/23.
//

#include "Transition.h"

Transition::Transition(const State &lhs, const std::vector<State*> &rhs) {
    nextState = new State(lhs);
    tolTransNum++;
}

Transition::Transition() {
    tolTransNum++;
    nextState = nullptr;

}

Transition::Transition(const State &lhs, State* rhs) {
    tolTransNum++;
    nextState = new State(lhs);
}

Transition::Transition(State *lhs, const vector<State *> &rhs) {
    tolTransNum++;
    nextState = lhs;
}

Transition::Transition(State *lhs, State *rhs) {
    tolTransNum++;
    nextState = lhs;
}

void Transition::showDetail() {
    tolTransNum++;
    recursionShow(nextState);
}

void Transition::recursionShow(State* state) {
    if(state== nullptr){
        return;
    }


}

Transition::Transition(int ID, char inaccept, State *next):transID(ID),inAccept(inaccept) {
    tolTransNum++;
    nextState = next;
}

//
// Created by 王若璇 on 16/11/23.
//

#include "Transition.h"

///@todo static tolNum++ when new a Transition.
Transition::Transition(const State &lhs, const std::vector<State*> &rhs) {
    nextState = new State(lhs);
}

Transition::Transition() {
    nextState = nullptr;

}

Transition::Transition(const State &lhs, State* rhs) {
    nextState = new State(lhs);
}

Transition::Transition(State *lhs, const vector<State *> &rhs) {
    nextState = lhs;
}

Transition::Transition(State *lhs, State *rhs) {
    nextState = lhs;
}

void Transition::showDetail() {
    recursionShow(nextState);
}

void Transition::recursionShow(State* state) {
    if(state== nullptr){
        return;
    }


}

Transition::Transition(int ID, char inaccept, State *next):transID(ID),inAccept(inaccept) {
    nextState = next;
}

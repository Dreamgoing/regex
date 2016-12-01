//
// Created by 王若璇 on 16/11/22.
//

#include "State.h"
#include "Transition.h"

State::State() {
    transition.clear();
    matched = false;
    visited = false;
    tolStateNum++;

}

State::~State() {
}

State::State(int stateID) : stateID(stateID) {
    transition.clear();
    tolStateNum++;
    matched = false;
    visited = false;
}

State::State(int stateID, State::NodeState nodeState) : stateID(stateID), nodeState(nodeState) {
    matched = false;
    visited = false;
    tolStateNum++;
    transition.clear();

}

State::State(State::NodeState node) : nodeState(node) {
    tolStateNum++;
    matched = false;
    visited = false;
    transition.clear();

}

void State::addTransition(Transition *trans) {
    nextStates.push_back(trans);
}

void State::show() {

    for (int i = 0; i < nextStates.size(); i++) {
        Transition *it = nextStates[i];
        cout << "state " << this->stateID << " => " << it->inAccept << " => " << it->nextState->stateID << endl;
    }

}

void State::showDetail() {
    show();
}

void State::clean() {
}

bool State::operator<(const State &lhs) const{
    return stateID<lhs.stateID;
}

bool State::operator<(State *lhs) const {
    return stateID<lhs->stateID;
}



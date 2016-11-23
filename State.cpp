//
// Created by 王若璇 on 16/11/22.
//

#include "State.h"

State::State() {
    transition.clear();
    matched = false;

}

State::~State() {
    matched = false;
    transition.clear();
}

State::State(int stateID):stateID(stateID) {
    transition.clear();
    matched = false;
}

State::State(int stateID, State::NodeState nodeState) :stateID(stateID),nodeState(nodeState){
    matched = false;
    transition.clear();

}

State::State(State::NodeState node) : nodeState(node){

}

void State::addTransition(Transition* trans) {
    nextStates.push_back(trans);
}



//
// Created by 王若璇 on 16/11/23.
//

#ifndef REGEX_FRAGMENT_H
#define REGEX_FRAGMENT_H

#include "State.h"
#include <vector>
#include <iostream>

class Transition {
public:
    static int tolTransNum;
public:
    State *nextState;
    int transID;
    char inAccept;

private:
    void recursionShow(State *state);

public:
    Transition();

    Transition(const State &lhs, const std::vector<State *> &rhs);

    Transition(const State &lhs, State *rhs);

    Transition(State *lhs, const vector<State *> &rhs);

    Transition(State *lhs, State *rhs);

    Transition(int ID, char inaccept, State *next);


    void showDetail();

};


#endif //REGEX_FRAGMENT_H

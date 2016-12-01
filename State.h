//
// Created by 王若璇 on 16/11/22.
//


#ifndef REGEX_STATE_H
#define REGEX_STATE_H

#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

///@todo call constructor inc static member tolStateNum.
class Transition;

using namespace std;

class State {
public:
    enum NodeState {
        SINGLE,
        SPLIT,
        MATCH
    } nodeState;
    static int tolStateNum;
public:
    multimap<char, State *> transition;
    vector<Transition *> nextStates;
    State *outa;
    State *outb;
    int stateID;
    bool matched;
    bool visited;
    bool operator< (const State& lhs)const ;
    bool operator< (State* lhs) const;


private:
    void show();

    void clean();

public:
    State();

    ~State();

    State(int stateID);

    State(int state, NodeState nodeState);

    State(NodeState node);

    void addTransition(Transition *trans);

    void showDetail();


};


#endif //REGEX_STATE_H

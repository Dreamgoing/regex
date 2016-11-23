//
// Created by 王若璇 on 16/11/20.
//

#ifndef REGEX_NFA_H
#define REGEX_NFA_H

#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <map>
#include "State.h"
#include "Transition.h"

using namespace std;

/**
 * @brief Non-Deterministic Finite Automation.
 *        Converting Regular Expressions to NFAs.
 * */

class Fragment{
public:
    State* start;
    State* final;
    Fragment(){}
    Fragment(int stateID,int transID,char inputChar){
        State* s1 = new State(stateID);
        State* s2 = new State(stateID+1);
        Transition* trans = new Transition(transID,inputChar,s2);
        s1->addTransition(trans);
        start = s1;
        final = s2;
    }
    Fragment(State* start,State* final){
        this->start = start;
        this->final = final;
    }
};
class NFA {
private:
    map<char,int> precedenceMap;
    stack<Fragment*> fragStack;
    State* initRoot;

private:
    void initPrecedenceMap();
    int getPrecedence(char c);
    string formatRegEx(const string &regEx);
    void catenation();
    void alternation();
    void literal(char character);
    void patch(std::vector<State*> &out,State* rhs);

public:
    NFA();
    ///@todo thinking how to implement the whole project.
    string regExToPostfix(const string &regEx);
    bool ThompsonNFA(const string &postfix);
    void showNFA();


};


#endif //REGEX_NFA_H

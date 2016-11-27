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
#include <queue>
#include <cassert>
#include "State.h"
#include "Transition.h"

using namespace std;

/**
 * @brief Non-Deterministic Finite Automation.
 *        Converting Regular Expressions to NFAs.
 * */

class Fragment {
public:
    State *start;
    State *final;

    Fragment() {}

    Fragment(int stateID, int transID, char inputChar) {
        State *s1 = new State(stateID);
        State *s2 = new State(stateID + 1);
        Transition *trans = new Transition(transID, inputChar, s2);
        s1->addTransition(trans);
        start = s1;
        final = s2;
    }

    Fragment(State *start, State *final) {
        this->start = start;
        this->final = final;
    }

    ///@note test TO
    void showFragment() {
        queue<State *> stateQueue;
        while (!stateQueue.empty()) {
            stateQueue.pop();
        }
        State *now;
        stateQueue.push(start);
        while (!stateQueue.empty()) {
            now = stateQueue.front();
            stateQueue.pop();
            if (!now->visited) {
                now->visited = true;
                now->showDetail();
                for (int i = 0; i < now->nextStates.size(); i++) {
                    State *next = now->nextStates[i]->nextState;
                    stateQueue.push(next);
                }
            }
        }
    }
};

class NFA {
private:
    map<char, int> precedenceMap;
    stack<Fragment *> fragStack;
    State *initRoot;
    set<char> charSet;
    string postfix;
public:
    const set<char> &getCharSet() const;

    void setCharSet(const set<char> &charSet);

    const stack<Fragment *, deque<Fragment *, allocator<Fragment *>>> &getFragStack() const;

    void setFragStack(const stack<Fragment *, deque<Fragment *, allocator<Fragment *>>> &fragStack);

    State *getInitRoot() const;

    void setInitRoot(State *initRoot);

    State *getEnd() const;

    void setEnd(State *end);

    Fragment *getNfa() const;

    void setNfa(Fragment *nfa);

    const map<char, int> &getPrecedenceMap() const;

    void setPrecedenceMap(const map<char, int> &precedenceMap);

private:
    State *end;
    Fragment *nfa;

private:
    void initPrecedenceMap();

    int getPrecedence(char c);

    string formatRegEx(const string &regEx);

    void catenation();

    void alternation();

    void literal(char character);

    void closure();

    void closurePlus();

    void zeroOrOne();

    void patch(std::vector<State *> &out, State *rhs);

    void clean();

public:
    NFA();

    ~NFA();

    void init();

    ///@todo thinking how to implement the whole project.
    string regExToPostfix(const string &regEx);

    bool ThompsonNFA(const string &postfix);

    void showNFA();

    void regexToNFA(const string& regex);


};


#endif //REGEX_NFA_H

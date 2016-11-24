//
// Created by 王若璇 on 16/11/20.
//
#include <iostream>
#include <map>
#include "NFA.h"
#include "Transition.h"
#include <cassert>
using namespace std;

//#define DEBUG_SHOW_FRAGMENT

int Transition::tolTransNum = 0;
int State::tolStateNum = 0;
void testRegExToPostfix(){
    NFA nfa;
    string regEx;
    while (cin>>regEx){
        cout<<nfa.regExToPostfix(regEx)<<endl;
    }

}
void testRegExToNFA(){
    NFA nfa;
    string regEx;
    while (cin>>regEx){
        cout<<"regex: "<<regEx<<endl;

        nfa.init();
#ifdef DEBUG_SHOW_FRAGMENT
        assert(nfa.fragStack.empty());
        cout<<State::tolStateNum<<" "<<Transition::tolTransNum<<endl;
#endif
        string postfix = nfa.regExToPostfix(regEx);
        nfa.ThompsonNFA(postfix);
        nfa.showNFA();
        cout<<'\n';
    }
}
int main() {
//    testRegExToPostfix();
    testRegExToNFA();
}


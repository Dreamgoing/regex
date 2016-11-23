//
// Created by 王若璇 on 16/11/20.
//
#include <iostream>
#include <map>
#include "NFA.h"
#include "Transition.h"
using namespace std;

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
        string postfix = nfa.regExToPostfix(regEx);
        nfa.ThompsonNFA(postfix);
        nfa.showNFA();
    }
}
int main() {
    testRegExToPostfix();
    //testRegExToNFA();
}


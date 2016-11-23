//
// Created by 王若璇 on 16/11/20.
//

#include "NFA.h"



void NFA::initPrecedenceMap() {
    precedenceMap.clear();
    precedenceMap = {{')',1},{'|',2},{'.',3},{'?',4},{'*',4},{'+',4},{'^',5}};


}

NFA::NFA() {
    initPrecedenceMap();
    initRoot = nullptr;

}

int NFA::getPrecedence(char c) {
    auto res = precedenceMap.find(c);
    if(res!=precedenceMap.end()){
        return res->second;
    } else{
        return 6; ///@note the max precedence
    }
}

/**
 * @brief Transform regular expression by inserting a '.'
 * as explicit concatenation operator.
 * */
string NFA::formatRegEx(const string &regEx) {
    set<char> allOperators;
    allOperators.clear();
    allOperators.insert('+');
    allOperators.insert('|');
    allOperators.insert('?');
    allOperators.insert('*');
    allOperators.insert('^');
    set<char> BinaryOperators;
    BinaryOperators.clear();
    BinaryOperators.insert('^');
    BinaryOperators.insert('|');

    string res;
    res.clear();

    for(int i = 0;i<regEx.length();i++){
        char now = regEx[i];
        if(i+1<regEx.length()){
            char next = regEx[i+1];
            res+=now;
            if(now!='('&&next!=')'&&
                    allOperators.find(next)==allOperators.end() &&
                    BinaryOperators.find(now)==BinaryOperators.end()){
                res+='.';
            }
        }
    }
    res+=regEx[regEx.length()-1];
    return res;

}

/**
 * @brief Convert regular expression from infix to postfix notation
 * using Shunting-yard algorithm. Insert a '.' as explicit concatenation operator.
 *
 * @brief Shunting-yard algorithm
 *
 * 1. If the incoming symbols is an operand, print it..
 * 2. If the incoming symbol is a left parenthesis, push it on the stack.
 * 3. If the incoming symbol is a right parenthesis:
 * discard the right parenthesis, pop and print the stack symbols
 * until you see a left parenthesis. Pop the left parenthesis and discard it.
 * 4. If the incoming symbol is an operator and the stack is
 * empty or contains a left parenthesis on top,
 * push the incoming operator onto the stack.
 * 5. If the incoming symbol is an operator and
 * has either higher precedence than the operator on the top of the stack,
 * or has the same precedence as the operator on the top of the stack
 * and is right associative -- push it on the stack.
 * 6. If the incoming symbol is an operator and
 * has either lower precedence than the operator on the top of the stack,
 * or has the same precedence as the operator on the top of the stack
 * and is left associative -- continue to pop the stack until this is not true.
 * Then, push the incoming operator.
 * 7. At the end of the expression,
 * pop and print all operators on the stack. (No parentheses should remain.)
 * */
string NFA::regExToPostfix(const string &regex) {
    string rule(formatRegEx(regex));
    string postfix;
    stack<char> st;
    while (!st.empty()){
        st.pop();
    }
    postfix.clear();
    for(int i = 0;i<rule.length();i++){
        char now = rule[i];
        switch (now){
            case '(':
                st.push(now);
                break;
            case ')':
                while (st.top()!='('){
                    postfix+=st.top();
                    st.pop();
                }
                st.pop();
                break;
            default:
                while (!st.empty()){
                    char peeked = st.top();
                    int peekedPrecedence = getPrecedence(peeked);
                    int nowPrecedence = getPrecedence(now);
                    if(peekedPrecedence>=nowPrecedence){
                        postfix+=peeked;
                        st.pop();
                    } else{
                        break;
                    }
                }
                st.push(now);
                break;
        }

    }
    while (!st.empty()){
        postfix+=st.top();
        st.pop();
    }
    return postfix;
}

///@note '~' empty edge
bool NFA::ThompsonNFA(const string &postfix) {
    for(int i = 0;i<postfix.length();i++){
        char now = postfix[i];
        switch (now){
            case '.':
                catenation();
                break;
            case '|':
                alternation();
                break;
            default:
                literal(now);
                break;
        }

    }
    return true;
}

void NFA::catenation() {
    Fragment* lhs = fragStack.top();
    fragStack.pop();
    Fragment* rhs = fragStack.top();
    fragStack.pop();
    Transition* transition = new Transition(Transition::tolTransNum,'~',lhs->start);
    rhs->final->addTransition(transition);
    rhs->final = lhs->final;
    fragStack.push(rhs);

}

void NFA::patch(std::vector<State*> &out,State* rhs) {
    for(int i = 0;i<out.size();i++){
        out[i] = rhs;
    }

}

void NFA::literal(char character) {
    Fragment* fragment = new Fragment(State::tolStateNum,Transition::tolTransNum,character);
    State::tolStateNum+=2;
    Transition::tolTransNum++;
    fragStack.push(fragment);
}

void NFA::showNFA() {
}

void NFA::alternation() {
    Fragment* lhs = fragStack.top();
    fragStack.pop();
    Fragment* rhs = fragStack.top();
    fragStack.pop();
    State* tmpStart = new State(State::tolStateNum);
    State* tmpFinal = new State(State::tolStateNum);
    Transition* fromTmpStartTolhs = new Transition(Transition::tolTransNum,'~',lhs->start);
    Transition* fromTmpStartTorhs = new Transition(Transition::tolTransNum,'~',rhs->start);
    tmpStart->addTransition(fromTmpStartTolhs);
    tmpStart->addTransition(fromTmpStartTolhs);

    Transition* fromlhsToTmpFinal = new Transition(Transition::tolTransNum,'~',tmpFinal);
    Transition* fromrhsToTmpFinal = new Transition(Transition::tolTransNum,'~',tmpFinal);
    lhs->final->addTransition(fromlhsToTmpFinal);
    rhs->final->addTransition(fromrhsToTmpFinal);

    Fragment* res = new Fragment(tmpStart,tmpFinal);
    fragStack.push(res);




}


//
// Created by 王若璇 on 16/11/25.
//

#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H

#include <iostream>
#include <cstdio>
#include <string>
#include "DFA.h"


///@todo learn to write more effective README
///@todo implement this class use Object-Oriented Inheritance.
using namespace std;

class Regex {
private:
    DFA dfa;

public:
    string regularExpression;

    Regex(const string &regularExpression);

    Regex();

    ///init before use Regex
    bool init(const string& rule);
    bool regexMatch(const string& str);
    tuple<bool,string> regexSearch(const string& str);


};


#endif //REGEX_REGEX_H

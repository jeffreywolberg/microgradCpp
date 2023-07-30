#ifndef _Operator_
#define _Operator_

#include <string>
#include <map>

using namespace std;

enum class Operator {
    NONE,
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    RELU
};

extern map<Operator, string> operatorStringMap;

#endif
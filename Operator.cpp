#include "Operator.hpp"

using namespace std;

map<Operator, string> operatorStringMap {
    {Operator::NONE, "None"},
    {Operator::ADD, "+"},
    {Operator::SUB, "-"},
    {Operator::MUL, "*"},
    {Operator::DIV, "/"},
    {Operator::POW, "**"},
    {Operator::RELU, "ReLU"}
};
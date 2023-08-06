#ifndef _VALUE_
#define _VALUE_

#include <vector>
#include <string>
#include <map>
#include "Operator.hpp"

using namespace std;



// struct OperatorComp {
//     bool operator() (const Operator& lhs, const Operator& rhs) const {
//         return static_cast<int>(lhs) < static_cast<int>(rhs);
//     }
// };

class Value {
    public: 
        Value(double data, string label, Operator op, vector<Value*> prev);
        Value(double data, Operator op, vector<Value*> prev);
        Value(double data, string label);
        Value(double data);
        Value(Value *v);
        friend ostream &operator<<(ostream &os, const Value &value);
        string getGraphName();
        string getGraphOpName();
        double data;
        double grad;
        string label;
        Operator op;
        vector<Value*> prev;
        Value *operator +(Value &obj);
        // Value operator +(double const n);
        Value *operator *(Value &obj);
        // Value operator *(double const n);
        Value *operator -(Value &obj);
        // Value operator -(double const n);
        Value *operator /(Value &obj);
        Value *power(Value &obj);
        // Value power(double n);
        Value *relu();
        function<void()> _backward;
};

#endif
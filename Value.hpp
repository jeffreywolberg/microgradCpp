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
        friend ostream &operator<<(ostream &os, const Value &value);
        string getGraphName();
        double data;
        double grad;
        string label;
        // function<void()> backward();
        Operator op;
        vector<Value*> prev;
        Value operator +(Value &obj);
        // Value operator +(double const n);
        Value operator *(Value &obj);
        // Value operator *(double const n);
        Value operator -(Value &obj);
        // Value operator -(double const n);
        Value operator /(Value &obj);
        Value power(Value &obj);
        // Value power(double n);
        Value relu();
    private:
        function<void()> _backward;
};

#endif
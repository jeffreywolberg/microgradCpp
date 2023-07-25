#include <vector>
#include <string>

using namespace std;

class Value {
    public: 
        Value(double data, string label, string op, vector<Value> children);
        Value(double data, string label);
        Value(double data);
        friend ostream &operator<<(ostream &os, const Value &value);
        double data;
        double grad;
        string label;
        string op;
        vector<Value> children;
        Value operator +(Value const &obj);
        Value operator +(double const n);
        Value operator *(Value const &obj);
        Value operator *(double const n);
        Value operator -(Value const &obj);
        Value operator -(double const n);
        Value power(Value const &obj);
        Value power(double const n);

};
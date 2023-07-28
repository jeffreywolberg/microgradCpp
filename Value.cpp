
// num, op, prev, label
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

#include "Value.hpp"

using namespace std;



Value::Value(double data, string label, string op, vector<Value*> prev) {
    this->data = data;
    this->grad = 0;
    this->op = op; 
    this->prev = prev; // by value
    this->label = label; 
}
Value::Value(double data, string op, vector<Value*> prev) {
    this->data = data;
    this->grad = 0;
    this->op = op;
    this->prev = prev; // by value
}

Value::Value(double data) {
    this->data = data;
    this->grad = 0;
}
Value::Value(double data, string label) {
    this->data = data;
    this->label = label;
    this->grad = 0;
}
ostream& operator<<(ostream &os, const Value &value) {
    os << "Value(" << value.data << ", label: " << value.label << ", op: " << value.op << ", children: [";
    for (int i=0; i<value.prev.size(); i++) os << "Value(" << value.prev[i]->data << ", " << value.prev[i]->label << "),";
    os << "])" << endl;
    return os;
}
string Value::getGraphName() {
    ostringstream oss;
    oss << '"' << this->label << ", data: " << this->data << ", grad: " << this->grad << '"';
    return oss.str();
}

Value Value::operator +(Value &obj) {
    Value out = Value(this->data + obj.data, "+", vector<Value*>{this, (Value*) &obj});

    return out;
}
// Value Value::operator +(double const n) {
//     return Value(this->data + n);
// }
Value Value::operator *(Value &obj) {
    return Value(this->data * obj.data, "*", vector<Value*>{this, (Value*) &obj});
}
// Value Value::operator *(double const n) {
//     return Value(this->data * n);
// }
Value Value::operator -(Value &obj) {
    return Value(this->data - obj.data, "-", vector<Value*>{this, (Value*) &obj});
}
// Value Value::operator -(double const n) {
//     return Value(this->data - n);
// }
Value Value::operator /(Value &obj) {
    Value l = *this;
    Value r = obj.power(1.0);
    // return (*this) * obj.power(1.0); // why does this throw a compiler error but line below does not?
    return l * r;
}


Value Value::power(Value &obj) {
    return Value(pow(this->data, (double) obj.data), "pow", vector<Value*>{this, (Value*) &obj});
}

Value Value::power(double const n)  {
    return Value(pow(this->data, (double) n));
}

Value Value::relu() {
    return Value(this->data > 0 ? this->data : 0, "relu", vector<Value*>{this});  
}


// int main() {
//     Value a = Value(1, "a");
//     Value b = Value(2, "b");
//     Value c = a + b;
//     Value d = Value(3, "d");

//     Value e = c*d + a;  e.label = "e";
//     cout << e << endl;
// }
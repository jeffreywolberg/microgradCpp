
// num, op, children, label
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

#include "Value.hpp"

using namespace std;

Value::Value(double data, string label, string op, vector<Value> children) {
            this->data = data;
            this->grad = 0;
            this->op = op; // by value
            this->children = children; // by value
            this->label = label; // by value
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
            os << "Value(" << value.data << ", label: " << value.label << ")" << endl;
            return os;
        }

        Value Value::operator +(Value const &obj) {
            return Value(this->data + obj.data);
        }
        Value Value::operator +(double const n) {
            return Value(this->data + n);
        }
        Value Value::operator *(Value const &obj) {
            return Value(this->data * obj.data);
        }
        Value Value::operator *(double const n) {
            return Value(this->data * n);
        }
        Value Value::operator -(Value const &obj) {
            return Value(this->data - obj.data);
        }
        Value Value::operator -(double const n) {
            return Value(this->data - n);
        }
        Value Value::power(Value const &obj) {
            return Value(pow(this->data, (double) obj.data));
        }
        Value Value::power(double const n)  {
            return Value(pow(this->data, (double) n));
        }

int main() {
    Value a = Value(1);
    Value b = Value(2);
    Value c = Value((a + b).data, "c", "+", vector<Value>{a, b});
    cout << c << endl;
}
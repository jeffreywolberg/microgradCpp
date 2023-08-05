
// num, op, prev, label
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

#include "Value.hpp"

using namespace std;

Value::Value(Value *v) {
    this->data  = v->data;
    this->grad  = v->grad;
    this->op    = v->op; 
    this->prev  = v->prev; // by value
    this->label = v->label; 
};

Value::Value(double data, string label, Operator op, vector<Value*> prev) {
    this->data = data;
    this->grad = 0;
    this->op = op; 
    this->prev = prev; // by value
    this->label = label; 
}
Value::Value(double data, Operator op, vector<Value*> prev) {
    this->data = data;
    this->grad = 0;
    this->op = op;
    this->prev = prev; // by value
}

Value::Value(double data) {
    this->data = data;
    this->grad = 0;
    this->op = Operator::NONE;
}
Value::Value(double data, string label) {
    this->data = data;
    this->label = label;
    this->grad = 0;
    this->op = Operator::NONE;
}
ostream& operator<<(ostream &os, const Value &value) {
    os << "Value(" << value.data << ", label: " << value.label << ", op: " << operatorStringMap[value.op] << ", children: [";
    for (int i=0; i<value.prev.size(); i++) os << "Value(" << value.prev[i]->data << ", " << value.prev[i]->label << "),";
    os << "])" << endl;
    return os;
}
string Value::getGraphName() {
    ostringstream oss;
    oss << '"' << this->label << ", data: " << this->data << ", grad: " << this->grad << '"';
    return oss.str();
}

string Value::getGraphOpName() {
    ostringstream oss;
    oss << '"' + this->label + ":" + operatorStringMap[this->op] + '"';
    return oss.str();
}

Value *Value::operator +(Value &obj) {
    Value *out = new Value(this->data + obj.data, Operator::ADD, vector<Value*>{this, (Value*) &obj});
    
    out->_backward =  [this, &obj, out]() {
        cout << "In + backward function for node: " << this->label << endl;
        cout << "this data: " << this->data << ", out.grad: " << out->grad << ", out.data: " << out->data << ", obj.data: " << obj.data << endl;
        obj.grad += 1.0 * out->grad;
        this->grad += 1.0 * out->grad;
    };

    return out;
}
// Value *Value::operator +(double const n) {
//     return Value(this->data + n);
// }
Value *Value::operator *(Value &obj) {
    Value *out = new Value(this->data * obj.data, Operator::MUL, vector<Value*>{this, &obj});
    cout << long (out) << " result of mul between " << this->data << " and " << obj.data << ": " << out->data << endl; 
    out->_backward =  [this, &obj, out]() {
        cout << "In * backward function for node: " << this->label << endl;
        cout << "this data: " << this->data << ", out.addr " << (long) out << ", out.grad: " << out->grad << ", out.data: " << out->data << ", obj.data: " << obj.data << endl;
        obj.grad += this->data * out->grad;
        this->grad += obj.data * out->grad;
    };
    return out;
}
// Value *Value::operator *(double const n) {
//     return Value(this->data * n);
// }
Value *Value::operator -(Value &obj) {
    Value *out = new Value(this->data - obj.data, Operator::SUB, vector<Value*>{this, (Value*) &obj});
    out->_backward =  [this, &obj, out]() {
        obj.grad += 1.0 * out->grad;
        this->grad += 1.0 * out->grad;
    };
    return out;
}
// Value *Value::operator -(double const n) {
//     return Value(this->data - n);
// }
Value *Value::operator /(Value &obj) {
    Value *l = this;
    Value *tmp = new Value(-1.0, "-1");
    Value *r = obj.power(*tmp); r->label = obj.label + "^-1";
    // return (*this) * obj.power(1.0); // why does this throw a compiler error but line below does not?
    return (*l * *r);
}


Value *Value::power(Value &obj) {
    Value *out = new Value(pow(this->data, obj.data), Operator::POW, vector<Value*>{this, (Value*) &obj});
    cout << long (out) << " result of pow between " << this->data << " and " << obj.data << ": " << out->data << endl; 
    out->_backward =  [this, &obj, out]() {
        cout << "In ** backward function for node: " << this->label << endl;
        cout << "this data: " << this->data << ", out.addr " << (long) out << ", out.grad: " << out->grad << ", out.data: " << out->data << ", obj.data: " << obj.data << endl;
        this->grad += (obj.data) * pow(this->data, obj.data-1) * out->grad;
        obj.grad += pow(this->data, obj.data) * log(this->data) * out->grad;
    };
    return out;
}

// Value Value::power(double const n)  {
//     return Value(pow(this->data, (double) n));
// }

Value *Value::relu() {
    Value *out = new Value(this->data > 0 ? this->data : 0, Operator::RELU, vector<Value*>{this}); 
    out->_backward =  [this, out]() {
        this->grad += out->data > 0 ? 1 : 0;
    };
    return out;
}

void Value::backward() {
    cout << "Running backward on: " << this->label << endl;
    if (this->_backward != nullptr) this->_backward();
    for (Value *ch : this->prev) {
        cout << (long) ch << ", " << ch->label << "'s grad : " << ch->grad << endl;
    }
    for (Value *ch : this->prev) {
        ch->backward();
    }
}


// int main() {
//     Value a = Value(1, "a");
//     Value b = Value(2, "b");
//     Value c = a + b;
//     Value d = Value(3, "d");

//     Value e = c*d + a;  e.label = "e";
//     cout << e << endl;
// }
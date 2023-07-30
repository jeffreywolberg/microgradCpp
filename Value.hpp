#include <vector>
#include <string>

using namespace std;

enum Operator {
    NONE,
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    RELU
};

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
        string op;
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
        // void addBackward(Value &other, Value const &out);
        // void mulBackward(Value &other, Value const &out);
        // void subBackward(Value &other, Value const &out);
        // void powerBackward(Value &other, Value const &out);
        // // void powerBackward(double const n, Value const out);
        // void reluBackward(Value const &out);
        function<void()> _backward;
};


// void Value::addBackward(Value &other, Value const &out) {
//     other.grad = 1.0 * out.grad;
//     this->grad = 1.0 * out.grad;
// }
// void Value::mulBackward(Value &other, Value const &out) {
//     other.grad = this->data * out.grad;
//     this->grad = other.data * out.grad;
// }
// void Value::subBackward(Value &other, Value const &out) {
//     other.grad = 1.0 * out.grad;
//     this->grad = 1.0 * out.grad;
// }
// void Value::powerBackward(double const n, Value const out) {
//     this->grad = (n) * pow(out.grad, n-1);
// }
// this.data raised to other.data, producing out.data
// void Value::powerBackward(Value &other, Value const &out) {
//     this->grad = (other.data) * pow(this->data, other.data-1) * out.grad;
//     other.grad = pow(this->data, other.data) * log(this->data) * out.grad;
// }

// void Value::reluBackward(Value const &out) {
//     this->grad = out.data > 0 ? 1 : 0;
// }
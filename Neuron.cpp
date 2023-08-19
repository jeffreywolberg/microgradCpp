#include "Neuron.hpp"
#include <random>
#include <iostream>

using namespace std;

random_device rd;  // obtain a seed from the hardware
mt19937 gen(rd()); // seed the generator
uniform_real_distribution<> distr(-1.0, 1.0);

Neuron::Neuron(int nin, string name, bool nonlin) {
    for (int i=0; i<nin; i++) {
        weights.push_back(new Value(distr(gen), name + ":w" + to_string(i)));
    }
    bias = new Value(distr(gen), name + ":b");
    this->nonlin = nonlin;
    this->nin = nin;
}

vector<Value *> Neuron::parameters() {
    vector<Value *> out = this->weights; // deep copy
    out.push_back(this->bias);
    return out;
}

Value *Neuron::call(vector<Value *> data) {
    Value *sum = new Value(0.0);
    assert(data.size() == this->weights.size());
    for (int i=0; i<this->weights.size(); i++) {
        Value *mulTmp = *(this->weights[i]) * *data[i];
        mulTmp->label = this->weights[i]->label + " * " + data[i]->label;
        sum = (*sum) + *mulTmp;
        sum->label = mulTmp->label + " cumsum";
    }
    Value *res = *sum + *bias;
    res->label = sum->label + " + bias";
    return nonlin ? res->relu() : res;
}

ostream& operator<<(ostream &os, const Neuron &neuron) {
    os << "Neuron(" << neuron.weights.size() << ")" << endl;
    return os;
}

// int main() {
//     Neuron n = Neuron(3, "neuron1", false);
//     for (Value *v : n.parameters()) {
//         cout << *v;
//     }
//     vector<Value *> data;
//     data.push_back(new Value(.5, "d1"));
//     data.push_back(new Value(.25, "d2"));
//     data.push_back(new Value(.75, "d3"));

//     Value *res = n.call(data); res->label = "res";
//     cout << *res << endl;
//     cout << n << endl;
// }
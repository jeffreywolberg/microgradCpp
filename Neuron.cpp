#include "Neuron.hpp"
#include <random>
#include <iostream>

using namespace std;

random_device rd;  // obtain a seed from the hardware
mt19937 gen(rd()); // seed the generator
uniform_real_distribution<> distr(-1.0, 1.0);

Neuron::Neuron(int nin, string name) {
    for (int i=0; i<nin; i++) {
        weights.push_back(new Value(distr(gen), name + ":w" + to_string(i)));
    }
    bias = new Value(distr(gen), name + ":b");
}

vector<Value *> Neuron::paramaters() {
    vector<Value *> out = this->weights; // deep copy
    out.push_back(this->bias);
    return out;
}

Value *Neuron::call(vector<Value *> data) {
    Value *sum = this->bias;
    for (int i=0; i<this->weights.size(); i++) {
        sum = (*sum) + (*(*(this->weights[i]) * *data[i]));
    }
    return sum->relu();
}

ostream& operator<<(ostream &os, const Neuron &neuron) {
    os << "Neuron(" << neuron.weights.size() << ")" << endl;
    return os;
}

int main() {
    Neuron n = Neuron(3, "neuron1");
    for (Value *v : n.paramaters()) {
        cout << *v;
    }
    vector<Value *> data;
    data.push_back(new Value(.5, "d1"));
    data.push_back(new Value(.25, "d2"));
    data.push_back(new Value(.75, "d3"));

    Value *res = n.call(data); res->label = "res";
    cout << *res << endl;
    cout << n << endl;
}
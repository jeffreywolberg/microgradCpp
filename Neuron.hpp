#ifndef __NEURON__
#define __NEURON__

#include "Value.hpp"

class Neuron {
    public:
        Neuron(int nin, string name);
        vector<Value *> paramaters();
        Value *call(vector<Value *>);
        friend ostream &operator<<(ostream &os, const Neuron &neuron);
        vector<Value *> weights;
        Value *bias;
};

#endif
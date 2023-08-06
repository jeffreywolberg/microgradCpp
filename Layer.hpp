#ifndef _LAYER_
#define _LAYER_

#include "Neuron.hpp"
#include <vector>
#include <string>

class Layer {
    public:
        Layer(int nin, int nout, string layerName, bool nonlin);
        vector<Value *>call(vector<Value*> data);
        vector<Neuron *> neurons;
        vector<Value *> paramaters();
        friend ostream& operator<<(ostream &os, const Layer &layer);
        string layerName;

};

#endif
#include "Layer.hpp"
#include <iostream>

using namespace std;

Layer::Layer(int nin, int nout, string layerName, bool nonlin) {
    assert(nin > 0 && nout > 0);
    for (int i=0; i<nout; i++) {
        neurons.push_back(new Neuron(nin, layerName + ":neuron" + to_string(i), nonlin));
    }
    this->layerName = layerName;
}

vector<Value*> Layer::parameters() {
    vector<Value *> res;
    for (int i=0; i<neurons.size(); i++) {
        vector<Value *> params = neurons[i]->parameters();
        res.insert(res.end(), params.begin(), params.end());
    }
    return res;
}


vector<Value *> Layer::call(vector<Value *> data) {
    vector<Value *> res;
    for (int i=0; i<neurons.size(); i++) {
        Neuron *n = neurons[i];
        assert(data.size() == n->nin);
        Value *resValue = n->call(data);
        res.push_back(resValue);
    }
    return res;
}

ostream& operator<<(ostream &os, const Layer &layer) {
    for (int i=0; i<layer.neurons.size(); i++) {
        Neuron *n = layer.neurons[i];
        os << layer.layerName << ":" << "n" << i << ": " << *n;
    }
    return os;
}


// int main() {
//     Layer l = Layer(2, 2, "l0", false);
//     for (Value *v : l.parameters()) {
//         cout << *v;
//     }
//     vector<Value *> data;
//     data.push_back(new Value(.5, "d0"));
//     data.push_back(new Value(.25, "d1"));
//     // data.push_back(new Value(.75, "d2"));

//     vector<Value *> res = l.call(data);
//     for (Value *v : res) {
//         cout << *v << endl;
//     }

//     // Graph g = Graph();
//     // g.backward(res);
//     // g.visualizeGraph(res, "graphs/graph_double3.png");
// }
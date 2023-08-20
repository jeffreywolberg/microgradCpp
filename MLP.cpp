#include "MLP.hpp"
#include <iostream>

using namespace std;

// layerDims represents [inputDims, ..., outputDims]
// numLayers == layerDims.size() - 1
MLP::MLP(vector<int> layerDims, string mlpName) {
    for (int i=0;i<layerDims.size()-1; i++) {
        bool nonLinOutput = (i+1) != layerDims.size()-1;
        string layerName = mlpName + ":" + "l" + to_string(i);
        layers.push_back(new Layer(layerDims[i], layerDims[i+1], layerName, nonLinOutput));
    }
    this->mlpName = mlpName;
}

vector<Value*> MLP::parameters() {
    vector<Value *> res;
    for (int i=0; i<layers.size(); i++) {
        vector<Value *> params = layers[i]->parameters();
        res.insert(res.end(), params.begin(), params.end());
    }
    return res;
}

vector<Value *> MLP::call(vector<Value *> data) {
    vector<Value *> res;
    vector<Value *> activations = data; // output from previous layer
    for (int i=0; i<this->layers.size(); i++) {
        Layer *l = this->layers[i];
        assert(activations.size() == l->neurons[0]->nin);
        activations = l->call(activations);
    }
    return activations;
}

void MLP::zeroGrad() {
    for (Value *value : this->parameters()) {
        value->grad = 0;
    }
}

ostream& operator<<(ostream &os, const MLP &mlp) {
    for (int i=0; i<mlp.layers.size(); i++) {
        Layer *l = mlp.layers[i];
        os << *l;
    }
    os << endl;
    return os;
}


// int main() {
//     MLP mlp = MLP({2, 2, 3}, "mlp0");
//     for (Value *v : mlp.parameters()) {
//         cout << *v;
//     }
//     vector<Value *> data;
//     data.push_back(new Value(.5, "d0"));
//     data.push_back(new Value(.25, "d1"));
//     // data.push_back(new Value(.75, "d2"));

//     vector<Value *> res = mlp.call(data);
//     for (Value *v : res) {
//         cout << *v << endl;
//     }
// }
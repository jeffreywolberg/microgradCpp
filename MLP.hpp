#ifndef _MLP_
#define _MLP_

#include "Layer.hpp"
#include <vector>
#include <string>

class MLP {
    public:
        MLP(vector<int> layerDims, string mlpName);
        vector<Value *>call(vector<Value*> data);
        vector<Layer *> layers;
        vector<Value *> parameters();
        friend ostream& operator<<(ostream &os, const MLP &mlp);
        string mlpName;
};

#endif
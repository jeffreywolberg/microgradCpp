#include <iostream>
#include <string>
#include <vector>

#include "Training.hpp"

using namespace std;

#define NUM_SAMPLES 2
#define NUM_INPUTS 2
#define NUM_OUTPUTS 1
#define NUM_EPOCHS 100 // total training passes through data

Value two = Value(2);

int main() {
    double learningRate = 0.001;

    Value *input[][NUM_INPUTS] = {
        {new Value(1), new Value(2)},
        {new Value(5), new Value(6)}
    };
    Value *groundTruth[] = {new Value(1), new Value(5)}; 
    Graph g = Graph();

    // assert input and groundTruth samples match
    assert(NUM_SAMPLES == sizeof(input) / sizeof(Value *) / NUM_INPUTS);
    assert(NUM_SAMPLES == (sizeof(groundTruth) / sizeof(groundTruth[0])) ); 

    MLP mlp = MLP({NUM_INPUTS, NUM_OUTPUTS}, "mlp");
    for (int epoch=0; epoch<NUM_EPOCHS; epoch++)
    {
        mlp.zeroGrad(); // zero the gradients every epoch
        double totalLoss = 0;
        for (int i=0; i<NUM_SAMPLES; i++) {
            vector<Value *> inputVec(input[i], input[i] + NUM_INPUTS);
            vector<Value *> res = mlp.call(inputVec);
            assert(NUM_OUTPUTS == res.size());
            // accum grad for sample
            for (Value *pred : res) {
                Value *loss = (*groundTruth[i] - *pred)->power(two);
                g.backward(loss);
                totalLoss += loss->data;
            }
        }
        cout << "Epoch " << to_string(epoch) << " train loss: " << to_string(totalLoss) << endl; 

        for (Value *param : mlp.parameters()) {
            // grad in this case means loss gets bigger if I make data more positive
            // therefore, to reduce loss, subtract
            // cout << "param: " << param->label << " data: " << param->data << ", grad: " << param->grad << endl;
            param->data -= learningRate * param->grad;
        }
    }

    for (int i = 0; i < NUM_SAMPLES; i++) {
        for (int j = 0; j < NUM_INPUTS; j++) {
            delete input[i][j];
        }
    }
    for (int i=0; i<NUM_SAMPLES; i++) {
        delete groundTruth[i];
    }
}
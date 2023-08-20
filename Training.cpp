#include <iostream>
#include <string>
#include <vector>

#include "Training.hpp"

using namespace std;

#define NUM_SAMPLES 2
#define NUM_INPUTS 2
#define NUM_OUTPUTS 1

#define CONST_VALUE_2 ;

int main() {
    Value two = Value(2);

    Value *input[][NUM_INPUTS] = {
        {new Value(1), new Value(2)},
        {new Value(5), new Value(6)}
    };
    Value *output[] = {new Value(1), new Value(5)}; 
    Graph g = Graph();

    // assert input and output samples match
    assert(NUM_SAMPLES == sizeof(input) / sizeof(Value *) / NUM_INPUTS);
    assert(NUM_SAMPLES == (sizeof(output) / sizeof(output[0])) ); 

    MLP mlp = MLP({NUM_INPUTS, NUM_OUTPUTS}, "mlp");
    for (int i=0; i<NUM_SAMPLES; i++) {
        cout << i << endl;
        vector<Value *> inputVec(input[i], input[i] + NUM_INPUTS);
        vector<Value *> res = mlp.call(inputVec);
        assert(NUM_OUTPUTS == res.size());
        for (Value *n : res) {
            
            Value *loss = (*output[i] - *n)->power(two);
            g.backward(loss);
        }
    }


    for (int i = 0; i < NUM_SAMPLES; i++) {
        for (int j = 0; j < NUM_INPUTS; j++) {
            delete input[i][j];
        }
    }
    for (int i=0; i<NUM_SAMPLES; i++) {
        delete output[i];
    }
}
#include <iostream>
#include <string>
#include <vector>

#include "Training.hpp"

using namespace std;

#define NUM_SAMPLES 4
#define NUM_INPUTS 3
#define NUM_OUTPUTS 1
#define NUM_EPOCHS 200 // total training passes through data

// Value two = Value(2);

int main() {
  double learningRate = 0.005;
  double tmpInput[NUM_SAMPLES][NUM_INPUTS] = {{2,3,-1.0}, {3,-1.0, 0.5}, {0.5,1,1}, {1, 1, -1}};
  Value *input[NUM_SAMPLES][NUM_INPUTS];
  for (int i=0; i<NUM_SAMPLES; i++) {
    for (int j=0; j<NUM_INPUTS; j++) {
        input[i][j] = new Value(tmpInput[i][j]);
    }
  }
  double tmpOutput[NUM_SAMPLES][NUM_OUTPUTS] = {1 -1, -1, 1};
  Value *groundTruth[NUM_SAMPLES][NUM_OUTPUTS];
  for (int i=0; i<NUM_SAMPLES; i++) {
    for (int j=0; j<NUM_OUTPUTS; j++) {
        groundTruth[i][j] = new Value(tmpOutput[i][j]);
    }
  }
  Graph g = Graph();

  // assert input and groundTruth samples match
  assert(NUM_SAMPLES == sizeof(input) / sizeof(Value *) / NUM_INPUTS);
  assert(NUM_SAMPLES == (sizeof(groundTruth) / sizeof(Value *) / NUM_OUTPUTS));

  MLP mlp = MLP({NUM_INPUTS, 4, NUM_OUTPUTS}, "mlp");
  for (int epoch = 0; epoch < NUM_EPOCHS; epoch++) {
    double totalLoss = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
      mlp.zeroGrad(); // zero the gradients
      vector<Value *> inputVec(input[i], input[i] + NUM_INPUTS);
      vector<Value *> res = mlp.call(inputVec);
      assert(NUM_OUTPUTS == res.size());
      // accum grad for sample
      for (int j=0; j<res.size(); j++) {
        Value *pred = res.at(j);
        Value two = Value(2.0);
        Value *loss = (*groundTruth[i][j] - *pred)->power(two);
        g.backward(loss);
        if (epoch == NUM_EPOCHS - 1) {
            g.visualizeGraph({loss}, "graphs/graphOR_" + to_string(i) + ".png");
        }
        totalLoss += loss->data;
      }
    }
    cout << "Epoch " << to_string(epoch)
         << " train loss: " << to_string(totalLoss) << endl;

    for (Value *param : mlp.parameters()) {
      // grad in this case means loss gets bigger if I make data more positive
      // therefore, to reduce loss, subtract
      // cout << "param: " << param->label << " data: " << param->data << ",
      // grad: " << param->grad << endl;
      param->data -= learningRate * param->grad;
    }
  }

  for (int i=0; i<NUM_SAMPLES; i++) {
    vector<Value *> inputVec(input[i], input[i] + NUM_INPUTS);
    Value *output = mlp.call(inputVec)[0];
    cout << to_string(i) << ": " << *output << endl;
    // g.visualizeGraph({output}, "graphs/graphOR_" + to_string(i) + ".png");
  }

//   for (Value *param : mlp.parameters()) {
    // cout << *param;
//   }




  for (int i = 0; i < NUM_SAMPLES; i++) {
    for (int j = 0; j < NUM_INPUTS; j++) {
      delete input[i][j];
    }
  }
  for (int i = 0; i < NUM_SAMPLES; i++) {
    for (int j = 0; j < NUM_OUTPUTS; j++) {
        delete groundTruth[i][j];
    }
  }
}
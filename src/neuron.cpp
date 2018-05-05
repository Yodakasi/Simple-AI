#include "neuron.h"
#include <iostream>


neuron::neuron(int numOfOutputs, int index) {
  for(int i=0; i<numOfOutputs; i++) {
    double lol = -1 + rand() / double(RAND_MAX/2.0);
    //std::cout << lol << std::endl;
    weights.push_back(lol);
  }
  this->index = index;
}

double neuron::transferFun(double x) {
  return tanh(x);
}

void neuron::feedForward(layer &prevLayer, int Myindex) {

  double sum = 0.0;

  for(int i=0; i<prevLayer.size(); i++) {
    sum += prevLayer[i].outputVal * prevLayer[i].weights[Myindex];
  }
  //std::cout << "elo " << sum << std::endl;

  outputVal = transferFun(sum);
  //std::cout << "elooutput " << outputVal << std::endl;
}

#include "neuron.h"


neuron::neuron(int numOfOutputs, int index) {
  for(int i=0; i<numOfOutputs; i++) {
    double lol = -1 + rand() / double(RAND_MAX/2.0);
    weights.push_back(connection());
    weights.back().weight = lol;
    weights.back().deltaWeight = 0.0;
  }
  this->index = index;
}

double neuron::transferFun(double x) {
  return tanh(x);
}

void neuron::feedForward(layer &prevLayer, int Myindex) {
  double sum = 0.0;
  for(unsigned i=0; i<prevLayer.size(); i++) {
    sum += prevLayer[i].outputVal * prevLayer[i].weights[Myindex].weight;
  }
  outputVal = transferFun(sum);

}

std::vector<double> neuron::getWeight() {
  std::vector<double> weightTmp;
  for(unsigned i=0; i<weights.size(); i++) {
    weightTmp.push_back(weights[i].weight);
  }
  return weightTmp;
}

void neuron::setWeight(int index, double newWeight) {
  weights[index].weight = newWeight;
}

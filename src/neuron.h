#ifndef LAYERS_H_
#define LAYERS_H_
#include <vector>
#include <cmath>
#include <cstdlib>

class neuron;

typedef std::vector<neuron> layer;

class neuron {
  static double transferFun(double x);
  double outputVal;
  std::vector<double> weights;
  int index;
public:
  neuron(int numOfOutputs, int index);
  void setOutputval(double val) {outputVal = val;}
  double getOutputval() {return outputVal;}
  void feedForward(layer &prevLayer, int Myindex);
};


#endif

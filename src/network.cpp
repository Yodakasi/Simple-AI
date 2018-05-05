#include "network.h"
#include <iostream>


network::network(std::vector<int> &topology) {
  int numOfLayers = topology.size();
  for(int i=0; i<numOfLayers; i++) {
    layers.push_back(layer());
    int numOfOutputs = i == numOfLayers - 1 ? 0 : topology[i + 1];
    for(int j=0; j<=topology[i]; j++) {
      layers.back().push_back(neuron(numOfOutputs, j));
      std::cout << "nufka sztuka" << std::endl;
    }
    layers.back().back().setOutputval(1.0);
  }
}

void network::feedForward(std::vector<double> &input) {
  assert(layers[0].size() - 1 == input.size());
  for(int i=0; i<input.size(); i++) {
    layers[0][i].setOutputval(input[i]);
  }
  //std::cout << "dupa " << layers[0][1].getOutputval();


  for(int i=1; i<layers.size(); i++) {
    layer &prevLayer = layers[i - 1];
    for(int j=0; j<layers[i].size() - 1; j++) {
      layers[i][j].feedForward(prevLayer, j);
    }
  }
}

void network::getValues(std::vector<double> &values) {
  for(int i=0; i<layers.back().size() - 1; i++) {
    values[i] = (layers[layers.size() - 1][i].getOutputval());
  }
}

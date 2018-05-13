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
  for(unsigned i=0; i<input.size(); i++) {
    layers[0][i].setOutputval(input[i]);
  }
  //std::cout << "dupa " << layers[0][1].getOutputval();


  for(unsigned i=1; i<layers.size(); i++) {
    layer &prevLayer = layers[i - 1];
    for(unsigned j=0; j<layers[i].size() - 1; j++) {
      layers[i][j].feedForward(prevLayer, j);
    }
  }
}

void network::getValues(std::vector<double> &values) {
  for(unsigned i=0; i<layers.back().size() - 1; i++) {
    values[i] = (layers[layers.size() - 1][i].getOutputval());
  }
}


void network::mixNets(std::vector<int> topology, std::vector<double> net, int share) {
  int netSize = net.size();
  int startNeuron = rand() % (netSize - (netSize * share)/100);
  int stopNeuron = (netSize * share)/100 + startNeuron;
  int layersIterator = 0;
  int neuronsIterator = 0;
  int weightIterator = 0;
  std::cout << "start " << startNeuron << " " << stopNeuron << std::endl;
  for(int i=0; i<netSize; i++) {
    if(i < startNeuron || i > stopNeuron) {
      layers[layersIterator][neuronsIterator].setWeight(weightIterator, net[i]);
    }
    ++weightIterator;
    if(weightIterator >= topology[layersIterator + 1]) {
      weightIterator = 0;
      ++neuronsIterator;
    }
    if(neuronsIterator > topology[layersIterator]) {
      neuronsIterator = 0;
      ++layersIterator;
    }
  }
  //layers[0][0].getWeight();
  //rand() % 17

}

void network::setNet(std::vector<int> topology, std::vector<double> net) {
  int netSize = net.size();
  int layersIterator = 0;
  int neuronsIterator = 0;
  int weightIterator = 0;
  for(int i=0; i<netSize; i++) {
    layers[layersIterator][neuronsIterator].setWeight(weightIterator, net[i]);
    ++weightIterator;
    if(weightIterator >= topology[layersIterator + 1]) {
      weightIterator = 0;
      ++neuronsIterator;
    }
    if(neuronsIterator > topology[layersIterator]) {
      neuronsIterator = 0;
      ++layersIterator;
    }
  }
  //layers[0][0].getWeight();
  //rand() % 17

}
void network::mutateNet(std::vector<int> topology, int chance) {
  unsigned layersIterator = 0;
  int neuronsIterator = 0;
  int weightIterator = 0;
  while(layersIterator < topology.size()-1) {
    int elo = 1 + rand() % 100;
    if((elo) <= chance) {
      layers[layersIterator][neuronsIterator].setWeight(weightIterator, -1 + rand() / double(RAND_MAX/2.0));
    }
    ++weightIterator;
    if(weightIterator >= topology[layersIterator + 1]) {
      weightIterator = 0;
      ++neuronsIterator;
    }
    if(neuronsIterator > topology[layersIterator]) {
      neuronsIterator = 0;
      ++layersIterator;
    }
  }

}

std::vector<double> network::getNet() {
  std::vector<double> net;
  std::vector<double> layerTmp;
  for(unsigned i=0; i<layers.size(); i++) {
    for(unsigned j=0; j<layers[i].size(); j++) {
      layerTmp = layers[i][j].getWeight();
      net.insert(net.end(), layerTmp.begin(), layerTmp.end());
    }
  }
  return net;
}

#ifndef NETWORK_H_
#define NETWORK_H_
#include <vector>
#include <cassert>
#include "neuron.h"


class network {
  std::vector<layer> layers;
public:
  network(std::vector<int> &topology);
  void feedForward(std::vector<double> &input);
  void getValues(std::vector<double> &values);
  void mixNets(std::vector<int> topology, std::vector<double> net);
  void setNet(std::vector<int> topology, std::vector<double> net);
  void mutateNet(std::vector<int> topology,int chance);
  void backProp();
  std::vector<double> getNet();
};


#endif

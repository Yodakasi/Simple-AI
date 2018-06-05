#ifndef SETTINGS_H_
#define SETTINGS_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "car.h"
#include "network.h"

class settings {
  double carAccelaration;
  double carBrakes;
  double carMaxspeed;
  int carsNumber;
  int topologyHiddenLayers;
  std::vector<int> topology;
  std::vector<int> neuronsNumber;
  sf::Vector2u resolution;
  int mutationChanceprog;
  int mutationChancenoprog;
public:
  settings(double carAccelaration, double carBrakes, double carMaxspeed, int carsNumber, int topologyHiddenLayers, int mutationChanceprog, int mutationChancenoprog);
  bool draw(sf::RenderWindow &window, sf::Font &font, sf::Event &event);
  void set(sf::RenderWindow &window, std::vector<car> &cars, std::vector<network> &net, std::vector<int> &topology, int &mutationChanceprog, int &mutationChancenopro, int &carsNumber);
};

#endif

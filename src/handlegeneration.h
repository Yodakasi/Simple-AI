#ifndef GENERATION_H_
#define GENERATION_H_
#include "car.h"
#include "network.h"
#include <vector>
#include <string>

class generation {
  std::vector<double> output;
  std::vector<double> input;
  std::vector<double> bestNet;
  int progress;
  int generationNum;
  int bestScore;
  sf::Text textgen;
  sf::Text textfit;
  sf::Text textprog;
  sf::Text textfitgen;
public:
  generation(sf::Font &font);
  void handleCars(sf::RenderWindow &window, std::vector<car> &cars, std::vector<network> &net, sf::Image &windowImage, sf::Vector2f points_pointer[], int carNumber, int pointsNumber);
  void handleProgress(std::vector<car> &cars, std::vector<network> &net, std::vector<int> &topology, int carsNumber, int mutationChanceprog, int mutationChancenoprog, double x, double y);
  void drawGensInfo(sf::RenderWindow &window);
  void reset();
  std::vector<double> getBestNet() {return bestNet;}
};


#endif

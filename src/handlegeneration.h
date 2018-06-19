#ifndef GENERATION_H_
#define GENERATION_H_
#include "car.h"
#include "network.h"
#include <vector>
#include <string>

class generation {
  std::vector<double> output; /*!< Vektor z wartościami otrzymanymi z sieci neronowej */
  std::vector<double> input; /*!< Vektor z wartościami do przekazania sieci neuronowej */
  std::vector<double> bestNet; /*!< Vektor z najlepszymi sieciami */
  int progress; /*!< Zmienna pilnująca czy nastąpił postęp */
  int generationNum; /*!< Licznik generacji */
  int bestScore; /*!< Aktualny najlepszy wynik */
  sf::Text textgen;
  sf::Text textfit;
  sf::Text textprog;
  sf::Text textfitgen;
public:
  generation(sf::Font &font);
  void handleCars(sf::RenderWindow &window, std::vector<car> &cars, std::vector<network> &net, sf::Image &windowImage, std::vector<sf::Vector2f> &mapPoints, int carNumber);
  void handleProgress(std::vector<car> &cars, std::vector<network> &net, std::vector<int> &topology, int carsNumber, int mutationChanceprog, int mutationChancenoprog, double x, double y);
  void drawGensInfo(sf::RenderWindow &window);
  void reset();
  /*!
  * \brief Metoda zwracająca aktualnie najlepszą sieć
  */
  std::vector<double> getBestNet() {return bestNet;}
};


#endif

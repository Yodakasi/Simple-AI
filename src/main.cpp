#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include "car.h"
#include "map.h"
#include "network.h"
#include "settings.h"
#include "handlegeneration.h"

int main() {
  //initialization
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Gierka");
  window.setFramerateLimit(60);
  srand(time(0));

  int carsNumber = 10;
  double carAccelaration = 0.15;
  double carMaxSpeed = 4;
  double carBrakes = 0.35;
  int mutationChanceprog = 2;
  int mutationChancenoprog = 25;
  std::vector<int> topology;
  std::vector<network> net;
  std::vector<car> cars;
  bool showBestCar = false;
  map map(window);
  //original position
  double x = window.getSize().x/2.7;
  double y = window.getSize().y/1.2;



  sf::Font font;
  if (!font.loadFromFile("../font/DejaVuSans.ttf")) {
      std::cout << "Font error" << std::endl;
  }

  sf::Texture textureSettingsButton;
  sf::Sprite settingsButton;
  sf::Texture textureBestCar;
  sf::Sprite bestCarButton;
  sf::Texture textureReturnButton;
  sf::Sprite returnButton;
  if(textureSettingsButton.loadFromFile("../img/settings.png")) {
    settingsButton.setTexture(textureSettingsButton);
  }
  if(textureReturnButton.loadFromFile("../img/return.png")) {
    returnButton.setTexture(textureReturnButton);
  }
  if(textureBestCar.loadFromFile("../img/bestcar.png")) {
    bestCarButton.setTexture(textureBestCar);
  }
  bestCarButton.setPosition(0, 30);
  returnButton.setPosition(120, 0);

  int pointsNumber = map.countPoints();
  sf::Vector2f points_pointer[pointsNumber];
  map.getPoints(points_pointer);

  generation generation(font);
  settings settings(carAccelaration, carBrakes, carMaxSpeed, carsNumber, 2, mutationChanceprog, mutationChancenoprog, x, y);
  settings.set(window, cars, net, topology, mutationChanceprog, mutationChancenoprog, carsNumber);

  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
              window.close();
      }

      if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(settingsButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && !showBestCar) {
          while(1) {
            window.clear();
            if(settings.draw(window, font, event)) {
              break;
            }
            window.display();
          }
          settings.set(window, cars, net, topology, mutationChanceprog, mutationChancenoprog, carsNumber);
          generation.reset();

        }
        if(bestCarButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && !showBestCar) {
          showBestCar = true;
          net[carsNumber].setNet(topology, generation.getBestNet());
          cars[carsNumber].carReset(x, y);
        }
      }
      window.clear();
      map.draw(window);
      sf::Image windowImage = window.capture();
      if(showBestCar) {
        if(cars[carsNumber].getcarstate()) {
          window.draw(returnButton);
          generation.handleCars(window, cars, net, windowImage, points_pointer, carsNumber, pointsNumber);
          if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if(returnButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
              showBestCar = false;
            }
          }
        }
        else {
          showBestCar = false;
        }
      }
      else {
        for(int i=0; i<carsNumber; i++) {
          generation.handleCars(window, cars, net, windowImage, points_pointer, i, pointsNumber);
        }
        for(int i=0; i<carsNumber; ++i) {
          if(cars[i].getcarstate()) {
            break;
          }
          if(i == carsNumber-1) {
            generation.handleProgress(cars, net, topology, carsNumber, mutationChanceprog, mutationChancenoprog, x, y);
          }

        }
        generation.drawGensInfo(window);
        window.draw(settingsButton);
        window.draw(bestCarButton);
      }
      window.display();
  }
  return 0;
}

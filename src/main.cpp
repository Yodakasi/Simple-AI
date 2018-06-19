/*!
* \authors Arkadiusz Bazak, Karol Wójcik
* \version 1.0 Compiled and tested on Linux system
* \date 18-06-2018
* \copyright GNU Public License
* \mainpage Simple artificial intelligence
* \section Kompilacja
* Do skompilowania i uruchomienia są potrzebne biblioteki sfml, można je zainstastalować poleceniem
* sudo apt-get install libsfml-dev
* potem uruchomić z głównego katalogu gry polecenie "make" i uruchomić polik binarny "gierka"
* który znajduje się w katalogu "bin".
*/
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
  sf::RenderWindow window(sf::VideoMode(960, 540), "Gierka", sf::Style::Titlebar | sf::Style::Close);
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
  std::vector<sf::Vector2f> mapPoints;
  bool showBestCar = false;
  map map;

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

  generation generation(font);
  settings settings(carAccelaration, carBrakes, carMaxSpeed, carsNumber, 2, mutationChanceprog, mutationChancenoprog);
  settings.set(window, cars, net, topology, mutationChanceprog, mutationChancenoprog, carsNumber);
  map.calcMap(window);
  map.getPoints(mapPoints);
  map.draw(window);
  window.display();
  sf::Image windowImage = window.capture();
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
          window.clear();
          map.calcMap(window);
          map.getPoints(mapPoints);
          map.draw(window);
          window.display();
          windowImage = window.capture();
          generation.reset();
        }
        if(bestCarButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && !showBestCar) {
          showBestCar = true;
          net[carsNumber].setNet(topology, generation.getBestNet());
          cars[carsNumber].carReset(window.getSize().x/2.7, window.getSize().y/1.2);
        }
      }
      window.clear();
      map.draw(window);
      if(showBestCar) {
        if(cars[carsNumber].getcarstate()) {
          window.draw(returnButton);
          generation.handleCars(window, cars, net, windowImage, mapPoints, carsNumber);
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
          generation.handleCars(window, cars, net, windowImage, mapPoints, i);
        }
        for(int i=0; i<carsNumber; ++i) {
          if(cars[i].getcarstate()) {
            break;
          }
          if(i == carsNumber-1) {
            generation.handleProgress(cars, net, topology, carsNumber, mutationChanceprog, mutationChancenoprog, window.getSize().x/2.7, window.getSize().y/1.2);
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

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <string>
#include "car.h"
#include "map.h"
#include "collider.h"
#include "network.h"
#include "settings.h"

int main() {
  //initialization
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Gierka");
  window.setFramerateLimit(60);
  srand(time(0));

  int carsNumber = 5;
  int bestScore = 0;
  int generation = 1;
  int progress = 0;
  double carAccelaration = 0.15;
  double carMaxSpeed = 4;
  double carBrakes = 0.35;
  int mutationChanceprog = 2;
  int mutationChancenoprog = 25;
  std::vector<double> bestNet;
  std::vector<int> topology;
  std::vector<double> output(2);
  std::vector<double> input(5);
  std::vector<network> net;
  std::vector<car> cars;
  bool showBestCar = false;
  map map(window);
  //original position
  double x = window.getSize().x/2.7;
  double y = window.getSize().y/1.2;










  sf::Font font;
  if (!font.loadFromFile("../font/DejaVuSans.ttf"))
  {
      std::cout << "Font error" << std::endl;
  }
  sf::Text textgen;
  sf::Text textfit;
  sf::Text textprog;
  sf::Text textfitgen;
  sf::Texture textureSettingsButton;
  sf::Sprite settingsButton;
  sf::Texture textureBestCar;
  sf::Sprite bestCarButton;
  if(textureSettingsButton.loadFromFile("../img/settings.png")) {
    settingsButton.setTexture(textureSettingsButton);
  }
  if(textureBestCar.loadFromFile("../img/bestcar.png")) {
    bestCarButton.setTexture(textureBestCar);
  }


  textgen.setFont(font);
  textfit.setFont(font);
  textprog.setFont(font);
  textfitgen.setFont(font);
  textgen.setCharacterSize(12);
  textfit.setCharacterSize(12);
  textfitgen.setCharacterSize(12);
  textprog.setCharacterSize(12);
  bestCarButton.setPosition(0, 30);
  textgen.setPosition(0, 70);
  textprog.setPosition(0, 100);
  textfit.setPosition(0, 85);
  textfitgen.setPosition(0, 115);


  int pointsNumber = map.countPoints();
  sf::Vector2f points_pointer[pointsNumber];
  map.getPoints(points_pointer);


  settings settings(carAccelaration, carBrakes, carMaxSpeed, carsNumber, 2, topology, 2, 4, x, y);
  settings.set(window, cars, net, topology, mutationChanceprog, mutationChancenoprog, carsNumber);

  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
              window.close();
      }

      if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(settingsButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
          while(1) {
            window.clear();
            if(settings.draw(window, font, event)) {
              break;
            }
            window.display();
          }
          settings.set(window, cars, net, topology, mutationChanceprog, mutationChancenoprog, carsNumber);
          generation = 0;
          bestScore = 0;
          bestNet.clear();
        }
      }
      if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(bestCarButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
          showBestCar = true;
        }
      }
      sf::Image windowImage = window.capture();

      window.clear();
      map.draw(window);


      textgen.setString("Generation: " + std::to_string(generation));
      textfit.setString("Best fitness: " + std::to_string(bestScore));
      for(int i=0; i<carsNumber; i++) {
      //check if collision occured
        if(cars[i].getcarstate()) {
          if(cars[i].checkCollision(cars[i].getBounds(), points_pointer, pointsNumber)) {
            cars[i].cardead();
          }
          if(float( (clock() - cars[i].getCarTime() ) /  CLOCKS_PER_SEC) > 5 && cars[i].getActualSpeed() < 1) {
            cars[i].cardead();
          }
          if(float( (clock() - cars[i].getCarTime() ) /  CLOCKS_PER_SEC) > 30) {
            cars[i].cardead();
          }


          cars[i].carline(windowImage, cars[i].carPosition(), cars[i].carRotation(), 40, 0);
          cars[i].carline(windowImage, cars[i].carPosition(), cars[i].carRotation() <= 300 ? cars[i].carRotation() + 60 : cars[i].carRotation() - 300, 35, 1);
          cars[i].carline(windowImage, cars[i].carPosition(), cars[i].carRotation() <= 60 ? cars[i].carRotation() + 300 : cars[i].carRotation() - 60, 35, 2);
          cars[i].carline(windowImage, cars[i].carPosition(), cars[i].carRotation() <= 330 ? cars[i].carRotation() + 30 : cars[i].carRotation() - 330, 40, 3);
          cars[i].carline(windowImage, cars[i].carPosition(), cars[i].carRotation() <= 30 ? cars[i].carRotation() + 330 : cars[i].carRotation() - 30, 40, 4);


          input[0] = cars[i].getDistance(cars[i].carPosition(), 0)/60 - 1;
          input[1] = cars[i].getDistance(cars[i].carPosition(), 1)/52.5 - 1;
          input[2] = cars[i].getDistance(cars[i].carPosition(), 2)/52.5 - 1;
          input[3] = cars[i].getDistance(cars[i].carPosition(), 3)/60 - 1;
          input[4] = cars[i].getDistance(cars[i].carPosition(), 4)/60 - 1;

          net[i].feedForward(input);
          net[i].getValues(output);

          cars[i].countScore();
          cars[i].move();
          cars[i].move(output[0], output[1]);



          cars[i].draw(window);

          window.draw(cars[i].getPoint(0));
          window.draw(cars[i].getPoint(1));
          window.draw(cars[i].getPoint(2));
          window.draw(cars[i].getPoint(3));
          window.draw(cars[i].getPoint(4));
        }
      }
      for(unsigned i=0; i<carsNumber; ++i) {
        if(cars[i].getcarstate()) {
          break;
        }
        if(i == carsNumber-1) {
          int max = 0, secondMax = 0, maxIterator = 0, secondMaxIterator;
          for(unsigned i=0; i<carsNumber; ++i) {
            if(cars[i].getScore() > max) {
              secondMax = max;
              secondMaxIterator = maxIterator;
              max = cars[i].getScore();
              maxIterator = i;
            }
            else if(cars[i].getScore() > secondMax) {
              secondMax = cars[i].getScore();
              secondMaxIterator = i;
            }
          }
          textfitgen.setString("Prev gen fitness: " + std::to_string(max + secondMax));
          if(bestScore - (max + secondMax) >= 0) {
            progress++;
          }
          else {
            progress = 0;

          }
          if(progress < 1) {
            if(secondMax == 0) secondMax++;
            int share = max/secondMax < 3 ? 55 + (max/secondMax) * 8 : 85;
            textprog.setString("Progress, share: " + std::to_string(share));
            net[maxIterator].mixNets(topology, net[secondMaxIterator].getNet(), share);
            if(bestScore < max + secondMax){
              bestScore = max + secondMax;
              bestNet = net[maxIterator].getNet();
            }

            for(int i=0; i<carsNumber; i++) {
              if(i == maxIterator) {
                continue;
              }
              net[i].setNet(topology, bestNet);
              net[i].mutateNet(topology, mutationChanceprog);
            }

          }
          else if(progress % 5 == 0){
            if(progress > 10) bestScore = max + secondMax;
            assert(bestNet.size() > 0);
            textprog.setString("Random mutations");
            for(int i=0; i<carsNumber; i++) {
              net[i].setNet(topology, bestNet);
              net[i].mutateNet(topology, mutationChancenoprog);
            }

          }
          else{
            assert(bestNet.size() > 0);
            textprog.setString("No progress for: " + std::to_string(progress) + " gen");
            for(int i=0; i<carsNumber; i++) {
              if(i == maxIterator) {
                net[i].setNet(topology, bestNet);
                net[i].mutateNet(topology, mutationChanceprog);
                continue;
              }
              net[i].setNet(topology, bestNet);
              net[i].mutateNet(topology, mutationChanceprog*2);
            }
          }
          generation++;
          std::cout << max << " " << secondMax << std::endl;
          for(unsigned i=0; i<carsNumber; ++i) {
            cars[i].carReset(x, y);
          }
        }
      }
      window.draw(settingsButton);
      window.draw(bestCarButton);
      window.draw(textgen);
      window.draw(textfitgen);
      window.draw(textfit);
      window.draw(textprog);
      window.display();
  }
  return 0;
}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include "car.h"
#include "map.h"
#include "collider.h"
#include "network.h"

int main() {
  //initialization
  sf::RenderWindow window(sf::VideoMode(1366, 768), "Gierka");
  window.setFramerateLimit(60);
  srand(time(0));
  //original position
  double x = window.getSize().x/2.7;
  double y = window.getSize().y/1.2;

  std::vector<double> output(2);
  std::vector<double> input(5);


  std::vector<int> topology;
  topology.push_back(5);
  topology.push_back(4);
  topology.push_back(3);
  topology.push_back(2);
  // set car accelaration, speed and  brakes power
  std::vector<network> net;
  std::vector<car> cars;

  for(int i=0; i<5; i++) {
    cars.push_back(car(window, 0.15, 4, 0.35, x, y));
    net.push_back(topology);

  }

  //car car(window, 0.15, 4, 0.35, x, y);

  //draw map
  map map(window);
  //save map points for collision
  int pointsNumber = map.countPoints();
  sf::Vector2f points_pointer[pointsNumber];
  map.getPoints(points_pointer);






  //collider collidercar1;

  while (window.isOpen())
  {

      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
      }
      window.clear();
      map.draw(window);
      sf::Image windowImage = window.capture();
      for(int i=0; i<5; i++) {
      //check if collision occured
        if(cars[i].getcarstate()) {
          if(cars[i].checkCollision(cars[i].getBounds(), points_pointer, pointsNumber)) {
            cars[i].cardead();
          }
          if(float( (clock() - cars[i].getCarTime() ) /  CLOCKS_PER_SEC) > 5 && cars[i].getActualSpeed() < 1) {
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
          //std::cout << input[0] << " " << input[1] << " " << input[2] << " " << input[3] << " " << input[4] << std::endl;

          net[i].feedForward(input);
          net[i].getValues(output);

          cars[i].countScore();
          cars[i].move();
          cars[i].move(output[0], output[1]);


          //std::cout << output[0] << " " << output[1] << std::endl;

          cars[i].draw(window);

          window.draw(cars[i].getPoint(0));
          window.draw(cars[i].getPoint(1));
          window.draw(cars[i].getPoint(2));
          window.draw(cars[i].getPoint(3));
          window.draw(cars[i].getPoint(4));
        }
      }
      //net.backProp();
      //handle drawing on screen
      for(unsigned i=0; i<cars.size(); ++i) {
        if(cars[i].getcarstate()) {
          break;
        }
        if(i == cars.size()-1) {
          int max = 0, secondMax = 0, maxIterator, secondMaxIterator;
          for(unsigned i=0; i<cars.size(); ++i) {
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
          std::vector<double> bestNet;
          net[maxIterator].mixNets(topology, net[secondMaxIterator].getNet());
          bestNet = net[maxIterator].getNet();
          for(int i=0; i<5; i++) {
            if(i == maxIterator) {
              continue;
            }
            net[i].setNet(topology, bestNet);
            net[i].mutateNet(topology, 5);
          }
          std::cout << max << " " << secondMax << std::endl;
          for(unsigned i=0; i<cars.size(); ++i) {
            cars[i].carReset(x, y);
          }

        }
      }
      window.display();


      //std::cout << car.countScore() << std::endl;


  }
  return 0;
}

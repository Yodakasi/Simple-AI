#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <ctime>
#include "car.h"
#include "map.h"
#include "collider.h"
#include "network.h"

int main() {
  //initialization
  sf::RenderWindow window(sf::VideoMode(1366, 768), "Gierka");
  window.setFramerateLimit(60);
  //original position
  double x = window.getSize().x/2.7;
  double y = window.getSize().y/1.2;
  // set car accelaration, speed and  brakes power
  car car(window, 0.15, 4, 0.35, x, y);

  //draw map
  map map(window);
  //save map points for collision
  int pointsNumber = map.countPoints();
  sf::Vector2f points_pointer[pointsNumber];
  map.getPoints(points_pointer);
  srand(time(0));

  std::vector<double> output(2);
  std::vector<double> input(5);


  std::vector<int> topology;
  topology.push_back(5);
  topology.push_back(4);
  topology.push_back(3);
  topology.push_back(2);
  network net(topology);


  collider circle1;
  collider circle2;
  collider circle3;
  collider circle4;
  collider circle5;

  collider collider;

  while (window.isOpen())
  {

      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
      }


      //check if collision occured
      if(collider.checkCollision(car.getBounds(), points_pointer, pointsNumber)) {
        car.carReset(x, y);
      }
      sf::Image windowImage = window.capture();
      circle1.carline(windowImage, car.carPosition(), car.carRotation(), 40);
      circle2.carline(windowImage, car.carPosition(), car.carRotation() <= 300 ? car.carRotation() + 60 : car.carRotation() - 300, 35);
      circle3.carline(windowImage, car.carPosition(), car.carRotation() <= 60 ? car.carRotation() + 300 : car.carRotation() - 60, 35);
      circle4.carline(windowImage, car.carPosition(), car.carRotation() <= 330 ? car.carRotation() + 30 : car.carRotation() - 330, 40);
      circle5.carline(windowImage, car.carPosition(), car.carRotation() <= 30 ? car.carRotation() + 330 : car.carRotation() - 30, 40);

      input[0] = circle1.getDistance(car.carPosition()) / 150 - 0.5;
      input[1] = circle2.getDistance(car.carPosition()) / 150 - 0.5;
      input[2] = circle3.getDistance(car.carPosition()) / 150 - 0.5;
      input[3] = circle4.getDistance(car.carPosition()) / 150 - 0.5;
      input[4] = circle5.getDistance(car.carPosition()) / 150 - 0.5;


      net.feedForward(input);
      net.getValues(output);


      car.move();
      car.move(output[0], output[1]);


      std::cout << output[0] << " " << output[1] << std::endl;


      //handle drawing on screen
      window.clear();
      map.draw(window);
      car.draw(window);

      window.draw(circle1.getPoint());
      window.draw(circle2.getPoint());
      window.draw(circle3.getPoint());
      window.draw(circle4.getPoint());
      window.draw(circle5.getPoint());
      window.display();


      //std::cout << car.countScore() << std::endl;


  }
  return 0;
}

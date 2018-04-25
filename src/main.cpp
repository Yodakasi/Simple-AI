#include <SFML/Graphics.hpp>
#include "car.h"
#include "map.h"
#include "collider.h"

int main() {
  //initialization
  sf::RenderWindow window(sf::VideoMode(1366, 768), "Gierka");
  window.setFramerateLimit(60);
  //original position
  double x = window.getSize().x/2.7;
  double y = window.getSize().y/1.2;
  // set car accelaration, speed and  brakes power
  car car(window, 0.3, 8, 0.35, x, y);

  //draw map
  map map(window);
  //save map points for collision
  int pointsNumber = map.countPoints();
  sf::Vector2f points_pointer[pointsNumber];
  map.getPoints(points_pointer);

  collider collider;

  while (window.isOpen())
  {

      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
      }

      car.move();
      //check if collision occured
      if(collider.checkCollision(car.getBounds(), points_pointer, pointsNumber)) {
        car.carReset(x, y);
      }
      //handle drawing on screen
      window.clear();
      map.draw(window);
      car.draw(window);
      window.display();
  }
  return 0;
}

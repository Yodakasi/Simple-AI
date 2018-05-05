#ifndef __COLLIDER_H_INCLUDED__
#define __COLLIDER_H_INCLUDED__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class collider {
  sf::CircleShape point;
public:
  bool checkCollision(sf::FloatRect car, sf::Vector2f points_pointer[], int pointsNumber);
  void carline(sf::Image window, sf::Vector2f position, float rotation, int reach);
  double getDistance(sf::Vector2f carPosition);
  sf::CircleShape getPoint() {return point;}
};

#endif

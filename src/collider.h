#ifndef __COLLIDER_H_INCLUDED__
#define __COLLIDER_H_INCLUDED__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

class collider {
  std::vector<sf::CircleShape> point;
public:
  collider() {point.resize(5);}
  ~collider() {}
  bool checkCollision(sf::FloatRect car, sf::Vector2f points_pointer[], int pointsNumber);
  void carline(sf::Image window, sf::Vector2f position, float rotation, int reach, int pointIndex);
  double getDistance(sf::Vector2f carPosition, int pointIndex);
  sf::CircleShape getPoint(int pointIndex) {return point[pointIndex];}
};

#endif

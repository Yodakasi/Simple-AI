#ifndef __COLLIDER_H_INCLUDED__
#define __COLLIDER_H_INCLUDED__
#include <SFML/Graphics.hpp>

class collider {
public:
  bool checkCollision(sf::FloatRect car, sf::Vector2f points_pointer[], int pointsNumber);
};

#endif

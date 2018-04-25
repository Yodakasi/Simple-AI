#include "collider.h"

bool collider::checkCollision(sf::FloatRect car, sf::Vector2f points_pointer[], int pointsNumber) {
  for(int i=0; i<pointsNumber; i++) {
    if(car.contains(points_pointer[i].x, points_pointer[i].y)) {
      return true;
    }
  }
  return false;
}

#include "collider.h"


bool collider::checkCollision(sf::FloatRect car, std::vector<sf::Vector2f> mapPoints) {
  for(int i=0; i<mapPoints.size(); i++) {
    if(car.contains(mapPoints[i].x, mapPoints[i].y)) {
      return true;
    }
  }
  return false;
}

void collider::carline(sf::Image window, sf::Vector2f position, float rotation, int reach, int pointIndex) {
  point[pointIndex].setRadius(5);
  double x = position.x;
  double y = position.y;
  int i = 0;
  while(window.getPixel(x, y).toInteger() != 4294967295 && i < reach) {
    i++;
    x += 3 * cos( rotation * M_PI / 180.0 );
    y += 3 * sin( rotation * M_PI / 180.0 );
  }
  point[pointIndex].setFillColor(sf::Color::Red);
  point[pointIndex].setPosition(x, y);
}

double collider::getDistance(sf::Vector2f carPosition, int pointIndex) {
  sf::Vector2f pointPosition = point[pointIndex].getPosition();
  return sqrt(pow(pointPosition.x - carPosition.x, 2) + pow(pointPosition.y - carPosition.y, 2));
}

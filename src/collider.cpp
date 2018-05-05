#include "collider.h"

bool collider::checkCollision(sf::FloatRect car, sf::Vector2f points_pointer[], int pointsNumber) {
  for(int i=0; i<pointsNumber; i++) {
    if(car.contains(points_pointer[i].x, points_pointer[i].y)) {
      return true;
    }
  }
  return false;
}

void collider::carline(sf::Image window, sf::Vector2f position, float rotation, int reach) {
  point.setRadius(5);
  double x = position.x;
  double y = position.y;
  //double a = tan(rotation * M_PI / 180.0);
  //double b = y - tan(rotation * M_PI / 180.0) * x;
  int i = 0;
  //std::cout << rotation << std::endl;
  while(window.getPixel(x, y).toInteger() != 4294967295 && i < reach) {
    //std::cout << window.getPixel(x, y).toInteger() << std::endl;
    i++;

    x += 3 * cos( rotation * M_PI / 180.0 );
    y += 3 * sin( rotation * M_PI / 180.0 );

    /*if((rotation < 45 && rotation >=0) || (rotation <= 360 && rotation > 315)) {
      x += 5;
      y = a * x + b;
    }
    else if(rotation > 135 && rotation < 225) {
      x -= 5;
      y = a * x + b;
    }
    else if(rotation > 225 && rotation < 315) {
      y -= 5;
      x = (y - b)/a;
    }
    else {
      y += 5;
      x = (y - b)/a;
    }*/
  }
  point.setFillColor(sf::Color::Red);
  point.setPosition(x, y);


    //std::cout << points_pointer[i].y << " " << a * points_pointer[i].x + b << std::endl;
    //sf::Color color = window.getPixel(points_pointer[i].x, points_pointer[i].y);
    //std::cout << color.toInteger() << std::endl;
}

double collider::getDistance(sf::Vector2f carPosition) {
  sf::Vector2f pointPosition = point.getPosition();
  return sqrt(pow(pointPosition.x - carPosition.x, 2) + pow(pointPosition.y - carPosition.y, 2));
}

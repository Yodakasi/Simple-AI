#ifndef __CAR_H_INCLUDED__
#define __CAR_H_INCLUDED__
#include <SFML/Graphics.hpp>

class car {
  sf::Sprite carSprite;
  sf::Texture texture;
  double accelaration;
  double speed;
  double brakes;
  double x;
  double y;
  double r;
  double actualSpeed;
public:
  car(sf::RenderWindow &window, double a, double b, double c, double x_start, double y_start);
  void draw(sf::RenderWindow &window);
  void move();
  sf::FloatRect getBounds();
  void carReset(double x_start, double y_start);
};

#endif

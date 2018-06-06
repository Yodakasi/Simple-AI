#ifndef __CAR_H_INCLUDED__
#define __CAR_H_INCLUDED__
#include <SFML/Graphics.hpp>
#include "collider.h"
#include <ctime>

class car : public collider {
  sf::Sprite carSprite;
  sf::Texture texture;
  double accelaration;
  double speed;
  double brakes;
  double x;
  double y;
  double r;
  double actualSpeed;
  int score = 0;
  bool alive = true;
  std::time_t beginTime;
public:
  car(sf::RenderWindow &window, double a, double b, double c, double x_start, double y_start);
  ~car() {}
  void draw(sf::RenderWindow &window);
  void move();
  void move(double turning, double engine);
  sf::FloatRect getBounds();
  sf::Vector2f carPosition();
  float carRotation();
  void carReset(double x_start, double y_start);
  void countScore();
  int getScore() {return score;}
  double getActualSpeed() {return actualSpeed;}
  std::time_t getCarTime() {return beginTime;}
  void cardead() {alive = false;}
  bool getcarstate() {return alive;}
};

#endif

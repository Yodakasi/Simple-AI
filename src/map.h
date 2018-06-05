#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>


class map {
  sf::VertexArray map_outside;
  sf::VertexArray map_inside;

public:
  void calcMap(sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);
  void getPoints(std::vector<sf::Vector2f> &points);
  int countPoints();
};

#endif

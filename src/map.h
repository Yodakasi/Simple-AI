#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__
#include <SFML/Graphics.hpp>


class map {
  sf::VertexArray map_outside;
  sf::VertexArray map_inside;

public:
  map(sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);
  sf::Vector2f *getPoints(sf::Vector2f points[]);
  int countPoints();
};

#endif

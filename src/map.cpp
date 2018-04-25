#include "map.h"
#include <cmath>
#include <iostream>

//caluculate points for inner and outer part of the track
void calc_points(sf::RenderWindow &window, sf::VertexArray &map_varcicies, double a, double b) {
  double x, y;
  for(double i=0; i<=2 * M_PI; i += 0.01 * M_PI) {
    x = a * cos(i);
    y = b * sin(i);
    map_varcicies.append(sf::Vector2f(x+window.getSize().x/2, y+window.getSize().y/2));
    x = (a+window.getSize().x/136.8) * cos(i);
    y = (b+window.getSize().y/76.8) * sin(i);
    map_varcicies.append(sf::Vector2f(x+window.getSize().x/2, y+window.getSize().y/2));
  }
}

//constructor
map::map(sf::RenderWindow &window) {
  map_outside.setPrimitiveType(sf::TrianglesStrip);
  map_inside.setPrimitiveType(sf::TrianglesStrip);
  calc_points(window, map_outside, window.getSize().x/2.27, window.getSize().y/2.19);
  calc_points(window, map_inside, window.getSize().x/3.4, window.getSize().y/5.12);
}

void map::draw(sf::RenderWindow &window) {
  window.draw(map_outside);
  window.draw(map_inside);
}

//return points of the track for collider
sf::Vector2f *map::getPoints(sf::Vector2f points[]) {
  int num = map_inside.getVertexCount();
  int i;
  for(i=0; i<num-1; i++) {
    points[i] = sf::Vector2f(map_outside[i].position);
  }
  num = map_outside.getVertexCount();
  for(int j=i, g=0; j<i+num-2; j++, g++) {
    points[j] = sf::Vector2f(map_inside[g].position);
  }

  return points;
}

//count how many points there is for collider
int map::countPoints() {
  return map_inside.getVertexCount() + map_outside.getVertexCount();
}

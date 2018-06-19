#include "map.h"


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

/*!
* \brief Metoda czyszcząca wcześniej zdefiniowaną mapę i obliczająca nowe punkty
* \param window zmienna okna przekazana przez referencje 
*/
void map::calcMap(sf::RenderWindow &window) {
  map_inside.clear();
  map_outside.clear();
  map_outside.setPrimitiveType(sf::TrianglesStrip);
  map_inside.setPrimitiveType(sf::TrianglesStrip);
  calc_points(window, map_outside, window.getSize().x/2.27, window.getSize().y/2.19);
  calc_points(window, map_inside, window.getSize().x/3.4, window.getSize().y/5.12);
}

/*!
* \brief Metoda rysująca mape w oknie
* \param window zmienna okna przekazana przez referencje 
*/
void map::draw(sf::RenderWindow &window) {
  window.draw(map_outside);
  window.draw(map_inside);
}

/*!
* \brief Metoda zwracają punkty mapy do późniejszego liczenia kolizji w klasie collider
* \param points Refencja do zmiennej przechowującej punkty mapy 
*/
void map::getPoints(std::vector<sf::Vector2f> &points) {
  points.clear();
  int num = map_inside.getVertexCount();
  int i;
  for(i=0; i<num-1; i++) {
    points.push_back(sf::Vector2f(map_outside[i].position));
  }
  num = map_outside.getVertexCount();
  for(int j=i, g=0; j<i+num-2; j++, g++) {
    points.push_back(sf::Vector2f(map_inside[g].position));
  }
}

/*!
* \brief Metoda zwracają ilość punktów mapy do późniejszego liczenia kolizji w klasie collider
*/
int map::countPoints() {
  return map_inside.getVertexCount() + map_outside.getVertexCount();
}

#include "car.h"
#include <cmath>
#include <iostream>


/*!
* \brief Konstruktor 
* \param window Referencja do okna 
* \param a Przyspieszenie samochodu 
* \param b Maksymalan prędkość samochodu 
* \param c Siła hamowania samochodu
* \param x_start Pozycja startowa samochodu na osi x
* \param y_start Pozycja startowa samochodu na osi y
* \details Ustala startową pozycje samochodu, jego maksymalną prędkość, przyspieszenie, siłe 
* hamowania i losowa przypisuje mu teksture 
*/
car::car(sf::RenderWindow &window, double a, double b, double c, double x_start, double y_start) {
  accelaration = a;
  speed = b;
  brakes = c;
  x = x_start;
  y = y_start;
  r = 0;
  actualSpeed = 0;
  carSprite.setPosition(x, y);
  switch(rand() % 4) {
    case 0:
      if(texture.loadFromFile("../img/car.png")){
        carSprite.setTexture(texture);
        break;
      }
      [[fallthrough]];
    case 1:
      if(texture.loadFromFile("../img/car2.png")){
        carSprite.setTexture(texture);
        break;
      }
      [[fallthrough]];
    case 2:
      if(texture.loadFromFile("../img/car3.png")){
        carSprite.setTexture(texture);
        break;
      }
      [[fallthrough]];
    case 3:
      if(texture.loadFromFile("../img/car3.png")){
        carSprite.setTexture(texture);
        break;
      }
      [[fallthrough]];
    default:
      carSprite.setTextureRect(sf::IntRect(25, 12.5, 50, 25));
      carSprite.setColor(sf::Color::Red);

  }
  beginTime = std::time(NULL);
  carSprite.setScale(window.getSize().x/1366.32, window.getSize().y/768.72);
  carSprite.setOrigin(carSprite.getLocalBounds().width/2, carSprite.getLocalBounds().height/2);
}

/*!
* \brief Metoda rysująca samochód w oknie
* \param window Referencja do okna
*/
void car::draw(sf::RenderWindow &window) {
  carSprite.setTexture(texture);
  carSprite.setRotation(r);
  window.draw(carSprite);
}

/*!
* \brief Metoda zajmująca poruszaniem się samochodu 
* \details Nie używana w aktualnej wersji przeznaczona tylko do testów
*/
[[deprecated("Don't use with neuron network, will alter with progress")]]
void car::move(){
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
      if(actualSpeed > 0 ) actualSpeed -= brakes;
      if(actualSpeed > (-speed)/2) actualSpeed -= accelaration/3;
  }
  //handle accelarating
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
      if(actualSpeed < speed) actualSpeed += accelaration;
  }
  //make car slow down if no key is pressed
  if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
      if(actualSpeed < 0.01 && actualSpeed > -0.01) actualSpeed = 0;
      else if(actualSpeed > 0) actualSpeed -= accelaration/5;
      else if(actualSpeed < 0) actualSpeed += accelaration/5;

  }
  //handle stering only if car is moving
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
      r -= 0.4 * (actualSpeed);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
      r += 0.4 * (actualSpeed);
  }

  //calculate car movement in x y axis
  x += cos( r * M_PI / 180.0 ) * (actualSpeed);
  y += sin( r * M_PI / 180.0 ) * (actualSpeed);
  carSprite.setPosition(x, y);
}

/*!
* \brief Metoda zajmująca poruszniem się samochów przez sieć neuronową
* \param turning Zminenna przechowująca wartości od -1 do 1 wyznacza kierunek (lewo, prawo) oraz siłe skrętu
* \param engine Zminenna przechowująca wartości od -1 do 1 wynacza kierunek (przód, tył) oraz prędkość jazdy
*/
void car::move(double turning, double engine){
  if (engine < 0)
  {
      if(actualSpeed > 0 ) actualSpeed -= brakes;
      if(actualSpeed > (-speed)/2) actualSpeed -= accelaration/3 * engine;
  }
  //handle accelarating
  else if (engine > 0)
  {
      if(actualSpeed < speed) actualSpeed += accelaration * engine;
  }
  //make car slow down if no key is pressed
  else
  {
      if(actualSpeed < 0.01 && actualSpeed > -0.01) actualSpeed = 0;
      else if(actualSpeed > 0) actualSpeed -= accelaration/5;
      else if(actualSpeed < 0) actualSpeed += accelaration/5;

  }
  //handle stering only if car is moving
  r += turning * (actualSpeed);
  //calculate car movement in x y axis
  x += cos( r * M_PI / 180.0 ) * (actualSpeed);
  y += sin( r * M_PI / 180.0 ) * (actualSpeed);
  carSprite.setPosition(x, y);
}

/*!
* \brief Metoda zwracająca granice samochodu
* \details Potrzebna do liczenia kolizji samochodu z punktami mapy
*/
sf::FloatRect car::getBounds() {
  return carSprite.getGlobalBounds();
}

/*!
* \brief Metoda resetująca samochód jeśli nastąpiła kolizja
* \param x_start Nowa pozycja samochodu na osi x
* \param y_start Nowa pozycja samochodu na osi y
*/
void car::carReset(double x_start, double y_start) {
  x = x_start;
  y = y_start;
  r = 0;
  score = 0;
  actualSpeed = 0;
  carSprite.setPosition(x, y);
  alive = true;
  beginTime = std::time(nullptr);
}

sf::Vector2f car::carPosition() {
  return carSprite.getPosition();
}

/*!
* \brief Metoda zwracająca aktualny kąt samochodu względem osi x
*/
float car::carRotation() {
  return carSprite.getRotation();
}

/*!
* \brief Metoda licząca punkty samochodu
*/
void car::countScore() {
  score += actualSpeed;
}

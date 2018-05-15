#include "car.h"
#include <cmath>
#include <iostream>


//constructor
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

  carSprite.setScale(window.getSize().x/1366.32, window.getSize().y/768.72);
  carSprite.setOrigin(carSprite.getLocalBounds().width/2, carSprite.getLocalBounds().height/2);
  beginTime = clock();
}
//drawing the car on screen
void car::draw(sf::RenderWindow &window) {
  carSprite.setTexture(texture);
  carSprite.setRotation(r);
  window.draw(carSprite);
}
//calculate car speed
void car::move(){
  //handle braking and reversing
  //std::cout << x << " " << y << " " << tan(r * M_PI / 180.0) * x + y - tan(r * M_PI / 180.0) * x << std::endl;
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

void car::move(double turning, double engine){
  //handle braking and reversing
  //std::cout << x << " " << y << " " << tan(r * M_PI / 180.0) * x + y - tan(r * M_PI / 180.0) * x << std::endl;
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

sf::FloatRect car::getBounds() {
  return carSprite.getGlobalBounds();
}

//method for reseting car if collision occured
void car::carReset(double x_start, double y_start) {
  x = x_start;
  y = y_start;
  r = 0;
  score = 0;
  actualSpeed = 0;
  carSprite.setPosition(x, y);
  alive = true;
  beginTime = clock();
}

sf::Vector2f car::carPosition() {
  return carSprite.getPosition();
}

float car::carRotation() {
  return carSprite.getRotation();
}

void car::countScore() {
  score += actualSpeed;
}

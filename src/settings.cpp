#include "settings.h"

settings::settings(double carAccelaration, double carBrakes, double carMaxspeed, int carsNumber, int topologyHiddenLayers, int mutationChanceprog, int mutationChancenoprog, int x, int y) {
  this->carAccelaration = carAccelaration;
  this->carBrakes = carBrakes;
  this->carMaxspeed = carMaxspeed;
  this->carsNumber = carsNumber;
  this->topologyHiddenLayers = topologyHiddenLayers;
  this->mutationChanceprog = mutationChanceprog;
  this->mutationChancenoprog = mutationChancenoprog;
  this->x = x;
  this->y = y;
  neuronsNumber.push_back(4);
  neuronsNumber.push_back(3);
  neuronsNumber.push_back(1);
  neuronsNumber.push_back(1);
}

void settings::set(sf::RenderWindow &window, std::vector<car> &cars, std::vector<network> &net, std::vector<int> &topology, int &mutationChanceprog, int &mutationChancenoprog, int &carsNumber) {
  carsNumber = this->carsNumber;
  cars.clear();
  net.clear();
  topology.clear();
  topology.push_back(5);
  for(int i=0; i<topologyHiddenLayers; i++) {
    topology.push_back(neuronsNumber[i]);
  }
  topology.push_back(2);
  for(int i=0; i<carsNumber+1; i++) {
    cars.push_back(car(window, carAccelaration, carMaxspeed, carBrakes, x, y));
    net.push_back(network(topology));
  }
  cars[carsNumber].cardead();
  std::cout << "Size " << cars.size() << " " << net.size() << std::endl;
  //topologyHiddenLayers = this->topologyHiddenLayers;
  mutationChanceprog = this->mutationChanceprog;
  mutationChancenoprog = this->mutationChancenoprog;
}


bool settings::draw(sf::RenderWindow &window, sf::Font &font, sf::Event &event) {
  sf::Texture textureReturn;
  sf::Sprite returnButton;
  sf::Texture texturePlus;
  sf::Sprite plusButton1;
  sf::Sprite plusButton2;
  sf::Sprite plusButton3;
  sf::Sprite plusButton4;
  sf::Sprite plusButton5;
  sf::Sprite plusButton6;
  sf::Sprite plusButton7;
  sf::Sprite plusButton8;
  sf::Sprite plusButton9;
  sf::Sprite plusButton10;
  sf::Sprite plusButton11;
  sf::Texture textureMinus;
  sf::Sprite minusButton1;
  sf::Sprite minusButton2;
  sf::Sprite minusButton3;
  sf::Sprite minusButton4;
  sf::Sprite minusButton5;
  sf::Sprite minusButton6;
  sf::Sprite minusButton7;
  sf::Sprite minusButton8;
  sf::Sprite minusButton9;
  sf::Sprite minusButton10;
  sf::Sprite minusButton11;
  sf::Text carAcc;
  sf::Text carBre;
  sf::Text carMaxSpe;
  sf::Text carsNum;
  sf::Text mutationChapro;
  sf::Text mutationChanopro;
  sf::Text hiddenLay;
  sf::Text neurons1;
  sf::Text neurons2;
  sf::Text neurons3;
  sf::Text neurons4;
  sf::Text carAccValue;
  sf::Text carBreValue;
  sf::Text carMaxSpeValue;
  sf::Text carsNumValue;
  sf::Text mutationChaproValue;
  sf::Text mutationChanoproValue;
  sf::Text hiddenLayValue;
  sf::Text neurons1Value;
  sf::Text neurons2Value;
  sf::Text neurons3Value;
  sf::Text neurons4Value;
  carAcc.setFont(font);
  carBre.setFont(font);
  carMaxSpe.setFont(font);
  carsNum.setFont(font);
  mutationChapro.setFont(font);
  mutationChanopro.setFont(font);
  hiddenLay.setFont(font);
  neurons1.setFont(font);
  neurons2.setFont(font);
  neurons3.setFont(font);
  neurons4.setFont(font);
  carAccValue.setFont(font);
  carBreValue.setFont(font);
  carMaxSpeValue.setFont(font);
  carsNumValue.setFont(font);
  mutationChaproValue.setFont(font);
  mutationChanoproValue.setFont(font);
  hiddenLayValue.setFont(font);
  neurons1Value.setFont(font);
  neurons2Value.setFont(font);
  neurons3Value.setFont(font);
  neurons4Value.setFont(font);
  carAcc.setCharacterSize(20);
  carBre.setCharacterSize(20);
  carMaxSpe.setCharacterSize(20);
  carsNum.setCharacterSize(20);
  mutationChapro.setCharacterSize(20);
  mutationChanopro.setCharacterSize(20);
  hiddenLay.setCharacterSize(20);
  neurons1.setCharacterSize(20);
  neurons2.setCharacterSize(20);
  neurons3.setCharacterSize(20);
  neurons4.setCharacterSize(20);
  carAccValue.setCharacterSize(20);
  carBreValue.setCharacterSize(20);
  carMaxSpeValue.setCharacterSize(20);
  carsNumValue.setCharacterSize(20);
  mutationChaproValue.setCharacterSize(20);
  mutationChanoproValue.setCharacterSize(20);
  hiddenLayValue.setCharacterSize(20);
  neurons1Value.setCharacterSize(20);
  neurons2Value.setCharacterSize(20);
  neurons3Value.setCharacterSize(20);
  neurons4Value.setCharacterSize(20);
  carAcc.setPosition(100, 135);
  carBre.setPosition(100, 170);
  carMaxSpe.setPosition(100, 205);
  carsNum.setPosition(100, 240);
  mutationChapro.setPosition(100, 275);
  mutationChanopro.setPosition(100, 310);
  hiddenLay.setPosition(100, 345);
  neurons1.setPosition(100, 380);
  neurons2.setPosition(100, 415);
  neurons3.setPosition(100, 450);
  neurons4.setPosition(100, 485);
  carAccValue.setPosition(850, 135);
  carBreValue.setPosition(850, 170);
  carMaxSpeValue.setPosition(850, 205);
  carsNumValue.setPosition(850, 240);
  mutationChaproValue.setPosition(850, 275);
  mutationChanoproValue.setPosition(850, 310);
  hiddenLayValue.setPosition(850, 345);
  neurons1Value.setPosition(850, 380);
  neurons2Value.setPosition(850, 415);
  neurons3Value.setPosition(850, 450);
  neurons4Value.setPosition(850, 485);
  carAcc.setString("Set car accelaration");
  carBre.setString("Set car breaking power");
  carMaxSpe.setString("Set car maximum speed");
  carsNum.setString("Set cars number");
  mutationChapro.setString("Set chance of mutation if there is progress");
  mutationChanopro.setString("Set chance of mutation if there is no progress");
  hiddenLay.setString("Set number of hidden layers");
  neurons1.setString("Set number of neurons in this layer");
  neurons2.setString("Set number of neurons in this layer");
  neurons3.setString("Set number of neurons in this layer");
  neurons4.setString("Set number of neurons in this layer");
  carAccValue.setString(std::to_string(carAccelaration));
  carBreValue.setString(std::to_string(carBrakes));
  carMaxSpeValue.setString(std::to_string(carMaxspeed));
  carsNumValue.setString(std::to_string(carsNumber));
  mutationChaproValue.setString(std::to_string(mutationChanceprog));
  mutationChanoproValue.setString(std::to_string(mutationChancenoprog));
  hiddenLayValue.setString(std::to_string(topologyHiddenLayers));
  neurons1Value.setString(std::to_string(neuronsNumber[0]));
  neurons2Value.setString(std::to_string(neuronsNumber[1]));
  neurons3Value.setString(std::to_string(neuronsNumber[2]));
  neurons4Value.setString(std::to_string(neuronsNumber[3]));
  if(textureReturn.loadFromFile("../img/return.png")) {
    returnButton.setTexture(textureReturn);
  }
  if(texturePlus.loadFromFile("../img/plus.png")) {
    plusButton1.setTexture(texturePlus);
    plusButton2.setTexture(texturePlus);
    plusButton3.setTexture(texturePlus);
    plusButton4.setTexture(texturePlus);
    plusButton5.setTexture(texturePlus);
    plusButton6.setTexture(texturePlus);
    plusButton7.setTexture(texturePlus);
    plusButton8.setTexture(texturePlus);
    plusButton9.setTexture(texturePlus);
    plusButton10.setTexture(texturePlus);
    plusButton11.setTexture(texturePlus);
  }
  if(textureMinus.loadFromFile("../img/minus.png")) {
    minusButton1.setTexture(textureMinus);
    minusButton2.setTexture(textureMinus);
    minusButton3.setTexture(textureMinus);
    minusButton4.setTexture(textureMinus);
    minusButton5.setTexture(textureMinus);
    minusButton6.setTexture(textureMinus);
    minusButton7.setTexture(textureMinus);
    minusButton8.setTexture(textureMinus);
    minusButton9.setTexture(textureMinus);
    minusButton10.setTexture(textureMinus);
    minusButton11.setTexture(textureMinus);
  }
  returnButton.setPosition(100, 100);
  minusButton1.setPosition(800, 135);
  plusButton1.setPosition(1000, 135);
  minusButton2.setPosition(800, 170);
  plusButton2.setPosition(1000, 170);
  minusButton3.setPosition(800, 205);
  plusButton3.setPosition(1000, 205);
  minusButton4.setPosition(800, 240);
  plusButton4.setPosition(1000, 240);
  minusButton5.setPosition(800, 275);
  plusButton5.setPosition(1000, 275);
  minusButton6.setPosition(800, 310);
  plusButton6.setPosition(1000, 310);
  minusButton7.setPosition(800, 345);
  plusButton7.setPosition(1000, 345);
  minusButton8.setPosition(800, 380);
  plusButton8.setPosition(1000, 380);
  minusButton9.setPosition(800, 415);
  plusButton9.setPosition(1000, 415);
  minusButton10.setPosition(800, 450);
  plusButton10.setPosition(1000, 450);
  minusButton11.setPosition(800, 485);
  plusButton11.setPosition(1000, 485);
  window.draw(returnButton);
  window.draw(minusButton1);
  window.draw(plusButton1);
  window.draw(minusButton2);
  window.draw(plusButton2);
  window.draw(minusButton3);
  window.draw(plusButton3);
  window.draw(minusButton4);
  window.draw(plusButton4);
  window.draw(minusButton5);
  window.draw(plusButton5);
  window.draw(minusButton6);
  window.draw(plusButton6);
  window.draw(minusButton7);
  window.draw(plusButton7);
  window.draw(carAcc);
  window.draw(carBre);
  window.draw(carMaxSpe);
  window.draw(carsNum);
  window.draw(mutationChapro);
  window.draw(mutationChanopro);
  window.draw(hiddenLay);
  window.draw(carAccValue);
  window.draw(carBreValue);
  window.draw(carMaxSpeValue);
  window.draw(carsNumValue);
  window.draw(mutationChaproValue);
  window.draw(mutationChanoproValue);
  window.draw(hiddenLayValue);
  switch (topologyHiddenLayers) {
    case 4:
    window.draw(neurons4);
    window.draw(neurons4Value);
    window.draw(minusButton11);
    window.draw(plusButton11);
    [[fallthrough]];
    case 3:
    window.draw(neurons3);
    window.draw(neurons3Value);
    window.draw(minusButton10);
    window.draw(plusButton10);
    [[fallthrough]];
    case 2:
    window.draw(neurons2);
    window.draw(neurons2Value);
    window.draw(minusButton9);
    window.draw(plusButton9);
    [[fallthrough]];
    case 1:
    window.draw(neurons1);
    window.draw(neurons1Value);
    window.draw(minusButton8);
    window.draw(plusButton8);
  }
  while (window.pollEvent(event)) {
    if((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
      if(returnButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        return true;
      }
      if(minusButton1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carAccelaration > 0.1) carAccelaration -= 0.05;
      }
      if(plusButton1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carAccelaration < 0.4) carAccelaration += 0.05;
      }
      if(minusButton2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carBrakes > 0.2) carBrakes -= 0.05;
      }
      if(plusButton2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carBrakes < 0.6) carBrakes += 0.05;
      }
      if(minusButton3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carMaxspeed > 2.5) carMaxspeed -= 0.5;
      }
      if(plusButton3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carMaxspeed < 7) carMaxspeed += 0.5;
      }
      if(minusButton4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carsNumber > 5) carsNumber -= 1;
      }
      if(plusButton4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carsNumber < 25) carsNumber += 1;
      }
      if(minusButton5.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(mutationChanceprog > 0) mutationChanceprog -= 1;
      }
      if(plusButton5.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(mutationChanceprog < 10) mutationChanceprog += 1;
      }
      if(minusButton6.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(mutationChancenoprog > 0) mutationChancenoprog -= 1;
      }
      if(plusButton6.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(mutationChancenoprog < 100) mutationChancenoprog += 1;
      }
      if(minusButton7.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(topologyHiddenLayers > 1) topologyHiddenLayers -= 1;
      }
      if(plusButton7.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(topologyHiddenLayers < 4) topologyHiddenLayers += 1;
      }
      if(minusButton8.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[0] > 1) neuronsNumber[0] -= 1;
      }
      if(plusButton8.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[0] < 4) neuronsNumber[0] += 1;
      }
      if(minusButton9.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[1] > 1) neuronsNumber[1] -= 1;
      }
      if(plusButton9.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[1] < 4) neuronsNumber[1] += 1;
      }
      if(minusButton10.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[2] > 1) neuronsNumber[2] -= 1;
      }
      if(plusButton10.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[2] < 4) neuronsNumber[2] += 1;
      }
      if(minusButton11.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[3] > 1) neuronsNumber[3] -= 1;
      }
      if(plusButton11.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[3] < 4) neuronsNumber[3] += 1;
      }
    }
    if (event.type == sf::Event::Closed) {
      window.close();
      return true;
    }
  }







  return false;
}

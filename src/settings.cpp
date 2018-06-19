#include "settings.h"

/*! 
* \brief Konstruktor
* \param carAccelaration Inicjująca wartość dla przyspieszenia samochodu
* \param carBrakes Inicjująca wartość dla siły hamowania
* \param carMaxspeed Inicjująca wartość dla maksymalnej prędkości
* \param carsNumber Inicjująca wartość dla liczby samochodów na mapie
* \param topologyHiddenLayers Inicjująca ilość ukrytych warstw w sieci neuronowej
* \param mutationChanceprog Inicjująca wartość dla szansy na mutację gdy zaszedł postęp
* \param mutationChancenoprog Inicjująca wartość dla szansy na mutację gdy nie zaszedł postęp
* \details W konstruktorze przypisywane są wartości inicjujące obiekt
*/
settings::settings(double carAccelaration, double carBrakes, double carMaxspeed, int carsNumber, int topologyHiddenLayers, int mutationChanceprog, int mutationChancenoprog) {
  this->carAccelaration = carAccelaration;
  this->carBrakes = carBrakes;
  this->carMaxspeed = carMaxspeed;
  this->carsNumber = carsNumber;
  this->topologyHiddenLayers = topologyHiddenLayers;
  this->mutationChanceprog = mutationChanceprog;
  this->mutationChancenoprog = mutationChancenoprog;
  neuronsNumber.push_back(4);
  neuronsNumber.push_back(3);
  neuronsNumber.push_back(1);
  neuronsNumber.push_back(1);
}

/*!
* \brief Metoda zmieniająca ustawienia 
* \param window Referencja do okna 
* \param cars Referencja na vektor przechowujący obiekty samochodów
* \param net Referencja na vektor przechowujący obiekty sieci neronowych
* \param topology Wygląd sieci (ilość neronów w każdej warstwie)
* \param mutationChanceprog wartość szansy na mutacje sieci gdy zaszedł postęp
* \param mutationChancenoprog wartość szansy na mutacje sieci gdy nie zaszedł postęp
* \param carsNumber Referencja na zmienną przechowującą liczbę samochodów
* \details Metoda jest wywoływana po każdym wyjściu z ekranu opcji, tworzy ona obiekty samochodów, sieci z nowymi opcjami wybranymi przez użytkownika
*/
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
    cars.push_back(car(window, carAccelaration, carMaxspeed, carBrakes, window.getSize().x/2.7, window.getSize().y/1.2));
    net.push_back(network(topology));
  }
  cars[carsNumber].cardead();
  mutationChanceprog = this->mutationChanceprog;
  mutationChancenoprog = this->mutationChancenoprog;
}

/*!
* \brief Metoda zmieniająca ustawienia 
* \param window Referencja do okna 
* \param font Referencja na aktualnie wczytaną czcionkę
* \param event Referencja na obiekt zdarzeń biblioteki sfml używana do obsługi opuszczenia programu z tego ekranu
* \details Metoda rysuje na ekranie ekran opcji
*/
bool settings::draw(sf::RenderWindow &window, sf::Font &font, sf::Event &event) {
  sf::Texture textureReturn;
  sf::Sprite returnButton;
  sf::Texture texturePlus;
  sf::Texture textureMinus;
  std::vector<sf::Sprite> plusButton(12);
  std::vector<sf::Sprite> minusButton(12);
  std::vector<sf::Text> description(12);
  std::vector<sf::Text> value(12);
  resolution.x = window.getSize().x;
  resolution.y = window.getSize().y;
  int ResolutionXArray[] = {768, 800, 848, 960, 1024, 1280, 1600};
  int ResolutionYArray[] = {432, 450, 480, 540, 576, 720, 900};
  int resolutionIndex = std::distance(ResolutionXArray, std::find(ResolutionXArray, ResolutionXArray + 7, resolution.x));

  for(int i=0; i<description.size(); i++) {
    description[i].setFont(font);
  }
  for(int i=0; i<value.size(); i++) {
    value[i].setFont(font);
  }
  for(int i=0; i<description.size(); i++) {
    description[i].setCharacterSize(20);
  }
  for(int i=0; i<value.size(); i++) {
    value[i].setCharacterSize(20);
  }
  for(int i=0; i<description.size(); i++) {
    description[i].setPosition(window.getSize().x/15, window.getSize().y/15 + 35 * i);
  }
  for(int i=0; i<value.size(); i++) {
    value[i].setPosition(window.getSize().x/1.5, window.getSize().y/15 + 35 * i);
  }
  description[0].setString("Car accelaration");
  description[1].setString("Car breaking power");
  description[2].setString("Car maximum speed");
  description[3].setString("Cars number");
  description[4].setString("Chance of mutation - progress");
  description[5].setString("Chance of mutation - no progress");
  description[6].setString("Resolution");
  description[7].setString("Number of hidden layers");
  description[8].setString("Number of neurons in first layer");
  description[9].setString("Number of neurons in second layer");
  description[10].setString("Number of neurons in third layer");
  description[11].setString("Number of neurons in fourth layer");
  value[0].setString(std::to_string(carAccelaration));
  value[1].setString(std::to_string(carBrakes));
  value[2].setString(std::to_string(carMaxspeed));
  value[3].setString(std::to_string(carsNumber));
  value[4].setString(std::to_string(mutationChanceprog));
  value[5].setString(std::to_string(mutationChancenoprog));
  value[6].setString(std::to_string(resolution.x) + "x" + std::to_string(resolution.y));
  value[7].setString(std::to_string(topologyHiddenLayers));
  value[8].setString(std::to_string(neuronsNumber[0]));
  value[9].setString(std::to_string(neuronsNumber[1]));
  value[10].setString(std::to_string(neuronsNumber[2]));
  value[11].setString(std::to_string(neuronsNumber[3]));
  if(textureReturn.loadFromFile("../img/return.png")) {
    returnButton.setTexture(textureReturn);
  }
  if(texturePlus.loadFromFile("../img/plus.png")) {
    for(int i=0; i<plusButton.size(); i++) {
      plusButton[i].setTexture(texturePlus);
    }
  }
  if(textureMinus.loadFromFile("../img/minus.png")) {
    for(int i=0; i<minusButton.size(); i++) {
      minusButton[i].setTexture(textureMinus);
    }
  }
  returnButton.setPosition(window.getSize().x/15, 1);
  for(int i=0; i<plusButton.size(); i++) {
    plusButton[i].setPosition(window.getSize().x/1.2, window.getSize().y/15 + 35 * i);
  }
  for(int i=0; i<minusButton.size(); i++) {
    minusButton[i].setPosition(window.getSize().x/1.7, window.getSize().y/15 + 35 * i);
  }

  window.draw(returnButton);
  for(int i=0; i<plusButton.size() - 4; i++) {
    window.draw(plusButton[i]);
  }
  for(int i=0; i<minusButton.size() - 4; i++) {
    window.draw(minusButton[i]);
  }
  for(int i=0; i<description.size() - 4; i++) {
    window.draw(description[i]);
  }
  for(int i=0; i<value.size() - 4; i++) {
    window.draw(value[i]);
  }
  switch (topologyHiddenLayers) {
    case 4:
    window.draw(description[11]);
    window.draw(value[11]);
    window.draw(minusButton[11]);
    window.draw(plusButton[11]);
    [[fallthrough]];
    case 3:
    window.draw(description[10]);
    window.draw(value[10]);
    window.draw(minusButton[10]);
    window.draw(plusButton[10]);
    [[fallthrough]];
    case 2:
    window.draw(description[9]);
    window.draw(value[9]);
    window.draw(minusButton[9]);
    window.draw(plusButton[9]);
    [[fallthrough]];
    case 1:
    window.draw(description[8]);
    window.draw(value[8]);
    window.draw(minusButton[8]);
    window.draw(plusButton[8]);
  }
  while (window.pollEvent(event)) {
    if((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
      if(returnButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        return true;
      }
      if(minusButton[0].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carAccelaration > 0.1) carAccelaration -= 0.05;
      }
      if(plusButton[0].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carAccelaration < 0.4) carAccelaration += 0.05;
      }
      if(minusButton[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carBrakes > 0.2) carBrakes -= 0.05;
      }
      if(plusButton[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carBrakes < 0.6) carBrakes += 0.05;
      }
      if(minusButton[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carMaxspeed > 0.5) carMaxspeed -= 0.5;
      }
      if(plusButton[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carMaxspeed < 7) carMaxspeed += 0.5;
      }
      if(minusButton[3].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carsNumber > 5) carsNumber -= 1;
      }
      if(plusButton[3].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(carsNumber < 25) carsNumber += 1;
      }
      if(minusButton[4].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(mutationChanceprog > 0) mutationChanceprog -= 1;
      }
      if(plusButton[4].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(mutationChanceprog < 10) mutationChanceprog += 1;
      }
      if(minusButton[5].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(mutationChancenoprog > 0) mutationChancenoprog -= 1;
      }
      if(plusButton[5].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(mutationChancenoprog < 100) mutationChancenoprog += 1;
      }
      if(minusButton[6].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(resolution.x > ResolutionXArray[0]) {
          resolutionIndex--;
          window.close();
          window.create(sf::VideoMode(ResolutionXArray[resolutionIndex], ResolutionYArray[resolutionIndex]), "Gierka", sf::Style::Titlebar | sf::Style::Close);
        }
      }
      if(plusButton[6].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(resolution.x < ResolutionXArray[6]) {
          resolutionIndex++;
          window.close();
          window.create(sf::VideoMode(ResolutionXArray[resolutionIndex], ResolutionYArray[resolutionIndex]), "Gierka", sf::Style::Titlebar | sf::Style::Close);
          window.setFramerateLimit(60);
        }
      }
      if(minusButton[7].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(topologyHiddenLayers > 1) topologyHiddenLayers -= 1;
      }
      if(plusButton[7].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(topologyHiddenLayers < 4) topologyHiddenLayers += 1;
      }
      if(minusButton[8].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[0] > 1) neuronsNumber[0] -= 1;
      }
      if(plusButton[8].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[0] < 4) neuronsNumber[0] += 1;
      }
      if(minusButton[9].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[1] > 1) neuronsNumber[1] -= 1;
      }
      if(plusButton[9].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[1] < 4) neuronsNumber[1] += 1;
      }
      if(minusButton[10].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[2] > 1) neuronsNumber[2] -= 1;
      }
      if(plusButton[10].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[2] < 4) neuronsNumber[2] += 1;
      }
      if(minusButton[11].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        if(neuronsNumber[3] > 1) neuronsNumber[3] -= 1;
      }
      if(plusButton[11].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
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

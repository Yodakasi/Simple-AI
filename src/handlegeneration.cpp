#include "handlegeneration.h"

generation::generation(sf::Font &font) {
  generationNum = 0;
  progress = 0;
  bestScore = 0;
  output.resize(2);
  input.resize(5);



  textgen.setFont(font);
  textfit.setFont(font);
  textprog.setFont(font);
  textfitgen.setFont(font);
  textgen.setCharacterSize(12);
  textfit.setCharacterSize(12);
  textfitgen.setCharacterSize(12);
  textprog.setCharacterSize(12);

  textgen.setPosition(0, 70);
  textprog.setPosition(0, 100);
  textfit.setPosition(0, 85);
  textfitgen.setPosition(0, 115);
}


void generation::handleCars(sf::RenderWindow &window, std::vector<car> &cars, std::vector<network> &net, sf::Image &windowImage, std::vector<sf::Vector2f> &mapPoints, int carNumber) {
  if(cars[carNumber].getcarstate()) {
    if(cars[carNumber].checkCollision(cars[carNumber].getBounds(), mapPoints)) {
      cars[carNumber].cardead();
    }
    if((std::time(nullptr) - cars[carNumber].getCarTime()) > 5 && cars[carNumber].getActualSpeed() < 1) {
      cars[carNumber].cardead();
    }
    if((std::time(nullptr) - cars[carNumber].getCarTime()) > 20) {
      cars[carNumber].cardead();
    }

    cars[carNumber].carline(windowImage, cars[carNumber].carPosition(), cars[carNumber].carRotation(), 40, 0);
    cars[carNumber].carline(windowImage, cars[carNumber].carPosition(), cars[carNumber].carRotation() <= 300 ? cars[carNumber].carRotation() + 60 : cars[carNumber].carRotation() - 300, 35, 1);
    cars[carNumber].carline(windowImage, cars[carNumber].carPosition(), cars[carNumber].carRotation() <= 60 ? cars[carNumber].carRotation() + 300 : cars[carNumber].carRotation() - 60, 35, 2);
    cars[carNumber].carline(windowImage, cars[carNumber].carPosition(), cars[carNumber].carRotation() <= 330 ? cars[carNumber].carRotation() + 30 : cars[carNumber].carRotation() - 330, 40, 3);
    cars[carNumber].carline(windowImage, cars[carNumber].carPosition(), cars[carNumber].carRotation() <= 30 ? cars[carNumber].carRotation() + 330 : cars[carNumber].carRotation() - 30, 40, 4);


    input[0] = cars[carNumber].getDistance(cars[carNumber].carPosition(), 0)/60 - 1;
    input[1] = cars[carNumber].getDistance(cars[carNumber].carPosition(), 1)/52.5 - 1;
    input[2] = cars[carNumber].getDistance(cars[carNumber].carPosition(), 2)/52.5 - 1;
    input[3] = cars[carNumber].getDistance(cars[carNumber].carPosition(), 3)/60 - 1;
    input[4] = cars[carNumber].getDistance(cars[carNumber].carPosition(), 4)/60 - 1;

    net[carNumber].feedForward(input);
    net[carNumber].getValues(output);

    cars[carNumber].countScore();
    cars[carNumber].move();
    cars[carNumber].move(output[0], output[1]);



    cars[carNumber].draw(window);

    window.draw(cars[carNumber].getPoint(0));
    window.draw(cars[carNumber].getPoint(1));
    window.draw(cars[carNumber].getPoint(2));
    window.draw(cars[carNumber].getPoint(3));
    window.draw(cars[carNumber].getPoint(4));
  }
}

void generation::handleProgress(std::vector<car> &cars, std::vector<network> &net, std::vector<int> &topology, int carsNumber, int mutationChanceprog, int mutationChancenoprog, double x, double y) {
  int max = 0, secondMax = 0, maxIterator = 0, secondMaxIterator;
  for(int i=0; i<carsNumber; ++i) {
    if(cars[i].getScore() > max) {
      secondMax = max;
      secondMaxIterator = maxIterator;
      max = cars[i].getScore();
      maxIterator = i;
    }
    else if(cars[i].getScore() > secondMax) {
      secondMax = cars[i].getScore();
      secondMaxIterator = i;
    }
  }
  textfitgen.setString("Prev gen fitness: " + std::to_string(max + secondMax));
  if(bestScore - (max + secondMax) >= 0) {
    progress++;
  }
  else {
    progress = 0;

  }
  if(progress < 1) {
    if(bestScore < max + secondMax){
      bestScore = max + secondMax;
      bestNet = net[maxIterator].getNet();
    }
    if(secondMax == 0) secondMax++;
    int share = max/secondMax < 3 ? 55 + (max/secondMax) * 8 : 85;
    textprog.setString("Progress, share: " + std::to_string(share));
    net[maxIterator].mixNets(topology, net[secondMaxIterator].getNet(), share);
    for(int i=0; i<carsNumber; i++) {
      if(i == maxIterator) {
        continue;
      }
      net[i].setNet(topology, bestNet);
      net[i].mutateNet(topology, mutationChanceprog);
    }

  }
  else if(progress % 5 == 0 && progress > 0){
    if(progress > 10) bestScore = max + secondMax;
    assert(bestNet.size() > 0);
    textprog.setString("Random mutations");
    for(int i=0; i<carsNumber; i++) {
      net[i].setNet(topology, bestNet);
      net[i].mutateNet(topology, mutationChancenoprog);
    }

  }
  else {
    assert(bestNet.size() > 0);
    textprog.setString("No progress for: " + std::to_string(progress) + " gen");
    for(int i=0; i<carsNumber; i++) {
      if(i == maxIterator) {
        net[i].setNet(topology, bestNet);
        net[i].mutateNet(topology, mutationChanceprog);
        continue;
      }
      net[i].setNet(topology, bestNet);
      net[i].mutateNet(topology, mutationChanceprog*2);
    }
  }
  generationNum++;
  for(int i=0; i<carsNumber; ++i) {
    cars[i].carReset(x, y);
  }

}
void generation::drawGensInfo(sf::RenderWindow &window) {
  textgen.setString("Generation: " + std::to_string(generationNum));
  textfit.setString("Best fitness: " + std::to_string(bestScore));

  window.draw(textgen);
  window.draw(textfitgen);
  window.draw(textfit);
  window.draw(textprog);
}

void generation::reset() {
  generationNum = 0;
  progress = 0;
  bestScore = 0;
  bestNet.clear();
}

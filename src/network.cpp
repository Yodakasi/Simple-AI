#include "network.h"

/*!
* \brief Konstruktor
* \param topology Wygląd sieci (ilość neronów w każdej warstwie)
* \details 
*/
network::network(std::vector<int> &topology) {
  int numOfLayers = topology.size(); /*! Na podstawie dostarczonej topologii ustala wielkość sieci, */
  for(int i=0; i<numOfLayers; i++) {
    layers.push_back(layer()); 
    int numOfOutputs = i == numOfLayers - 1 ? 0 : topology[i + 1]; /*! także ilość wyjść do następnej warstwy (dla ostatniej będzie ona zerem) */
    for(int j=0; j<=topology[i]; j++) {
      layers.back().push_back(neuron(numOfOutputs, j)); /*! i w końcu przypisuje neuron z odpowiednią ilością wyjść */
    }
    layers.back().back().setOutputval(1.0); /*! oraz ustawia wartość ostatniego neurona w każdej wartswie, jest ona stała i wynosi 1, (neuron ten nazywa się bias) */
  }
}

/*!
* \brief Metoda odpowiedzialna za przekazanie wartości z sensorów samochodu i przekazanie wyników do następnych warstw
* \param input Wartosci przekazane z sensorów samochodów
* \details 
*/
void network::feedForward(std::vector<double> &input) {
  assert(layers[0].size() - 1 == input.size());
  for(unsigned i=0; i<input.size(); i++) {
    layers[0][i].setOutputval(input[i]); /*! Na początku metoda przypisuje wartość każdemu z neronów z pierwszej warstwy wartości z sensorów samochodu, */
  }
  for(unsigned i=1; i<layers.size(); i++) {
    layer &prevLayer = layers[i - 1]; /*! bierze wartości neuronów z poprzedniej warstwy, zaczynając od drugiej warstwy */
    for(unsigned j=0; j<layers[i].size() - 1; j++) {
      layers[i][j].feedForward(prevLayer, j); /*! i przekazuje je do metody klasy neuron */
    }
  }
}

/*!
* \brief Metoda zapisująca wyniki z ostatniej warstwy
* \param values Referencja do vektora do którego zapiszemy otrzymane wartości
*/
void network::getValues(std::vector<double> &values) {
  for(unsigned i=0; i<layers.back().size() - 1; i++) {
    values[i] = (layers[layers.size() - 1][i].getOutputval()); 
  }
}

/*!
* \brief Metoda do mieszania dwóch najlepszych sieci
* \param topology Wygląd sieci (ilość neronów w każdej warstwie)
* \param net Vektor z nową siecią do połączenia
* \param share Procentowy udział lepszej sieci w nowej sieci
* \details  
*/
void network::mixNets(std::vector<int> topology, std::vector<double> net, int share) {
  int netSize = net.size();
  int startNeuron = rand() % (netSize - (netSize * share)/100); /*! Metoda w losowy sposób wybiera miejsce w które zacznie kopiować neurony z drugiej sieci */
  int stopNeuron = (netSize * share)/100 + startNeuron;
  int layersIterator = 0;
  int neuronsIterator = 0;
  int weightIterator = 0;
  for(int i=0; i<netSize; i++) {
    if(i < startNeuron || i > stopNeuron) {
      layers[layersIterator][neuronsIterator].setWeight(weightIterator, net[i]); /*! i przypisze neuronom odpowiednie wartości */
    }
    ++weightIterator;
    if(weightIterator >= topology[layersIterator + 1]) {
      weightIterator = 0;
      ++neuronsIterator;
    }
    if(neuronsIterator > topology[layersIterator]) {
      neuronsIterator = 0;
      ++layersIterator;
    }
  }

}
/*!
* \brief Metoda ustawiająca sieć z podanego parametru
* \param topology Wygląd sieci (ilość neronów w każdej warstwie)
* \param net Vektor z siecią która nadpisze tą w obiekcie 
* \details Zaczynająć od pierwszego neuronu metoda nadpisze wszystkie neurony w sieci
*/
void network::setNet(std::vector<int> topology, std::vector<double> net) {
  int netSize = net.size();
  int layersIterator = 0;
  int neuronsIterator = 0;
  int weightIterator = 0;
  for(int i=0; i<netSize; i++) {
    layers[layersIterator][neuronsIterator].setWeight(weightIterator, net[i]);
    ++weightIterator;
    if(weightIterator >= topology[layersIterator + 1]) {
      weightIterator = 0;
      ++neuronsIterator;
    }
    if(neuronsIterator > topology[layersIterator]) {
      neuronsIterator = 0;
      ++layersIterator;
    }
  }


}

/*!
* \brief Metoda mutująca sieć 
* \param topology Wygląd sieci (ilość neronów w każdej warstwie)
* \param chance Szansa na mutacje neuronu 
* \details Zaczynająć od pierwszego neuronu metoda wylosuje liczebe z przdziału 1 - 100 i jeśli będzie ona ona mniejsza bądź równa parametrowi chance to wylosuje dla aktualnego neuronu nową wagę
*/
void network::mutateNet(std::vector<int> topology, int chance) {
  unsigned layersIterator = 0;
  int neuronsIterator = 0;
  int weightIterator = 0;
  while(layersIterator < topology.size()-1) {
    if((1 + rand() % 100) <= chance) {
      layers[layersIterator][neuronsIterator].setWeight(weightIterator, -1 + rand() / double(RAND_MAX/2.0));
    }
    ++weightIterator;
    if(weightIterator >= topology[layersIterator + 1]) {
      weightIterator = 0;
      ++neuronsIterator;
    }
    if(neuronsIterator > topology[layersIterator]) {
      neuronsIterator = 0;
      ++layersIterator;
    }
  }

}

/*!
* \brief Metoda zwracająca sieć 
* \details Przechodząc przez wszystkie warstwy metoda zapisze wagi wszystkich neuronów do vektora net, następnie go zwróci 
*/
std::vector<double> network::getNet() {
  std::vector<double> net;
  std::vector<double> layerTmp;
  for(unsigned i=0; i<layers.size(); i++) {
    for(unsigned j=0; j<layers[i].size(); j++) {
      layerTmp = layers[i][j].getWeight();
      net.insert(net.end(), layerTmp.begin(), layerTmp.end());
    }
  }
  return net;
}

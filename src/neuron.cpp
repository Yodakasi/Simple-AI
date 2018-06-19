#include "neuron.h"

/*!
* \brief Konstruktor
* \param numOfOutputs liczba wyjść neurona, w praktyce ilość neuronów w następnej warstwie
* \param index numer aktualnie tworzonego neuronu
* \details Metoda ustawi losowo wagi dla każdego neuronu z następnej warstwy
*/
neuron::neuron(int numOfOutputs, int index) {
  for(int i=0; i<numOfOutputs; i++) {
    weights.push_back(-1 + rand() / double(RAND_MAX/2.0));
  }
  this->index = index;
}

/*!
* \brief Metoda wygładająca wartości neuronów
* \param x wartość do wygłądzenia
* \details Metoda przypisze wartości od -1 do 1 dla każdej liczby podanej w parametrze
*/
double neuron::transferFun(double x) {
  return tanh(x);
}

/*!
* \brief Metoda licząca wartość neuronu
* \param prevLayer poprzednia warstwa (wartoścu neuronów wraz z ich wagami)
* \param Myindex index neuronu
* \details Metoda liczy wartość neronu sumując iloczyn neuronów z poprzedniej warstwy z ich wagami i wygładza tą liczbe metodą transferFun
*/
void neuron::feedForward(layer &prevLayer, int Myindex) {
  double sum = 0.0;
  for(unsigned i=0; i<prevLayer.size(); i++) {
    sum += prevLayer[i].outputVal * prevLayer[i].weights[Myindex];
  }
  outputVal = transferFun(sum);
}

/*!
* \brief Metoda zwracająca wage
* \details Zwracana jest waga neuronu
*/
std::vector<double> neuron::getWeight() {
  return weights;
}

/*!
* \brief Metoda ustawia wage
* \param index Numer neuronu
* \param newWeight Nowa waga neuronu
* \details ustawiana jest waga neuronu
*/
void neuron::setWeight(int index, double newWeight) {
  weights[index] = newWeight;
}

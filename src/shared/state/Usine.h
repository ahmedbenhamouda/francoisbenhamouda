#ifndef STATE__USINE__H
#define STATE__USINE__H


namespace state {
  class Position;
  class Unite;
}

#include "Batiment.h"
#include "Position.h"
#include "Unite.h"

namespace state {

  /// class Usine - 
  template <class T>
  class Usine : public Batiment {
    // Attributes
  public:
    Position position;
    int color;
    int id_b     = 1;
    // Operations
  public:
    Usine ();
    Usine(Position position, int color);
    Unite creerU (int argent, Position& position, T* pt);
    int getId_b ();
    int getColor ();
    int getTileId ();
    ~Usine ();
    // Setters and Getters
  };
template<class T>
Usine<T>::~Usine() {
}


template<class T>
Usine<T>::Usine(Position position, int color) {
	this->position = position;
	this->color = color;
}
template<class T>
int Usine<T>::getColor() {
    return this->color;
}

template<class T>
int Usine<T>::getId_b() {
    return this->id_b;
}

template<class T>
int Usine<T>::getTileId() {
    return (4*this->getId_b()+this->getColor());
}

template<class T>
Unite Usine<T>::creerU(int argent, Position& position, T* pt) {
}




};

#endif

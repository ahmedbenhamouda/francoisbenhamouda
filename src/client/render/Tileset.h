
#ifndef RENDER__TILESET__H
#define RENDER__TILESET__H

#include <string>
#include <vector>

namespace render {
  class Tile;
}

#include "Tile.h"


namespace render {

  /// class Tileset - 
  template <class T>
  class Tileset {
    // Associations
    // Attributes
    std::vector<Tile> tiles;
    std::string filename;
  public:
    T t;
    // Operations
  public:
    Tileset();
    Tileset (std::string filename);
    ~Tileset();
    int getCellWidth() const;
    int getCellHeight() const;
    std::string getImageFile() const;
    Tile& getTile (T* pt);
    // Setters and Getters
  };

template<class T>
Tileset<T>::Tileset () {
}

template<class T>
Tileset<T>::Tileset (std::string filename) : filename(filename) {
    // peuplement de tiles
    if (filename=="res/terrain.png") {
            //terrain
            Tile routeh(400,16,16,16);
            Tile routev(400,0,16,16);
            Tile routedd(416,0,16,16);
            Tile routegd(448,0,16,16);
            Tile routedu(416,32,16,16);
            Tile routegu(448,32,16,16);
            Tile plaine(16,16,16,16);
            Tile foret(240,16,16,16);
            Tile montagne(48,0,16,16);

            tiles = {plaine,foret,montagne,routeh,routev,routedu,routegu,routedd,routegd};
    }

    if (filename=="res/batiments.png") {
            //QG
            Tile qgRouge(0,31,16,31);
            Tile qgBleu(0,62,16,31);
            Tile qgVert(0,93,16,31);
            Tile qgJaune(0,124,16,31);
            //Usine
            Tile usineRouge(32,31,16,31);
            Tile usineBleu(32,62,16,31);
            Tile usineVert(32,93,16,31);
            Tile usineJaune(32,124,16,31);

            tiles = {qgRouge,qgBleu,qgVert,qgJaune,usineRouge,usineBleu,usineVert,usineJaune};
    }

    if (filename=="res/units.png") {
            //Infantry
            Tile infantryRouge(0,0,16,16);
            Tile infantryBleu(0,16,16,16);
            Tile infantryVert(0,32,16,16);
            Tile infantryJaune(0,48,16,16);
	    //Mech
            Tile mechRouge(16,0,16,16);
            Tile mechBleu(16,16,16,16);
            Tile mechVert(16,32,16,16);
            Tile mechJaune(16,48,16,16);
            //Recon
            Tile reconRouge(32,0,16,16);
            Tile reconBleu(32,16,16,16);
            Tile reconVert(32,32,16,16);
            Tile reconJaune(32,48,16,16);
            //Tank
            Tile tankRouge(64,0,16,16);
            Tile tankBleu(64,16,16,16);
            Tile tankVert(64,32,16,16);
            Tile tankJaune(64,48,16,16);
            //HTank
            Tile hTankRouge(80,0,16,16);
            Tile hTankBleu(80,16,16,16);
            Tile hTankVert(80,32,16,16);
            Tile hTankJaune(80,48,16,16);
            tiles = {infantryRouge,infantryBleu,infantryVert,infantryJaune,mechRouge,mechBleu,mechVert,mechJaune,reconRouge,reconBleu,reconVert,reconJaune,tankRouge,tankBleu,tankVert,tankJaune,hTankRouge,hTankBleu,hTankVert,hTankJaune};
    }
    if (filename=="res/misc.png") {
            //carre
            Tile carre(0,0,16,16);

	    //explosion
            Tile explosion(16,0,16,16);

            tiles = {carre,explosion};
    }
    if (filename=="res/flags.png") {
            //flags
            Tile flagRouge(0,0,16,16);
	    Tile flagBleu(16,0,16,16);
            Tile flagVert(32,0,16,16);
	    Tile flagJaune(48,0,16,16);

            tiles = {flagRouge,flagBleu,flagVert,flagJaune};
    }
}

template<class T>
Tileset<T>::~Tileset() {
}

template<class T>
int Tileset<T>::getCellWidth() const {
    return tiles[0].getWidth();
}

template<class T>
int Tileset<T>::getCellHeight() const {
    return tiles[0].getHeight();
}

template<class T>
std::string Tileset<T>::getImageFile() const {
    return filename;
}

template<class T>
Tile& Tileset<T>::getTile(T* pt) {
    int i = pt->getTileId();
    return this->tiles[i];
}
}

#endif

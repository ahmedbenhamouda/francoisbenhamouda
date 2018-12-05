
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
	    Tile qgViolet(0,155,16,31);
            Tile qgBrun(0,186,16,31);
            Tile qgBleuF(0,217,16,31);
            Tile qgRougeF(0,248,16,31);
            //Usine
            Tile usineRouge(32,31,16,31);
            Tile usineBleu(32,62,16,31);
            Tile usineVert(32,93,16,31);
            Tile usineJaune(32,124,16,31);
	    Tile usineViolet(32,155,16,31);
            Tile usineBrun(32,186,16,31);
            Tile usineBleuF(32,217,16,31);
            Tile usineRougeF(32,248,16,31);

            tiles = {qgRouge,qgBleu,qgVert,qgJaune,qgViolet,qgBrun,qgBleuF,qgRougeF,usineRouge,usineBleu,usineVert,usineJaune,usineViolet,usineBrun,usineBleuF,usineRougeF};
    }

    if (filename=="res/units.png") {
            //Infantry
            Tile infantryRouge(0,0,16,16);
            Tile infantryBleu(0,16,16,16);
            Tile infantryVert(0,32,16,16);
            Tile infantryJaune(0,48,16,16);
            Tile infantryViolet(0,64,16,16);
            Tile infantryBrun(0,80,16,16);
            Tile infantryBleuF(0,96,16,16);
            Tile infantryRougeF(0,112,16,16);
	    //Infantry Flag
            Tile infantryRougeFlag(16,0,16,16);
            Tile infantryBleuFlag(16,16,16,16);
            Tile infantryVertFlag(16,32,16,16);
            Tile infantryJauneFlag(16,48,16,16);
            Tile infantryVioletFlag(16,64,16,16);
            Tile infantryBrunFlag(16,80,16,16);
            Tile infantryBleuFFlag(16,96,16,16);
            Tile infantryRougeFFlag(16,112,16,16);
            //Mech
            Tile mechRouge(32,0,16,16);
            Tile mechBleu(32,16,16,16);
            Tile mechVert(32,32,16,16);
            Tile mechJaune(32,48,16,16);
            Tile mechViolet(32,64,16,16);
            Tile mechBrun(32,80,16,16);
            Tile mechBleuF(32,96,16,16);
            Tile mechRougeF(32,112,16,16);
	    //Mech Flag
            Tile mechRougeFlag(48,0,16,16);
            Tile mechBleuFlag(48,16,16,16);
            Tile mechVertFlag(48,32,16,16);
            Tile mechJauneFlag(48,48,16,16);
            Tile mechVioletFlag(48,64,16,16);
            Tile mechBrunFlag(48,80,16,16);
            Tile mechBleuFFlag(48,96,16,16);
            Tile mechRougeFFlag(48,112,16,16);
	    //Recon
            Tile reconRouge(64,0,16,16);
            Tile reconBleu(64,16,16,16);
            Tile reconVert(64,32,16,16);
            Tile reconJaune(64,48,16,16);
            Tile reconViolet(64,64,16,16);
            Tile reconBrun(64,80,16,16);
            Tile reconBleuF(64,96,16,16);
            Tile reconRougeF(64,112,16,16);
	    //Recon Flag
            Tile reconRougeFlag(80,0,16,16);
            Tile reconBleuFlag(80,16,16,16);
            Tile reconVertFlag(80,32,16,16);
            Tile reconJauneFlag(80,48,16,16);
            Tile reconVioletFlag(80,64,16,16);
            Tile reconBrunFlag(80,80,16,16);
            Tile reconBleuFFlag(80,96,16,16);
            Tile reconRougeFFlag(80,112,16,16);
            //Tank
            Tile tankRouge(96,0,16,16);
            Tile tankBleu(96,16,16,16);
            Tile tankVert(96,32,16,16);
            Tile tankJaune(96,48,16,16);
            Tile tankViolet(94,64,16,16);
            Tile tankBrun(96,80,16,16);
            Tile tankBleuF(96,96,16,16);
            Tile tankRougeF(96,112,16,16);
	    //Tank Flag
            Tile tankRougeFlag(112,0,16,16);
            Tile tankBleuFlag(112,16,16,16);
            Tile tankVertFlag(112,32,16,16);
            Tile tankJauneFlag(112,48,16,16);
            Tile tankVioletFlag(112,64,16,16);
            Tile tankBrunFlag(112,80,16,16);
            Tile tankBleuFFlag(112,96,16,16);
            Tile tankRougeFFlag(112,112,16,16);
            //HTank
            Tile hTankRouge(128,0,16,16);
            Tile hTankBleu(128,16,16,16);
            Tile hTankVert(128,32,16,16);
            Tile hTankJaune(128,48,16,16);
            Tile hTankViolet(128,64,16,16);
            Tile hTankBrun(128,80,16,16);
            Tile hTankBleuF(128,96,16,16);
            Tile hTankRougeF(128,112,16,16);
	    //HTank Flag
            Tile hTankRougeFlag(144,0,16,16);
            Tile hTankBleuFlag(144,16,16,16);
            Tile hTankVertFlag(144,32,16,16);
            Tile hTankJauneFlag(144,48,16,16);
            Tile hTankVioletFlag(144,64,16,16);
            Tile hTankBrunFlag(144,80,16,16);
            Tile hTankBleuFFlag(144,96,16,16);
            Tile hTankRougeFFlag(144,112,16,16);
            tiles = {infantryRouge,infantryBleu,infantryVert,infantryJaune,infantryViolet,infantryBrun,infantryBleuF,infantryRougeF,mechRouge,mechBleu,mechVert,mechJaune,mechViolet,mechBrun,mechBleuF,mechRougeF,reconRouge,reconBleu,reconVert,reconJaune,reconViolet,reconBrun,reconBleuF,reconRougeF,tankRouge,tankBleu,tankVert,tankJaune,tankViolet,tankBrun,tankBleuF,tankRougeF,hTankRouge,hTankBleu,hTankVert,hTankJaune,hTankViolet,hTankBrun,hTankBleuF,hTankRougeF,infantryRougeFlag,infantryBleuFlag,infantryVertFlag,infantryJauneFlag,infantryVioletFlag,infantryBrunFlag,infantryBleuFFlag,infantryRougeFFlag,mechRougeFlag,mechBleuFlag,mechVertFlag,mechJauneFlag,mechVioletFlag,mechBrunFlag,mechBleuFFlag,mechRougeFFlag,reconRougeFlag,reconBleuFlag,reconVertFlag,reconJauneFlag,reconVioletFlag,reconBrunFlag,reconBleuFFlag,reconRougeFFlag,tankRougeFlag,tankBleuFlag,tankVertFlag,tankJauneFlag,tankVioletFlag,tankBrunFlag,tankBleuFFlag,tankRougeFFlag,hTankRougeFlag,hTankBleuFlag,hTankVertFlag,hTankJauneFlag,hTankVioletFlag,hTankBrunFlag,hTankBleuFFlag,hTankRougeFFlag};
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
            Tile flagViolet(64,0,16,16);
	    Tile flagBrun(80,0,16,16);
            Tile flagBleuF(96,0,16,16);
	    Tile flagRougeF(112,0,16,16);

            tiles = {flagRouge,flagBleu,flagVert,flagJaune,flagViolet,flagBrun,flagBleuF,flagRougeF};
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

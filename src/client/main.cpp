#include <iostream>
#include <string>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"

using namespace std;
using namespace state;

void tests() {
    // test sur la classe Position
    Position* pos = new Position(5, 1);
    cout<<"Pos x : "<<pos->getX()<<", pos y : "<<pos->getY()<<"."<<endl;

    // test sur la classe TerrainTab
    std::vector<std::vector<TerrainTypeId>> defaultVector {{plaine,plaine,plaine,plaine,plaine,plaine,plaine,plaine},
                                                           {route,route,route,route,plaine,foret,plaine,plaine},
                                                           {plaine,plaine,plaine,route,plaine,plaine,foret,plaine},
                                                           {plaine,plaine,plaine,route,plaine,plaine,plaine,plaine},
                                                           {plaine,foret,plaine,route,route,route,plaine,plaine},
                                                           {plaine,foret,plaine,route,plaine,route,route,route},
                                                           {plaine,plaine,route,route,montagne,montagne,plaine,plaine},
                                                           {plaine,plaine,route,plaine,plaine,plaine,plaine,plaine}};
    TerrainTab* terrainTab = new TerrainTab(defaultVector);
    cout<<"Terrain : "<<terrainTab->get(*pos)<<endl;
    Unite* U = new Unite(*pos, 0);
    cout<<"la position de l'unité est :"<<U->position.getX()<<","<<U->position.getY()<<"."<<endl;
    Position* pos2 = new Position(2, 4);
    Batiment* B = new Batiment(*pos2, 1);
    cout<<"la position du batiment est :"<<B->position.getX()<<","<<B->position.getY()<<"."<<endl;
    Position* pos3 = new Position(6, 3);
    Unite* U2 = new Infantry(*pos3, 0);
    cout<<"la position de l'unité est :"<<U2->position.getX()<<","<<U2->position.getY()<<"."<<endl;
    delete pos2;
    delete pos;
    delete terrainTab;
    delete U;
    delete B;
    delete pos3;
    delete U2;
}

int main(int argc,char* argv[]) 
{
    //Exemple exemple;
    //exemple.setX(53);

    if (argc < 2) {
        cout << "Missing the \"state\" argument." << endl;
    } else if (argc > 2) {
        cout << "Too many arguments." << endl;
    } else {
        string myString(argv[1]);
        if (myString != "state") {
            cout << "Invalid argument." << endl;
        } else {
            // Tests unitaires
            tests();
        }
    }
    return 0;
}

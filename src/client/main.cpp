#include <iostream>
#include <string>
#include <map>
#include <memory>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

void tests() {
    // création d'objets Position
    unique_ptr<Position> pos (new Position(5, 1));
    unique_ptr<Position> pos2 (new Position(2, 4));
    unique_ptr<Position> pos3 (new Position(6, 3));

    // création d'un objet TerrainTab
    std::vector<std::vector<TerrainTypeId>> defaultVector {{plaine,plaine,plaine,plaine,plaine,plaine,plaine,plaine},
                                                           {route,route,route,route,plaine,foret,plaine,plaine},
                                                           {plaine,plaine,plaine,route,plaine,plaine,foret,plaine},
                                                           {plaine,plaine,plaine,route,plaine,plaine,plaine,plaine},
                                                           {plaine,foret,plaine,route,route,route,plaine,plaine},
                                                           {plaine,foret,plaine,route,plaine,route,route,route},
                                                           {plaine,plaine,route,route,montagne,montagne,plaine,plaine},
                                                           {plaine,plaine,route,plaine,plaine,plaine,plaine,plaine}};
    unique_ptr<TerrainTab> terrainTab (new TerrainTab(defaultVector));

    // création d'objets Unite
    unique_ptr<Unite> U (new Unite(*pos, 0));
    unique_ptr<Unite> U2 (new HTank(*pos3, 0));

    // création d'un objet Batiment
    unique_ptr<Batiment> B (new Batiment(*pos2, 1));

    // création d'un objet Terrain
    std::vector<std::vector<Unite*>> unites (8, std::vector<Unite*>(8));
    unites[U->position.getY()][U->position.getX()] = U.get();
    unites[U2->position.getY()][U2->position.getX()] = U2.get();
    std::vector<std::vector<Batiment*>> batiments (8, std::vector<Batiment*>(8));
    batiments[B->position.getY()][B->position.getX()] = B.get();

    unique_ptr<Terrain> terrain(new Terrain(unites, batiments, *terrainTab));

    // creation d'un objet Jeu
    unique_ptr<Jeu> jeu(new Jeu(terrain.get()));
    
/*    // test sur l'attribut etatJeu de la classe Jeu
    Terrain* newTerrain = jeu->etatJeu;
    cout<<"Terrain à l'adresse "<<newTerrain<<"."<<endl;

    // test sur TerrainTab
    cout<<"Le type de terrain à la position ("<<pos->getX()<<","<<pos->getY()<<") est : "<<newTerrain->getGround(*pos)<<"."<<endl;

    // tests sur Unite
    Unite* foundUnit = newTerrain->getUnite(*pos3);
    cout<<"Unité "<<foundUnit<<" trouvée à la position ("<<foundUnit->position.getX()<<","<<foundUnit->position.getY()<<")."<<endl;
    cout<<"la vie de l'unité est :"<<foundUnit->getvie()<<"."<<endl;
    cout<<"La distance max de déplacement de l'unité est :"<<foundUnit->getmvt()<<"."<<endl;
    // test mouvement possible
    std::vector<Position> moveset = foundUnit->getLegalMove(); 
    cout<<"Liste des mouvements possibles : "<<endl;
    for (Position pos : moveset) {
	cout<<" * ("<<pos.getX()<<","<<pos.getY()<<")"<<endl;
    }
    //delete foundUnit;

    // Test critique
    Unite* noUnit = newTerrain->getUnite(*pos2);
    cout<<noUnit<<" n'existe pas."<<endl;
    //delete noUnit;

    // test sur Batiment
    Batiment* foundBat = newTerrain->getBatiment(*pos2);
    cout<<"Batiment "<<foundBat<<" trouvé à la position ("<<foundBat->position.getX()<<","<<foundBat->position.getY()<<")."<<endl;
    //delete foundBat;

    //delete newTerrain;*/
}

int main(int argc,char* argv[]) 
{
    //Exemple exemple;
    //exemple.setX(53);

    if (argc < 2) {
        cout << "Missing the \"render\" argument." << endl;
    } else if (argc > 2) {
        cout << "Too many arguments." << endl;
    } else {
        string myString(argv[1]);
        if (myString != "render") {
            cout << "Invalid argument." << endl;
        } else {
            // Tests unitaires
            tests();
        }
    }

    Unite u;
    int i = 12;
    i = u;
    cout << i << endl;
    return 0;
}

}

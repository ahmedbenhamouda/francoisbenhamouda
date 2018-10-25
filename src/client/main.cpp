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
    unique_ptr<Unite> U2 (new Infantry(*pos3, 0));

    //teste 1 sur les unites


    cout<<"la vie de l'unité est :"<<U2->getvie()<<"."<<endl;
    cout<<"La distance max de déplacement de l'unité est :"<<U2->getmvt()<<"."<<endl;
/*
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
*/    
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

void renderTest() {
    // Test with Unite
    unique_ptr<Position> pos (new Position(5, 1));
    unique_ptr<Unite> unit (new Infantry(*pos, 2));
    render::TileSet<Unite> test("res/units.png");
    Tile newTile = test.getTile(unit.get());
    cout<<"x : "<<newTile.getX()<<", y : "<<newTile.getY()<<", Height : "<<newTile.getHeight()<<", Width : "<<newTile.getWidth()<<endl;

    // Test with Batiment
    unique_ptr<Batiment> batiment (new state::Usine<Infantry>(*pos, 0));
    render::TileSet<Batiment> test2("res/batiments.png");
    Tile batTile = test2.getTile(batiment.get());
    cout<<"x : "<<batTile.getX()<<", y : "<<batTile.getY()<<", Height : "<<batTile.getHeight()<<", Width : "<<batTile.getWidth()<<endl;

    // création d'un objet TerrainTab
    std::vector<std::vector<TerrainTypeId>> defaultVector {{plaine,plaine,plaine,plaine,plaine,plaine,plaine,plaine},
                                                           {route,route,route,route,plaine,foret,plaine,plaine},
                                                           {plaine,plaine,plaine,route,plaine,plaine,foret,plaine},
                                                           {plaine,plaine,plaine,route,plaine,plaine,plaine,plaine},
                                                           {plaine,foret,plaine,route,route,route,plaine,plaine},
                                                           {plaine,foret,plaine,route,plaine,route,route,route},
                                                           {plaine,plaine,route,route,montagne,montagne,plaine,plaine},
                                                           {plaine,plaine,route,plaine,plaine,plaine,plaine,plaine}};

    // Test with TerrainTypeId
    unique_ptr<TerrainTile> terrainTile(new TerrainTile(defaultVector[0][0]));
    render::TileSet<TerrainTile> test3("res/terrain.png");
    Tile caseTile = test3.getTile(terrainTile.get());
    cout<<"x : "<<caseTile.getX()<<", y : "<<caseTile.getY()<<", Height : "<<caseTile.getHeight()<<", Width : "<<caseTile.getWidth()<<endl;

    /*// création d'objets Unite
    unique_ptr<Position> pos3 (new Position(6, 3));
    unique_ptr<Unite> U (new Infantry(*pos3, 0));

    //teste sur les unites
    cout<<"la vie de l'unité est :"<<U->getvie()<<"."<<endl;
    cout<<"La distance max de déplacement de l'unité est :"<<U->getmvt()<<"."<<endl;


   // création d'objets Usine
    unique_ptr<Position> pos2 (new Position(7, 2));
    unique_ptr<Batiment> B (new state::Usine<Infantry>(*pos2, 1));

    //teste sur l'usine
    cout<<"la couleur du batiment est :"<<B->getColor()<<"."<<endl;
    cout<<"L'identité du batiment est :"<<B->getId_b()<<"."<<endl;*/
    //unique_ptr<Surface> surf(new Surface());
    //surf->loadTexture("res/terrain.png");
    unique_ptr<render::Surface> surf(new render::Surface());
    surf->loadTexture(test3.getImageFile());
    surf->initQuads(64);
    //for (int i=0; i<8; i++) {
        //for (int j=0; j<8; j++) {
    surf->setSpriteLocation(0,0,8,16);
    surf->setSpriteTexture(0,0,8,caseTile);
	//}
    //}
    sf::RenderWindow window(sf::VideoMode(800,600), "window");
    sf::Event event;
    while(window.pollEvent(event))
    {
	if(event.type == sf::Event::Closed) {
	    window.close();
	}
	window.clear();
	window.draw(*surf);
	window.display(); 
    }

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
            //tests();
	    renderTest();
        }
    }
    return 0;
}



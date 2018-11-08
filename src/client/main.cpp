#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <thread>
#include <chrono>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"
#include "render.h"
#include "engine.h"

using namespace std;
using namespace state;
using namespace render;
using namespace engine;

void displayWindow(Layers* layers) {
	sf::RenderWindow window(sf::VideoMode(256,256), "Advance Wars");
		window.setVerticalSyncEnabled(false);
		while(window.isOpen()) {
			sf::Event event;
			while(window.pollEvent(event)) {
				if(event.type == sf::Event::Closed) {
					window.close();
				}
			}
			layers->displayLayers (&window);
		}
	
}

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

    //test 1 sur les unites


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
    unique_ptr<Unite> unit (new HTank(*pos, 2));
    unique_ptr<Position> pos3 (new Position(5, 2));
    unique_ptr<Unite> unit2 (new Infantry(*pos3, 1));
    unique_ptr<Position> pos4 (new Position(6, 2));
    unique_ptr<Unite> unit3 (new Tank(*pos4, 1));
    cout<<"la vie de l'unité du jouer 1 est:"<<unit->getvie()<<"."<<endl;
    cout<<"la puissance de l'unité du jouer 1 est:"<<unit->getpuissance()<<"."<<endl;
    //unit2->setpuissance(100);
    unit2->attacker(unit.get());
    cout<<"la nouvelle vie de l'unité du jouer 1 après être attacké est:"<<unit->getvie()<<"."<<endl;
    cout<<"la nouvelle puissance de l'unité du jouer 1 après être attacké est:"<<unit->getpuissance()<<"."<<endl;
    unit3->attacker(unit.get());
    cout<<"la nouvelle vie de l'unité du jouer 1 après être attacké pour la deuxième fois est:"<<unit->getvie()<<"."<<endl;
    cout<<"la nouvelle puissance de l'unité du jouer 1 après être attacké pour la deuxième fois est:"<<unit->getpuissance()<<"."<<endl;
    unit2->attacker(unit.get());
    cout<<"la nouvelle vie de l'unité du jouer 1 après être attacké pour la troisème fois est:"<<unit->getvie()<<"."<<endl;
    cout<<"la nouvelle puissance de l'unité du jouer 1 après être attacké pour la troisième fois est:"<<unit->getpuissance()<<"."<<endl;


    // Test with Batiment
    unique_ptr<Position> pos2 (new Position(4, 3));
    unique_ptr<Batiment> batiment (new state::Usine(*pos2, 0));

    // création d'un objet TerrainTab
    vector<vector<TerrainTypeId>> defaultVector {{plaine,plaine,plaine,plaine,plaine,plaine,plaine,plaine},
                                                           {route,route,route,route,plaine,foret,plaine,plaine},
                                                           {plaine,plaine,plaine,route,plaine,plaine,foret,plaine},
                                                           {plaine,plaine,plaine,route,plaine,plaine,plaine,plaine},
                                                           {plaine,foret,plaine,route,route,route,plaine,plaine},
                                                           {plaine,foret,plaine,route,plaine,route,route,route},
                                                           {plaine,plaine,route,route,montagne,montagne,plaine,plaine},
                                                           {plaine,plaine,route,plaine,plaine,plaine,plaine,plaine}};
	unique_ptr<TerrainTab> terrainTab (new TerrainTab(defaultVector));
    
    // création d'un objet Terrain
    vector<Unite*> unites;
    unites.push_back(unit.get());
    unites.push_back(unit2.get());

    vector<Batiment*> batiments;
    batiments.push_back(batiment.get());

    unique_ptr<Terrain> terrain(new Terrain(unites, batiments, *terrainTab));

    // Creation d'objets Tileset
    render::Tileset<state::Unite> uniteTileset("res/units.png");
    render::Tileset<state::Batiment> batimentTileset("res/batiments.png");
    render::Tileset<state::TerrainTile> terrainTileset("res/terrain.png"); 

    // creation d'un objet Layers
    unique_ptr<Layers> layers(new Layers(terrain.get(), &uniteTileset,  &batimentTileset, &terrainTileset));
    layers->setUniteSurface ();
    layers->setBatimentSurface ();
    layers->setTerrainSurface ();
    thread th(displayWindow, layers.get());
    th.join();
}

void engineTest() {
    // Creation d'objets Unite
    unique_ptr<Unite> unit (new HTank(Position(5, 1), 2));
    unique_ptr<Unite> unit2 (new Infantry(Position(5, 2), 1));
    unique_ptr<Unite> unit3 (new Tank(Position(6, 1), 1));

    // Creation d'objets Batiment

    unique_ptr<Batiment> batiment (new QG(Position(2, 5), 3));
    unique_ptr<Batiment> batiment2 (new Usine(Position(4, 3), 0));



    // création d'un objet TerrainTab
    vector<vector<TerrainTypeId>> defaultVector {{plaine,plaine,plaine,plaine,plaine,plaine,plaine,plaine},
                                                           {route,route,route,route,plaine,foret,plaine,plaine},
                                                           {plaine,plaine,plaine,route,plaine,plaine,foret,plaine},
                                                           {plaine,plaine,plaine,route,plaine,plaine,plaine,plaine},
                                                           {plaine,foret,plaine,route,route,route,plaine,plaine},
                                                           {plaine,foret,plaine,route,plaine,route,route,route},
                                                           {plaine,plaine,route,route,montagne,montagne,plaine,plaine},
                                                           {plaine,plaine,route,plaine,plaine,plaine,plaine,plaine}};
    unique_ptr<TerrainTab> terrainTab (new TerrainTab(defaultVector));
    
    // création d'un objet Terrain
    vector<Unite*> unites;
    unites.push_back(unit.get());
    unites.push_back(unit2.get());
    unites.push_back(unit3.get());

    vector<Batiment*> batiments;
    batiments.push_back(batiment.get());
    batiments.push_back(batiment2.get());

    unique_ptr<Terrain> terrain(new Terrain(unites, batiments, *terrainTab));


    // Creation d'un objet Jeu
    unique_ptr<Jeu> jeu(new Jeu(terrain.get())); 

    // Creation d'un objet Engine
    unique_ptr<Engine> engine(new Engine(jeu.get()));

    // Creation d'objets Tileset
    render::Tileset<state::Unite> uniteTileset("res/units.png");
    render::Tileset<state::Batiment> batimentTileset("res/batiments.png");
    render::Tileset<state::TerrainTile> terrainTileset("res/terrain.png"); 

    // creation d'un objet Layers
    unique_ptr<Layers> layers(new Layers(terrain.get(), &uniteTileset,  &batimentTileset, &terrainTileset));
    layers->setUniteSurface ();
    layers->setBatimentSurface ();
    layers->setTerrainSurface ();

    // Creation d'un thread dedie a l'affichage
    thread th(displayWindow, layers.get());
    cout<<"Initializing the game..."<<endl;

    // Creation d'une unite Infantry
    this_thread::sleep_for(chrono::seconds(5));
    cout<<"=> CreateUnitCommand(Position(4, 3), color))"<<endl;
    unique_ptr<CreateUnitCommand> cmd0(new CreateUnitCommand(Position(4, 3),0));
    engine->addCommand(cmd0.get());
    engine->update();
    layers->setUniteSurface (); // update de l'affichage

    // Deplacement de unite Infantry
    this_thread::sleep_for(chrono::seconds(5));
    cout<<"=> MoveUnitCommande(Position(4,3), Position(6,3))"<<endl;
    unique_ptr<MoveUnitCommand> cmd1(new MoveUnitCommand(Position(4,3),Position(6,3)));
    engine->addCommand(cmd1.get());
    engine->update();
    layers->setUniteSurface (); // update de l'affichage


    // Attaque de l'unite HTank
    this_thread::sleep_for(chrono::seconds(5));
    cout<<"la vie de l'unité du jouer 1 est:"<<unit->getvie()<<"."<<endl;
    cout<<"la puissance de l'unité du jouer 1 est:"<<unit->getpuissance()<<"."<<endl;
    cout<<"=> AttackUnitCommand(Position(5,2), Position(5,1))"<<endl;
    unique_ptr<AttackUnitCommand> cmd2(new AttackUnitCommand(Position(5,2),Position(5,1)));
    engine->addCommand(cmd2.get());
    engine->update();
    layers->setUniteSurface (); // update de l'affichage

    cout<<"la nouvelle vie de l'unité du jouer 1 après être attacké pour la première fois est:"<<unit->getvie()<<"."<<endl;
    cout<<"la nouvelle puissance de l'unité du jouer 1 après être attacké pour la première fois est:"<<unit->getpuissance()<<"."<<endl;


    // TODO : Coder proprement la méthode deleteUnite()
    // Supression de l'unite Infantry
    /*this_thread::sleep_for(chrono::seconds(5));
    cout<<"=> DeleteUnitCommand(Position(5,2))"<<endl;
    unique_ptr<DeleteUnitCommand> cmd3(new DeleteUnitCommand(Position(5,2)));
    engine->addCommand(cmd3.get());
    engine->update();
    layers->setUniteSurface (); // update de l'affichage*/

    //thread th(displayWindow, layers.get());
    th.join();
}

int main(int argc,char* argv[]) 
{
    //Exemple exemple;
    //exemple.setX(53);

    if (argc < 2) {
        cout << "Missing the \"engine\" argument." << endl;
    } else if (argc > 2) {
        cout << "Too many arguments." << endl;
    } else {
        string myString(argv[1]);
        if (myString != "engine") {
            cout << "Invalid argument." << endl;
        } else {
            // Tests unitaires
            //tests();
	    //renderTest();
	    engineTest();
        }
    }
    return 0;
}



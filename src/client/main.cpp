#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include "state/carte.h"
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

mutex m1;

void displayWindow(Layers* layers) {
	sf::RenderWindow window(sf::VideoMode(640,640), "Advance Wars");
		window.setVerticalSyncEnabled(false);
		while(window.isOpen()) {
			sf::Event event;
			while(window.pollEvent(event)) {
				if(event.type == sf::Event::Closed) {
					window.close();
				}
				if(event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left) {
					int px = event.mouseButton.x/32;
					int py = event.mouseButton.y/32;
					//cout<<"("<<px<<","<<py<<")"<<endl;
					m1.lock();
					layers->sendUnitCommand (Position(px,py));
					m1.unlock();
				}
				if(event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::Escape) {
					m1.lock();
					layers->sendTurnCommand();
					m1.unlock();
				}
			}
			layers->setUniteSurface ();
			layers->setFlagSurface ();
			layers->setMiscSurface ();
			layers->displayLayers (&window);
		}
	
}

void runEngine(Engine* engine) {
	//cout<<engine->commands.size()<<endl;
	while(1) {
		//if (engine->commands[0]) {
			m1.lock();
			engine->update();
			m1.unlock();
		//}
	}
}

/*void tests() {
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
    
    // test sur l'attribut etatJeu de la classe Jeu
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

    //delete newTerrain;
}*/

/*void renderTest() {
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
}*/





/*void engineTest() {
    // Creation d'objets Unite
    unique_ptr<Unite> unit (new HTank(Position(5, 1), 2));
    unique_ptr<Unite> unit2 (new Infantry(Position(5, 2), 1));
    unique_ptr<Unite> unit3 (new Tank(Position(6, 1), 1));

    // Creation d'objets Joueur
    unique_ptr<Joueur> joueur1(new Joueur(0));
    unique_ptr<Joueur> joueur2(new Joueur(1));
    unique_ptr<Joueur> joueur3(new Joueur(2));
    unique_ptr<Joueur> joueur4(new Joueur(3));
    std::vector<Joueur*> listeJoueurs {joueur1.get(), joueur2.get(), joueur3.get(), joueur4.get()};

    // Creation d'objets Batiment
    unique_ptr<Batiment> batiment (new Usine(Position(2, 2), 0));
    unique_ptr<Batiment> batiment2 (new Usine(Position(17, 17), 1));
    unique_ptr<Batiment> batiment3 (new Usine(Position(0, 2), 0));
    unique_ptr<Batiment> batiment4 (new Usine(Position(19, 17), 1));
    unique_ptr<Batiment> batiment5 (new QG(Position(1, 1), 0));
    unique_ptr<Batiment> batiment6 (new QG(Position(18, 18), 1));
    unique_ptr<Batiment> batiment7 (new Usine(Position(0, 17), 3));
    unique_ptr<Batiment> batiment8 (new QG(Position(18, 1), 2));
    unique_ptr<Batiment> batiment9 (new QG(Position(1, 18), 3));    
    unique_ptr<Batiment> batiment10 (new Usine(Position(2, 17), 3));
    unique_ptr<Batiment> batiment11 (new Usine(Position(17, 2), 2));
    unique_ptr<Batiment> batiment12 (new Usine(Position(19, 2), 2));

    vector<Batiment*> batiments;
    batiments.push_back(batiment.get());
    batiments.push_back(batiment2.get());
    batiments.push_back(batiment3.get());
    batiments.push_back(batiment4.get());
    batiments.push_back(batiment5.get());
    batiments.push_back(batiment6.get());
    batiments.push_back(batiment7.get());
    batiments.push_back(batiment8.get());
    batiments.push_back(batiment9.get());
    batiments.push_back(batiment10.get());
    batiments.push_back(batiment11.get());
    batiments.push_back(batiment12.get());

    // Creation d'objets Flag
    unique_ptr<Flag> flag1 (new Flag(Position(1,1),0));
    unique_ptr<Flag> flag2 (new Flag(Position(18,18),1));
    std::vector<Flag*> flags {flag1.get(), flag2.get()};

    // création d'un objet TerrainTab
    unique_ptr<TerrainTab> terrainTab (new TerrainTab(map1()));
    
    // création d'un objet Terrain
    unique_ptr<Terrain> terrain(new Terrain(batiments, flags, *terrainTab));

    // Creation d'un objet Jeu
    unique_ptr<Jeu> jeu(new Jeu(terrain.get(), listeJoueurs)); 

    // Creation d'un objet Engine
    unique_ptr<Engine> engine(new Engine(jeu.get()));

    // Creation d'objets Tileset
    render::Tileset<Unite> uniteTileset("res/units.png");
    render::Tileset<Batiment> batimentTileset("res/batiments.png");
    render::Tileset<Flag> flagTileset("res/flags.png");
    render::Tileset<TerrainTile> terrainTileset("res/terrain.png");
    render::Tileset<MiscTile> miscTileset("res/misc.png"); 

    // creation d'un objet Layers
    unique_ptr<Layers> layers(new Layers(jeu.get(), engine.get(), &uniteTileset,  &batimentTileset, &flagTileset, &terrainTileset, &miscTileset));
    layers->setUniteSurface ();
    layers->setBatimentSurface ();
    layers->setFlagSurface ();
    layers->setTerrainSurface ();
    layers->setMiscSurface ();

    // Creation d'un thread dedie a l'affichage
    thread ng(runEngine, engine.get());
    cout<<"Initializing the engine..."<<endl;

    // Creation d'un thread dedie a l'affichage
    thread lyr(displayWindow, layers.get());
    cout<<"Initializing the graphics..."<<endl;
    cout<<"Hit Ctrl-C to close the game."<<endl;
    cout<<"Press Escape to end your turn."<<endl;
    std::cout<<"Player 1's turn :"<<std::endl;

    // Creation d'une unite Infantry
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"=> CreateUnitCommand(Position(4, 3), color))"<<endl;
    unique_ptr<CreateUnitCommand> cmd0(new CreateUnitCommand(Position(4, 3),0));
    engine->addCommand(cmd0.get());
    //engine->update();

    // Selection de unite Infantry
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"=> SelectUnitCommand(Position(4,3))"<<endl;
    unique_ptr<SelectUnitCommand> cmd1(new SelectUnitCommand(Position(4,3)));
    engine->addCommand(cmd1.get());
    //engine->update();

    // Deplacement de unite Infantry
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"=> MoveUnitCommande(Position(6,4))"<<endl;
    unique_ptr<MoveUnitCommand> cmd2(new MoveUnitCommand(Position(6,4)));
    engine->addCommand(cmd2.get());
    //engine->update();

    // Selection de unite Infantry
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"=> SelectUnitCommand(Position(5,2))"<<endl;
    unique_ptr<SelectUnitCommand> cmd3(new SelectUnitCommand(Position(5,2)));
    engine->addCommand(cmd3.get());
    //engine->update();

    // Attaque de l'unite HTank
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"la vie de l'unité du jouer 1 est:"<<unit->getvie()<<"."<<endl;
    cout<<"la puissance de l'unité du jouer 1 est:"<<unit->getpuissance()<<"."<<endl;
    cout<<"=> AttackUnitCommand(Position(5,1))"<<endl;
    unique_ptr<AttackUnitCommand> cmd4(new AttackUnitCommand(Position(5,1)));
    engine->addCommand(cmd4.get());
    //engine->update();

    cout<<"la nouvelle vie de l'unité du jouer 1 après être attacké pour la première fois est:"<<unit->getvie()<<"."<<endl;
    cout<<"la nouvelle puissance de l'unité du jouer 1 après être attacké pour la première fois est:"<<unit->getpuissance()<<"."<<endl;


    // TODO : Trouver un moyen de ne pas utiliser de unique_ptr a cause de deleteUnite()
    // Supression de l'unite Infantry
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"=> DeleteUnitCommand(Position(5,1))"<<endl;
    unit2.release();
    unique_ptr<DeleteUnitCommand> cmd5(new DeleteUnitCommand(Position(5,1)));
    engine->addCommand(cmd5.get());
    //engine->update(); 

    lyr.join();
    //jeu->fin = true;
    ng.join();
}*/

void AITest() {
    // Creation d'objets Joueur
    unique_ptr<Joueur> joueur1(new Joueur(0,false));
    unique_ptr<Joueur> joueur2(new Joueur(1,true));
    std::vector<Joueur*> listeJoueurs {joueur1.get(), joueur2.get()};

    // Creation d'objets Batiment
    unique_ptr<Batiment> batiment (new Usine(Position(2, 2), 0));
    unique_ptr<Batiment> batiment2 (new Usine(Position(17, 17), 1));
    unique_ptr<Batiment> batiment3 (new Usine(Position(0, 2), 0));
    unique_ptr<Batiment> batiment4 (new Usine(Position(19, 17), 1));
    unique_ptr<Batiment> batiment5 (new QG(Position(1, 1), 0));
    unique_ptr<Batiment> batiment6 (new QG(Position(18, 18), 1));

    vector<Batiment*> batiments;
    batiments.push_back(batiment.get());
    batiments.push_back(batiment2.get());
    batiments.push_back(batiment3.get());
    batiments.push_back(batiment4.get());
    batiments.push_back(batiment5.get());
    batiments.push_back(batiment6.get());

    // Creation d'objets Flag
    unique_ptr<Flag> flag1 (new Flag(Position(1,1),0));
    unique_ptr<Flag> flag2 (new Flag(Position(18,18),1));
    std::vector<Flag*> flags {flag1.get(), flag2.get()};

    // création d'un objet TerrainTab
    unique_ptr<TerrainTab> terrainTab (new TerrainTab(map1()));
    
    // création d'un objet Terrain
    unique_ptr<Terrain> terrain(new Terrain(batiments, flags, *terrainTab));

    // Creation d'un objet Jeu
    unique_ptr<Jeu> jeu(new Jeu(terrain.get(), listeJoueurs)); 

    // Creation d'un objet Engine
    unique_ptr<Engine> engine(new Engine(jeu.get()));

    // Creation d'objets Tileset
    render::Tileset<Unite> uniteTileset("res/units.png");
    render::Tileset<Batiment> batimentTileset("res/batiments.png");
    render::Tileset<Flag> flagTileset("res/flags.png");
    render::Tileset<TerrainTile> terrainTileset("res/terrain.png");
    render::Tileset<MiscTile> miscTileset("res/misc.png"); 

    // creation d'un objet Layers
    unique_ptr<Layers> layers(new Layers(jeu.get(), engine.get(), &uniteTileset,  &batimentTileset, &flagTileset, &terrainTileset, &miscTileset));
    layers->setUniteSurface ();
    layers->setBatimentSurface ();
    layers->setFlagSurface ();
    layers->setTerrainSurface ();
    layers->setMiscSurface ();

    // Creation d'un thread dedie a l'affichage
    thread ng(runEngine, engine.get());
    cout<<"Initializing the engine..."<<endl;

    // Creation d'un thread dedie a l'affichage
    thread lyr(displayWindow, layers.get());
    cout<<"Initializing the graphics..."<<endl;
    cout<<"Hit Ctrl-C to close the game."<<endl;
    cout<<"Press Escape to end your turn."<<endl;
    std::cout<<"Player 1's turn :"<<std::endl;

    lyr.join();
    ng.join();
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
	    //engineTest();
	    AITest();
        }
    }
    return 0;
}



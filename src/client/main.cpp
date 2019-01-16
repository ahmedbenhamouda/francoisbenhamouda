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
#include "client.h"

using namespace std;
using namespace state;
using namespace render;
using namespace client;

mutex m1;
bool record;

void displayWindow(Layers* layers, UI* ui, Jeu* jeu) {
	sf::RenderWindow window(sf::VideoMode(640,740), "Advance Wars");
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
					if (py<20) {
						layers->sendUnitCommand (Position(px,py));
					} else {
						layers->sendUICommand (px,py);
					}
					m1.unlock();
				}
				if(event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::Escape) {
					m1.lock();
					layers->sendTurnCommand();
					m1.unlock();
				}
			}
			if (jeu->simulation == -1) {
				window.clear();
				// update layers
				layers->setUniteSurface ();
				layers->setFlagSurface ();
				layers->setMiscSurface ();
				layers->displayLayers (&window);
				// update UI
				ui->setGeneralData();
				ui->setUnitData();
				ui->setBatimentData();
				ui->displayUI(&window);
				window.display();
			}
		}	
}


/*void runEngine(Engine* engine, Jeu* jeu) {
	//cout<<engine->commands.size()<<endl;
	while(1) {
		//if (engine->commands[0]) {
			m1.lock();
			engine->update();
			if (engine->jeu->simulation == -1) {
				engine->Clear();
			}
			m1.unlock();
		//}
	}
}*/

void runClient(Client* client, Jeu* jeu) {
	cout<<"Record : "<<record<<std::endl;
	if (record) {
		while(jeu->tour<8) {
			m1.lock();
			client->run();
			m1.unlock();
		}
		client->save();
	}
}


/*void AIPlay(AI* ai, Jeu* jeu) {
	this_thread::sleep_for(chrono::milliseconds(1000));
	while(1) {
		if (jeu->simulation == -1) {
			this_thread::sleep_for(chrono::milliseconds(100));
		} else {
			this_thread::sleep_for(chrono::milliseconds(50));
		}
		m1.lock();
		ai->run();
		m1.unlock();
	}
}*/


void clientTest() {
    // Creation d'objets Joueur
    unique_ptr<Joueur> joueur1(new Joueur(6,true));
    unique_ptr<Joueur> joueur2(new Joueur(7,true));
    std::vector<Joueur*> listeJoueurs {joueur1.get(), joueur2.get()};


    // Creation d'objets Batiment
    unique_ptr<Batiment> batiment1 (new Usine(Position(5, 4), 6));
    unique_ptr<Batiment> batiment2 (new QG(Position(5, 5), 6));

    unique_ptr<Batiment> batiment3 (new Usine(Position(14, 15), 7));
    unique_ptr<Batiment> batiment4 (new QG(Position(14, 14), 7));

    vector<Batiment*> batiments;
    batiments.push_back(batiment1.get());
    batiments.push_back(batiment2.get());
    batiments.push_back(batiment3.get());
    batiments.push_back(batiment4.get());



    // Creation d'objets Flag
    unique_ptr<Flag> flag1 (new Flag(Position(5,5),6));
    unique_ptr<Flag> flag2 (new Flag(Position(14,14),7));

    std::vector<Flag*> flags {flag1.get(), flag2.get()};

    // création d'un objet TerrainTab
    unique_ptr<TerrainTab> terrainTab (new TerrainTab(map1()));
    
    // création d'un objet Terrain
    unique_ptr<Terrain> terrain(new Terrain(batiments, flags, *terrainTab));

    // Creation d'un objet Jeu
    unique_ptr<Jeu> jeu(new Jeu(terrain.get(), listeJoueurs)); 

    // Creation d'un objet Client
    unique_ptr<Client> client(new Client(jeu.get()));

    /*// Creation d'une IA
    unique_ptr<DeepAI> crazyAI(new DeepAI(6,engine.get(),jeu.get()));
    unique_ptr<DeepAI> geniusAI(new DeepAI(7,engine.get(),jeu.get()));*/

    // Creation d'objets Tileset
    render::Tileset<Unite> uniteTileset("res/units.png");
    render::Tileset<Batiment> batimentTileset("res/batiments.png");
    render::Tileset<Flag> flagTileset("res/flags.png");
    render::Tileset<TerrainTile> terrainTileset("res/terrain.png");
    render::Tileset<MiscTile> miscTileset("res/misc.png");

    // creation d'un objet Layers
    unique_ptr<Layers> layers(new Layers(jeu.get(), client->engine, &uniteTileset,  &batimentTileset, &flagTileset, &terrainTileset, &miscTileset));

    layers->setBatimentSurface ();
    layers->setTerrainSurface ();

    // creation d'un objet UI
    unique_ptr<UI> ui(new UI(jeu.get()));
    
    // Creation d'un thread dedie au client
    thread cli(runClient, client.get(), jeu.get());
    cout<<"Initializing the client..."<<endl;
    
    // Creation d'un thread dedie a l'affichage
    thread lyr(displayWindow, layers.get(), ui.get(), jeu.get());
    cout<<"Initializing the graphics..."<<endl;
    
    /*// Creation d'un thread dedie au moteur
    thread ng(runEngine, engine.get(), jeu.get());
    cout<<"Initializing the engine..."<<endl;

    // Creation de deux threads dedies a l'IA
    thread ia_th1(AIPlay, crazyAI.get(), jeu.get());
    thread ia_th2(AIPlay, geniusAI.get(), jeu.get());
    cout<<"Initializing the AI..."<<endl;*/

    cout<<"Hit Ctrl-C to close the game."<<endl;
    cout<<"Press Escape to end your turn."<<endl;
    //std::cout<<"Player 1's turn :"<<std::endl;

    lyr.join();
    cli.join();
    //ng.join();
    //ia_th1.join();
    //ia_th2.join();
}


int main(int argc,char* argv[]) 
{
    //Exemple exemple;
    //exemple.setX(53);

    if (argc < 2) {
        cout << "Missing the \"record\" argument." << endl;
    } else if (argc > 2) {
        cout << "Too many arguments." << endl;
    } else {
        string myString(argv[1]);
        if (myString != "record") {
            cout << "Invalid argument." << endl;
        } else {
            record = true;
	    clientTest();
        }
    }
    return 0;
}



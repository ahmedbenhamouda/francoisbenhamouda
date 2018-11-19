#include "UI.h"
#include <string>
#include <sstream>
#include <exception>
#include <iostream>

namespace render {
	UI::UI() {		
    		uniteText = std::vector<sf::Text>();
    		batimentText = std::vector<sf::Text>();
	}
	UI::UI(state::Jeu* jeu) {
		if (!font.loadFromFile("res/arial.ttf")) {
			throw std::runtime_error("No such file");
		}
		this->jeu = jeu;
	}
	void UI::setGeneralData() {
		// init
		generalText = std::vector<sf::Text>();

		// Joueur
		int nb_joueurs = jeu->joueurs.size();
		std::stringstream joueur;
		joueur<<"Joueur "<<(jeu->tour%nb_joueurs)+1<<" :";
		sf::Text player(joueur.str(),font,16);
		generalText.push_back(player);

		// couleur
		int color = jeu->joueurs[jeu->tour%nb_joueurs]->color;
		std::string couleur;
		switch (color) {
			case 0 :
				couleur = "Rouge";
				break;
			case 1 :
				couleur = "Bleu";
				break;
			case 2 :
				couleur = "Vert";
				break;
			case 3 :
				couleur = "Jaune";
				break;
		}
		std::stringstream ss_color;
		ss_color<<"Couleur : "<<couleur<<".";
		sf::Text colorText(ss_color.str(),font,16);
		generalText.push_back(colorText);

		// argent
		int argent = jeu->joueurs[jeu->tour%nb_joueurs]->monnaie.getArgent();
		std::stringstream cash;
		cash<<"Argent : "<<argent<<" $.";
		sf::Text money(cash.str(),font,16);
		generalText.push_back(money);
	}
	void UI::displayUI (sf::RenderWindow* window) {
		for (size_t i=0; i<generalText.size(); i++) {
			generalText[i].setPosition(50.f,650.f+float(20*i));
			generalText[i].setColor(sf::Color::White);
			window->draw(generalText[i]);
		}
	}
	UI::~UI() {
	}
}

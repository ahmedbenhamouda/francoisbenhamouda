#include "UI.h"
#include <string>
#include <sstream>
#include <exception>
#include <iostream>

namespace render {
	UI::UI() {		
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
	void UI::setUnitData () {
		// init
		uniteText = std::vector<sf::Text>();

		// Check if player is selected
		if (jeu->selectedUnit) {
			std::string unit_type;
			switch(jeu->selectedUnit->getId()) {
				case 0:
					unit_type = "Infantry";
					break;
				case 1:
					unit_type = "Recon";
					break;
				case 2:
					unit_type = "Mech";
					break;
				case 3:
					unit_type = "Tank";
					break;
				case 4:
					unit_type = "HTank";
					break;
			}
			sf::Text colorText("Unite selectionnee : "+unit_type,font,16);
			uniteText.push_back(colorText);

			// Get unite life
			int vie = jeu->selectedUnit->getvie();
			std::stringstream life;
			life<<"Vie : "<<vie<<" PV.";
			sf::Text getLife(life.str(),font,16);
			uniteText.push_back(getLife);

			// Get unite power
			int puissance = jeu->selectedUnit->getpuissance();
			std::stringstream power;
			power<<"Puissance : "<<vie<<".";
			sf::Text getPower(power.str(),font,16);
			uniteText.push_back(getPower);
		} else {
			sf::Text colorText("Unite selectionnee : aucune",font,16);
			uniteText.push_back(colorText);
		}
	}
	void UI::displayUI (sf::RenderWindow* window) {
		// display general text
		for (size_t i=0; i<generalText.size(); i++) {
			generalText[i].setPosition(20.f,650.f+float(20*i));
			generalText[i].setColor(sf::Color::White);
			window->draw(generalText[i]);
		}
		// display unite text
		for (size_t i=0; i<uniteText.size(); i++) {
			uniteText[i].setPosition(200.f,650.f+float(20*i));
			uniteText[i].setColor(sf::Color::White);
			window->draw(uniteText[i]);
		}
	}
	UI::~UI() {
	}
}

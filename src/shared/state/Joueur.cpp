#include "Joueur.h"

namespace state {
	Joueur::Joueur() {
		monnaie = PorteMonnaie();
	}
	Joueur::Joueur(int color) {
		Joueur();
		this->color = color;
	}
	Joueur::~Joueur() {
	}
}

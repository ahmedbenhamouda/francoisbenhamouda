#include "Joueur.h"

namespace state {
	Joueur::Joueur() {
		monnaie = PorteMonnaie();
	}
	Joueur::Joueur(int color, bool is_AI) {
		Joueur();
		this->color = color;
		this->is_AI = is_AI;
	}
	Joueur::~Joueur() {
	}
}

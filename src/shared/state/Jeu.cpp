#include "Jeu.h"

namespace state {
	Jeu::Jeu(Terrain* etatInit, std::vector<Joueur*> joueurs) {
		etatJeu = etatInit;
		this->joueurs = joueurs;
	}
	Jeu::~Jeu() {
	}
}

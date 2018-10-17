#include "Jeu.h"

namespace state {
	Jeu::Jeu(Terrain* etatInit) {
		etatJeu = etatInit;
		tour = 0;
		fin = false;
	}
	Jeu::~Jeu() {
	}
}

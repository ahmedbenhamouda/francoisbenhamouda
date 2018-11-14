#include "AI.h"

namespace ai {
	void AI::fillStateLists(){
		for (state::Unite* unit:jeu->etatJeu->getUniteList()){
			if (color == unit->getColor()){
				liste_unites.push_back(unit);		
			}
		}
		for (state::Batiment* bat:jeu->etatJeu->getBatimentList()){
			if (color == bat->getColor()){
				liste_batiments.push_back(bat);							
			}
		}
	}
	void AI::fillCommandList(){
	}
	void run(){
	}
}

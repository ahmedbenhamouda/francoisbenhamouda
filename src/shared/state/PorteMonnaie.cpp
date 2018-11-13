#include "PorteMonnaie.h"

namespace state {
	PorteMonnaie::PorteMonnaie() {
	}
	int PorteMonnaie::getArgent () {
		return argent;
	}
	void PorteMonnaie::achat (int argent) {
		this->argent -= argent;
	}
	void PorteMonnaie::gainTour (int argent) {
		this->argent += argent;
	}
	PorteMonnaie::~PorteMonnaie() {
	}
}

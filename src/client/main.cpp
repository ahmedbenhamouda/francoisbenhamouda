#include <iostream>
#include <string>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{
   

    if (argc < 2) {
        cout << "Missing the \"hello\" argument." << endl;
    } else if (argc > 2) {
        cout << "Too many arguments." << endl;
    } else {
        string myString(argv[1]);
        if (myString != "hello") {
            cout << "Invalid argument." << endl;
        } else {
            cout << "- Hello there !\n- General Kenobi !" << endl;
        }
    }
    return 0;
}

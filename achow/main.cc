
#include <iostream>
#include <fsteram>
#include <string>
#include <istream>
#include "gameobject.h"
#include "item.h"
#include "game.h"

using namespace std;

int main (argc, char **argv) {
	ifstream file; 
	file.open("defaultmap.txt")
	Game *game = new Game (file);

	game.display();
	
	delete game;
	file.close();
}
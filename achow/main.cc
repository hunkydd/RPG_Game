
#include <iostream>
#include <fsteram>
#include <string>
#include <istream>
#include <cstdlib>
#include <ctype.h>
#include "gameobject.h"
#include "item.h"
#include "game.h"
#include "unoccupied.h"
#include "cell.h"

using namespace std;

int main (int argc, char *argv[]) {
	bool d = true;
	char c;
	ifstream file; 


	for (int i = 1; i < argc; i++) {
		if (isdigit(argv[i])) {
			setSeed(atoi(argv[i])
		} else {
			file.open(argv[i]);
			d = false;
		}
	}

	if (d) file.open("defaultmap.txt");

	cin >> c;
	Game *game = new Game (file, d, c);

	game.display();
	


	/*
	while true {
		game.action(cin);
	}
	
	*/

	delete game;
	file.close();
}
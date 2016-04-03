
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
#include "character.h"
#include "player.h"
#include "enemy.h"

using namespace std;

int main (int argc, char *argv[]) {
	bool d = true;
	char c;
	string s;
	ifstream file; 


	for (int i = 1; i < argc; i++) {
		if (isdigit(argv[i])) {
			setSeed(atoi(argv[i])
		} else {
			file.open(argv[i]);
			if(file.file()) {
				cout << "Problem loading board from the map file '" << argv[i] << "'." << endl;
			} else {
				d = false;
			}

		}
	}

	if (d) file.open("defaultmap.txt");

	for(;;) {
		cout << "Welcome to Chamber Crawler 3000" << endl;
		cout << "What would you like to play as today?" << endl;
		cout << "w) Wizard" << endl;
		cout << "k) Knight" << endl;
		cout << "s) Samurai" << endl;
		while(cin >> c) {
			if (c == 's' || c == 'w' || c == 'k') break;
			cout << "Did not recognize input." <<endl;
		}
		Game *game = new Game (file, d, c);

		cout << "You have chose to play as a " << game->type() <<". Good luck." endl;
				
		while (!game.win()) {
			game.display();
			cout << "What will you do?" << endl;
			game.action(cin);

		}
		if (game->play()) {
			cout << "Play Again? (y/n)" <<endl;
			for (;;) {
				cin >> s;
		 		if (s != 'y' || s != 'n') {
		 			cout << "Did not recognize input." <<endl;
		 		} else {
			 		if (s == "n") {
			 			goto L;
			 		}
		 		}
			}			
		} else {
			break;
		}


		delete game;

	}
	L1;
	delete game;
	file.close();
}
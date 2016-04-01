#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <iomanip>
#include "game.h"
#include "PRNG.h"

PRNG prng( getpid() );

using std::cout;
using std::endl;

//Sets seed of prng
void setSeed( uint32_t seed ) {
  prng.seed( seed );
}

Game::Game (fstream &file) {
	floor = 0;
	char c;

	Cell ***grid2 = new Cell **[MAX_FLOORS];
	for (int i = 0; i < MAX_FLOORS; i++) {
		*grid[i]= new Cell *[MAX_ROWS];
		for (int s = 0; s < MAX_ROWS; s++) {
			grid[i][s] = new Cell[MAX_COLS];
		}
	}

	grid = grid2;

	for (int i = 0; i < MAX_FLOORS; i++) {
		for (int y = 0; y < MAX_ROWS; y++) {
			for (int x = 0; x < MAX_COLS; x++) {
				file.get(c);
				grid[i][y][x] = new Cell (x, y, c);
				if (c == '-' || c == '|' || c == ' ') {
					Unoccupied *tile = new Unoccupied(x,y,true);
					grid[i][y][x].changeContents(tile);
				} else if (c == '.' || c == '+' || c == '#') {
					Unoccupied *tile = new Unoccupied(x,y,false);
					grid[i][y][x].changeContents(tile);
				}
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		generatePotion();
	}
	for (int i = 0; i < 10; i++) {
		generateGold();
	}

}

Game::~Game() {
	for (int i = 0; i < MAX_FLOORS; i++) {
		for (int y = 0; y < MAX_ROWS; y++) {
			delete [] grid[i][y];
		}
		delete [] grid [i];
	}
	delete [] grid;
}

int Game::getfloor() { return floor; }


void Game::generatePotion() {
	int room;
	int x, y;

	while true {
		room = prng(4);
		if (room == 0) {
			y = prng(3) + 3;
			x = prng(25) + 3;
			if (!checkOcc(x,y)) {
				grid[floor][y][x].changeContents(typePot(x,y));
				break;
			}
		} else if (room == 1) {
			section = prng(3);
			if (section == 0) {
				y = prng(3) + 3;
				x = prng(29) + 39;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typePot(x,y));
					break;
				}
			} else if (section == 1) {
				y = prng(1) + 5;
				x = prng(7) + 62;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typePot(x,y));
					break;
				}
			} else if (section == 2) {
				y = 6
				x = prng(1) + 71;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typePot(x,y));
					break;
				}
			} else {
				y = prng(4) + 8;
				x = prng(14) + 61;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typePot(x,y));
					break;
				}
			}
		} else if (room == 2) {
			y = prng(2) + 10;
			x = prng(9) + 38;
			if (!checkOcc(x,y)) {
				grid[floor][y][x].changeContents(typePot(x,y));
				break;
			}
		} else if (room == 3) {
			y = prng(6) + 15;
			x = prng(20) + 4;
			if (!checkOcc(x,y)) {
				grid[floor][y][x].changeContents(typePot(x,y));
				break;
			}
		} else {
			section = prng(1);
			if (section == 0) {
				y = prng(2) + 16;
				x = prng(10) + 65;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typePot(x,y));
					break;
				}
			} else {
				y = prng(2) + 19;
				x = prng(38) + 37;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typeGold(x,y));
					break;
				}
			}
		}
	}
}

*Item Game::typeGold(int x, int y) {
	int rn = prng(7);
	if (rn > 0) {
		Item *gold = new Item(x,y,6);
	} else {
		Item *gold = new Item(x,y,7);
	}
	return gold;
}

*Item Game::typePot(int x, int y) {
	int rn = prng(6);
	Item *pot = new Item(x,y,6);
	return pot;
}

void Game::generateGold() {
	int room;
	int x, y;
	int section;

	while true {
		room = prng(4);
		if (room == 0) {
			y = prng(3) + 3;
			x = prng(25) + 3;
			if (!checkOcc(x,y)) {
				grid[floor][y][x].changeContents(typeGold(x,y));
				break;
			}
		} else if (room == 1) {
			section = prng(3);
			if (section == 0) {
				y = prng(3) + 3;
				x = prng(29) + 39;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typeGold(x,y));
					break;
				}
			} else if (section == 1) {
				y = prng(1) + 5;
				x = prng(7) + 62;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typeGold(x,y));
					break;
				}
			} else if (section == 2) {
				y = 6
				x = prng(1) + 71;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typeGold(x,y));
					break;
				}
			} else {
				y = prng(4) + 8;
				x = prng(14) + 61;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typeGold(x,y));
					break;
				}
			}
		} else if (room == 2) {
			y = prng(2) + 10;
			x = prng(9) + 38;
			if (!checkOcc(x,y)) {
				grid[floor][y][x].changeContents(typeGold(x,y));
				break;
			}
		} else if (room == 3) {
			y = prng(6) + 15;
			x = prng(20) + 4;
			if (!checkOcc(x,y)) {
				grid[floor][y][x].changeContents(typeGold(x,y));
				break;
			}
		} else {
			section = prng(1);
			if (section == 0) {
				y = prng(2) + 16;
				x = prng(10) + 65;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typeGold(x,y));
					break;
				}
			} else {
				y = prng(2) + 19;
				x = prng(38) + 37;
				if (!checkOcc(x,y)) {
					grid[floor][y][x].changeContents(typeGold(x,y));
					break;
				}
			}
		}
	}
}

//Checks if tile is occupied
bool Game::checkOcc (int x, int y) {
	return grid[floor][y][x].getContents()->occupied();
}


void display() {
	for (int y = 0; y < MAX_ROWS; y++) {
		for (int x = 0; x < MAX_COLS; x++) {
				cout<<grid[i][y][x].display();
		}
	}
	cout<<endl;
	cout<<"           Class: " << setw(15) << "Knight" << "GP: " << setw(15) <<"0"<< "Floor" << getfloor() << endl;
	cout<<"           HP: " << setw(3) << "/100            Atk:" << setw(15) <<"50" <<"          Def:" << setw(15) << "50" << "\%" << "          Turn: " << "1" << endl;

	
}
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <iomanip>
#include "game.h"
#include "PRNG.h"

PRNG prng( getpid() );

using std::cout;
using std::endl;
using std::string;

//Sets seed of prng
void setSeed( uint32_t seed ) {
        prng.seed( seed );
}

Game::Game (fstream &file, bool d) : floor(0){
	char c;

	Cell ***grid2 = new Cell **[MAX_FLOORS];
	for (int i = 0; i < MAX_FLOORS; i++) {
		*grid[i]= new Cell *[MAX_ROWS];
		for (int s = 0; s < MAX_ROWS; s++) {
			grid[i][s] = new Cell[MAX_COLS];
		}
	}

	grid = grid2;

	if (!d) {
		for (int i = 0; i < MAX_FLOORS; i++) {
			for (int y = 0; y < MAX_ROWS; y++) {
				for (int x = 0; x < MAX_COLS; x++) {
					file.get(c);
					grid [i][y][x] = new Cell (x, y, c);
					if (c == '-' || c == '|' || c == ' ') { //unwalkable
						Unoccupied *tile = new Unoccupied(x,y,false,false);
						grid[i][y][x].changeContents(tile, c);
					} else if (c == '.' || c == '+' || c == '#' || c == '>') { //walkable
						Unoccupied *tile = new Unoccupied(x,y,true,true); //not spawning so don't have to check if gameobjects can spawn
						if (c == '>') tile->stair();
						grid[i][y][x].changeContents(tile, c);
					} else if (c == '@') { //player
						//init player
					} else if (c == 'X' || c == 'g' || c == 'M' || c == 'O' || c == 'D') { //enemy 
						//init enemy
					} else if (c == '6' || c == '7') { //gold
						Item *item = new Item(x,y, c - '0');
						grid[i][y][x].changeContents(item, '$');
					} else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5') { //potion
						Item *item = new Item(x,y, c - '0');
						grid[i][y][x].changeContents(item, '!');
					}
				}
			}
		}
	} else {
		for (int i = 0; i < MAX_FLOORS; i++) {
			for (int y = 0; y < MAX_ROWS; y++) {
				for (int x = 0; x < MAX_COLS; x++) {
					file.get(c);
					grid [i][y][x] = new Cell (x, y, c);
					if (c == '-' || c == '|' || c == ' ') {
						Unoccupied *tile = new Unoccupied(x,y,false,false);
						grid[i][y][x].changeContents(tile, c);
					} else if (c == '.' || c == '+' || c == '#') {
						Unoccupied *tile = new Unoccupied(x,y,true,true); //+ and # are not in the bounds of the genLocation so dont need to check if gameobjects can spawn
						grid[i][y][x].changeContents(tile, c);
					} 
				}
			}
			spawnPlayer(i);
			spawnStairs(i);
			for (int z = 0; z < 10; z++) {
				spawnPotion(int i);
			}
			for (int z = 0; z < 10; z++) {
				spawnGold(int i);
			}
			for (int z = 0; z < 20; z++) {
				spawnEnemy(int i);
			}
		}		
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
	//delete player maybe
}

int Game::getfloor() { return floor; }

void Game::genLocation(int f, bool stairs) {
	int room;
	int x, y, section;
	while true {
		if (stairs) {
			room = prng(3);
			if (room >= player.getRoom() /*temp*/) { room += 1; }
		} else {
			room = prng(4);
		}

		if (room == 0) {
			y = prng(3) + 3;
			x = prng(25) + 3;
			if (canSpawn(x,y,f)) {
				break;
			}
		} else if (room == 1) {
			section = prng(3);
			if (section == 0) {
				y = prng(3) + 3;
				x = prng(29) + 39;
				if (canSpawn(x,y,f)) {
					break;
				}
			} else if (section == 1) {
				y = prng(1) + 5;
				x = prng(7) + 62;
				if (canSpawn(x,y,f)) {
					break;
				}
			} else if (section == 2) {
				y = 6;
				x = prng(1) + 71;
				if (canSpawn(x,y,f)) {
					break;
				}
			} else {
				y = prng(4) + 8;
				x = prng(14) + 61;
				if (canSpawn(x,y,f)) {
					break;
				}
			}
		} else if (room == 2) {
			y = prng(2) + 10;
			x = prng(9) + 38;
			if (canSpawn(x,y,f)) {
				break;
			}
		} else if (room == 3) {
			y = prng(6) + 15;
			x = prng(20) + 4;
			if (canSpawn(x,y,f)) {
				break;
			}
		} else {
			section = prng(1);
			if (section == 0) {
				y = prng(2) + 16;
				loc.x = prng(10) + 65;
				if (canSpawn(x,y)) {
					break;
				}
			} else {
				y = prng(2) + 19;
				x = prng(38) + 37;
				if (canSpawn(x,y,f)) {
					break;
				}
			}
		}
	}
	loc.x = x;
	loc.y = y;
}

void Game::spawnStairs(int f) {
	genLocation(f, true);
	Unoccupied *stairs = new Unoccupied(loc.x, loc.y, false, true);
	stairs->stair();
	grid[f][loc.y][loc.x].changeContents(stairs,'>');

}

//TO BE DONE LATER
void Game::spanwPlayer(int f) {

}

void Game::spawnPotion(int f) {
	int rn = prng(6);
	Item *pot = new Item(6);

	genLocation(f, false);

	pot.x(loc.x);
	pot.y(loc.y);
	grid[f][loc.y][loc.x].changeContents(pot, '!');
	pot.location(grid[f][loc.y][loc.x]);
}


void Game::spawnGold(int f) {
	int room;
	int x, y, section;

	int rn = prng(7);
	if (rn > 0) {
		Item *gold = new Item(6);
		genLocation(f, false);
		
	} else {
		Item *gold = new Item(7);
		//while true {
			genLocation(f, false);
		//} //for spawning dragon
	}

	gold.x(loc.x);
	gold.y(loc.y);
	grid[f][loc.y][loc.x].changeContents(gold,'$');
	gold.location(grid[f][loc.y][loc.x]);
}

//TO BE DONE LATER
void spawnEnemy(int f) {

}


//Checks to see if you can spawn on tile
bool Game::canSpawn (int x, int y, int f) {
	return grid[f][y][x].getContents()->canSpawn();
}

//Checks to see if you can walk on tile
bool Game::canWalk (int x, int y) {
	return grid[f][y][x].getContents()->canWalk();
}

void action (istream &cmd) {
	cmd >> s;
	if (s == "no") {

	} else if (s == "so") {

	} else if (s == "ea") {

	} else if (s == "we") {

	} else if (s == "ne") {

	} else if (s == "nw") {

	} else if (s == "se") {

	} else if (s == "sw") {

	} else if (s == "se") {

	} else if (s == "a") {

	} else if (s == "u") {

	} else if (s == "q") {

    } else if (s == "stopwander") {

	} else if (s == "stopdeath") {

	}

}

void display() {
	for (int y = 0; y < MAX_ROWS; y++) {
		for (int x = 0; x < MAX_COLS; x++) {
				cout<<grid[i][y][x].display();
		}
	}
	cout<<endl;
	cout<<"           Class: " << setw(15) << "Knight" << "GP: " << setw(15) <<"0"<< "Floor" << getfloor() << endl;
	cout<<"           HP: " << setw(3) << "/100            Atk:" << setw(15) <<"50" <<"          Def:" << setw(15) <<"50"<<"\%" << "          Turn: " << "1" << endl;

	
}
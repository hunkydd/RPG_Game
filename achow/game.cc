#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <iomanip>
#include "game.h"
#include "PRNG.h"

PRNG prng( getpid() );

using std::cout;
using std::endl;
using std::list;
using std::string;

//Sets seed of prng
void setSeed( uint32_t seed ) {
        prng.seed( seed );
}

Game::Game (fstream &file, bool d, char c) : floor(0){
	char c;

	Cell ***grid2 = new Cell **[MAX_FLOORS];
	for (int i = 0; i < MAX_FLOORS; i++) {
		*grid[i]= new Cell *[MAX_ROWS];
		for (int s = 0; s < MAX_ROWS; s++) {
			grid[i][s] = new Cell[MAX_COLS];
		}
	}

	grid = grid2;

	Player *player = new Player(c);
	_player=player;

	list<Enemy *> *en = new list<Enemy *>[MAX_FLOORS];
	enemies = en;
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
						grid[i][y][x].changeContents(player, c);
					} else if (c == 'X' || c == 'g' || c == 'M' || c == 'O' || c == 'D') { //enemy 
						Enemy *e = new Enemy(c);
						e->x(loc.x);
						e->y(loc.y);
						grid[f][loc.y][loc.x].changeContents(gold,c);
						e->location(grid[f][loc.y][loc.x]);
						enemies[f]->push_back(e);
					} else if (c == '6') {
						Item *item = new Item(x,y, c - '0');
						item->x(loc.x);
						item->y(loc.y);
						grid[i][y][x].changeContents(item, '$');
						item->location(grid[f][loc.y][loc.x]);
					} else if (c == '7') { //gold
						DragonGold *item = new DragonGold(x,y, c - '0');
						item->x(loc.x);
						item->y(loc.y);
						grid[i][y][x].changeContents(item, '$');
						item->location(grid[f][loc.y][loc.x]);
					} else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5') { //potion
						Item *item = new Item(x,y, c - '0');
						item->x(loc.x);
						item->y(loc.y);
						grid[i][y][x].changeContents(item, '!');
						item->location(grid[f][loc.y][loc.x]);
					}
				}
			}
			for (int l=0; l < 7; l++) {
				adjacent()
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
			if (room >= playerRoom) { room += 1; }
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
	playerRoom = room; //Changes everytime a player is placed in floor
	loc.x = x;
	loc.y = y;
}

void Game::spawnStairs(int f) {
	genLocation(f, true);
	Unoccupied *stairs = new Unoccupied(loc.x, loc.y, false, true);
	stairs->stair();
	grid[f][loc.y][loc.x].changeContents(stairs,'>');

}

void Game::spanwPlayer(int f) {
	genLocation(f, false);
	//player.x(loc.x);
	//player.y(loc.y);
	grid[f][loc.y][loc.x].changeContents(player,'@');
	//player.location(grid[f][loc.y][loc.x]);
}

void Game::spawnPotion(int f) {
	int rn = prng(6);
	Item *pot = new Item(6);

	genLocation(f, false);

	pot->x(loc.x);
	pot->y(loc.y);
	grid[f][loc.y][loc.x].changeContents(pot, '!');
	pot->location(grid[f][loc.y][loc.x]);
}


void Game::spawnGold(int f) {
	int x, y;

	int rn = prng(7);
	if (rn < 7) {
		Item *gold = new Item(6);
		genLocation(f, false);
		x=loc.x;
		y=loc.y;
	} else {
		DragonGold *gold = new DragonGold(7);
		for(;;) {
			genLocation(f, false);
			x=loc.x;
			y=loc.y;
			int rn = prng(8);
			adjacent(x,y,f,rn);
			if(canSpawn(loc.x,loc.y)) {
				Enemy *drag = new Enemy('D');
				drag->x(loc.x);
				drag->y(loc.y);
				grid[f][loc.y][loc.x].changeContents(drag,'D');
				enemies[f]->push_back(drag);
				gold->addDragon(drag);
			}
		} //for spawning dragon
	}

	gold->x(x);
	gold->y(y);
	grid[f][loc.y][loc.x].changeContents(gold,'$');
	gold->location(grid[f][loc.y][loc.x]);
}


void spawnEnemy(int f) {
	int rn = prng (5);
	char c;
	if ( rn == 0 || rn == 1 ) {
		c = 'X';
	} else if ( rn == 2 || rn == 3 )  {
		c ='g';
	} else if ( rn == 4) {
		c = 'O';
	} else {
		c = 'M';
	}
	Enemy *e = new Enemy(c);

	genLocation(f, false);

	e->x(loc.x);
	e->y(loc.y);
	grid[f][loc.y][loc.x].changeContents(gold,c);
	e->location(grid[f][loc.y][loc.x]);
	enemies[f]->push_back(e);

}

void adjacent(int x, int y, int f, int centre) {
	
	int row=y 
	int col=x;
	switch (centre) {
		case 0:
			row--;
			col--;
			break;
		case 1:
			row--;
			break;
		case 2:
			row--;
			col++;
			break;
		case 3:
			col--;
			break;
		case 4:
			col++;
			break;
		case 5:
			row++;
			col--;
			break;
		case 6:
			row++
			break;
		case 7:
			row++;
			col++;
			break;
	}
	loc.x=col;
	loc.y=row;
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
	for_each(enemies[floor].begin(), enemies[floor].end(),/*do stuff*/);

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
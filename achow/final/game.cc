#include <iostream>
#include <fstream>
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
using std::for_each;
using std::setw;

//Sets seed of prng
void setSeed( uint32_t seed ) {
        prng.seed( seed );
}

Game::Game (std::ifstream &file, bool d, char p) : floor(0){
	char c;

	grid = new Cell **[MAX_FLOORS];
	for (int i = 0; i < MAX_FLOORS; i++) {
		grid[i]= new Cell *[MAX_ROWS];
		for (int s = 0; s < MAX_ROWS; s++) {
			grid[i][s] = new Cell[MAX_COLS];
		}
	}
	/*
	for (int i = 0; i < MAX_FLOORS; i++) {
		for (int y = 0; y < MAX_ROWS; y++) {
			for (int x = 0; x < MAX_COLS; x++) {
				grid[i][y][x]=new Cell();
			} 
		}
	}
	*/
	player = new Player(-1,-1,p);
	
	playerLoc = new Unoccupied[MAX_FLOORS];

	list<Enemy *> *en = new list<Enemy *>[MAX_FLOORS];
	enemies = en;
	if (!d) {
		for (int i = 0; i < MAX_FLOORS; i++) {
			//cout<<i<<endl;
			for (int y = 0; y < MAX_ROWS; y++) {
				for (int x = 0; x < MAX_COLS-1; x++) {
					file.get(c);
					Cell *cell = new Cell (x,y,c);
					grid [i][y][x] = *cell;
					if (c == '-' || c == '|' || c == ' ' || c == '\n') { //unwalkable
						Unoccupied *tile = new Unoccupied(x,y,false,false);
						grid[i][y][x].changeContents(tile, c);
					} else if (c == '.' || c == '+' || c == '#' || c == '>') { //walkable
						Unoccupied *tile = new Unoccupied(x,y,true,true); //not spawning so don't have to check if gameobjects can spawn
						if (c == '>') tile->stair();
						grid[i][y][x].changeContents(tile, c);
					} else if (c == '@') { //player
						Unoccupied *tile = new Unoccupied(x,y,true,true);
						grid[i][y][x].changeContents(tile, c);
						tile->location(&grid[i][y][x]);
						playerLoc[i] = *tile;
					} else if (c == 'X' || c == 'g' || c == 'M' || c == 'O' || c == 'D') { //enemy 
						Enemy *e = new Enemy(x,y,c);
						e->x(x);
						e->y(y);
						grid[i][y][x].changeContents(e,c);
						e->location(&grid[i][y][x]);
						enemies[i].push_back(e);
					} else if (c == '6') {
						Item *item = new Item(x,y, c - '0');
						item->x(x);
						item->y(y);
						grid[i][y][x].changeContents(item, '$');
						item->location(&grid[i][y][x]);
					} else if (c == '7') { //gold
						DragonGold *item = new DragonGold(x,y, c - '0');
						item->x(x);
						item->y(y);
						grid[i][y][x].changeContents(item, '$');
						item->location(&grid[i][y][x]);
					} else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5') { //potion
						Item *item = new Item(x,y, c - '0');
						item->x(x);
						item->y(y);
						grid[i][y][x].changeContents(item, '!');
						item->location(&grid[i][y][x]);
					}
				}
			}
			list<Enemy *>::iterator x;
			for( x = enemies[i].begin(); x != enemies[i].end(); x++) {
				findHoard(i,*x);
			}
		}
	} else {
		for (int i = 0; i < MAX_FLOORS; i++) {
			//cout<<i<<endl;
			for (int y = 0; y < MAX_ROWS; y++) {
				for (int x = 0; x < MAX_COLS; x++) {
					file.get(c);
					Cell *cell = new Cell(x,y,c);
					grid [i][y][x] = *cell;
					if (c == '-' || c == '|' || c == ' ' || c == '\n') {
						Unoccupied *tile = new Unoccupied(x,y,false,false);
						grid[i][y][x].changeContents(tile, c);
					} else if (c == '.' || c == '+' || c == '#') {
						Unoccupied *tile = new Unoccupied(x,y,true,true); //+ and # are not in the bounds of the genLocation so dont need to check if gameobjects can spawn
						grid[i][y][x].changeContents(tile, c);
					} 
				}
			}
		}
		for (int i = 0; i < MAX_FLOORS; i++) {
			//display();
			//cout<<i<<endl;
			spawnPlayer(i);
			spawnStairs(i);
			for (int z = 0; z < 10; z++) {
				spawnPotion(i);
			}
			
			for (int z = 0; z < 10; z++) {
				spawnGold(i);
			}
			
			for (int z = 0; z < 20; z++) {
				spawnEnemy(i);
			}
			//cout<<i<<endl;
		}
	}
	setPlayer(floor);

}

void Game::setPlayer(int f) {
	player->x(playerLoc[f].x());
	player->y(playerLoc[f].y());
	grid[f][player->y()][player->x()].changeContents(player,'@');
	player->location(&grid[f][player->y()][player->x()]);
}

void Game::findHoard(int f, Enemy *en) {
	if (en->getType() == 4) {
		for (int i=0; i < 7; i++) {
			adjacent(en->x(), en->y(), f, i);
			if(grid[f][loc.y][loc.x].display() == '$') {
				if(grid[f][loc.y][loc.x].getContents()->item() == 7) {
					grid[f][loc.y][loc.x].changeContents(en,'$');
					break;
				}
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
	//delete [] playerLoc;
	//delete player maybe
}

//int Game::floor() { return floor; }

void Game::genLocation(int f, bool stairs) {
	int room;
	int x, y, section;
	for (;;) {
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
				if (canSpawn(x,y,f)) {
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
	//cout<<y<<" "<<x<<endl;
}

void Game::spawnStairs(int f) {
	genLocation(f, true);
	Unoccupied *stairs = new Unoccupied(loc.x, loc.y, false, true);
	stairs->isStair();
	grid[f][loc.y][loc.x].changeContents(stairs,'>');
	stairs->location(&grid[f][loc.y][loc.x]);
}

void Game::spawnPlayer(int f) {
	genLocation(f, false);
	Unoccupied *tile = new Unoccupied(loc.x,loc.y,true,true);
	grid[f][loc.y][loc.x].changeContents(tile, ' ');
	tile->location(&grid[f][loc.y][loc.x]);
	playerLoc[f] = *tile;
}

void Game::spawnPotion(int f) {
	int rn = prng(6);
	Item *pot = new Item(rn);

	genLocation(f, false);

	pot->x(loc.x);
	pot->y(loc.y);
	grid[f][loc.y][loc.x].changeContents(pot, '!');
	pot->location(&grid[f][loc.y][loc.x]);
}


void Game::spawnGold(int f) {
	int x, y;
	Item *gold;
	int rn = prng(7);
	if (rn < 7) {
		gold = new Item(6);
		genLocation(f, false);
		x=loc.x;
		y=loc.y;
	} else {
		DragonGold *gold2 = new DragonGold(7);
		for(;;) {
			genLocation(f, false);
			x=loc.x;
			y=loc.y;
			int rn = prng(8);
			adjacent(x,y,f,rn);
			//cout<<loc.x<<" "<<loc.y<<endl;
			if(canSpawn(loc.x,loc.y, f)) {
				Enemy *drag = new Enemy(loc.x,loc.y,'D');
				drag->x(loc.x);
				drag->y(loc.y);
				grid[f][loc.y][loc.x].changeContents(drag,'D');
				enemies[f].push_back(drag);
				gold2->addDragon(drag);
				gold = gold2;
				break;
			}
		} //for spawning dragon
	}

	gold->x(x);
	gold->y(y);
	grid[f][loc.y][loc.x].changeContents(gold,'$');
	gold->location(&grid[f][loc.y][loc.x]);
}


void Game::spawnEnemy(int f) {
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
	Enemy *e = new Enemy(loc.x,loc.y,c);

	genLocation(f, false);

	e->x(loc.x);
	e->y(loc.y);
	grid[f][loc.y][loc.x].changeContents(e,c);
	e->location(&grid[f][loc.y][loc.x]);
	enemies[f].push_back(e);

}

void Game::adjacent(int x, int y, int f, int centre) {
	int row=y; 
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
			row++;
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
	//cout<<y<<" "<<x<<endl;
	//cout<<grid[f][y][x]->display()<<endl;
	return grid[f][y][x].getContents()->canSpawn();
}

//Checks to see if you can walk on tile
bool Game::canWalk (int x, int y) {
	return grid[floor][y][x].getContents()->canWalk();
}

void Game::action (std::istream &cmd) {
	string s;
	cmd >> s;
	try {
		if (s == "no") {
			player->move(s, &grid[floor]);
		} else if (s == "so") {
			player->move(s, &grid[floor]);
		} else if (s == "ea") {
			player->move(s, &grid[floor]);
		} else if (s == "we") {
			player->move(s, &grid[floor]);
		} else if (s == "ne") {
			player->move(s, &grid[floor]);
		} else if (s == "nw") {
			player->move(s, &grid[floor]);
		} else if (s == "se") {
			player->move(s, &grid[floor]);
		} else if (s == "sw") {
			player->move(s, &grid[floor]);
		} else if (s == "a") {
			cmd >> s;
			player->attack(s, &grid[floor]);
		} else if (s == "u") {
			cmd >> s;
			player->use(s, &grid[floor]);
		} else if (s == "q") {
	 		cout << "Are you sure you want to quit? (y/n)" <<endl;
	 		cmd >> s;
	 		if (s != "y" && s != "n") {
	 			cout << "Did not recognize input." <<endl;
	 		} else {
		 		if (s == "y") {
		 			cout << "You have chosen to exit. At least you tried." <<endl;
		 			done = true;
					goto L;
		 		} else {
		 			goto L;
		 		}	 			
	 		}
	    	} else if (s == "stopwander") {
	    		stopWander = true;
		} else if (s == "stopdeath") {
			stopDeath = true;
		} else {
			cout << "Did not recognize input." <<endl;
			action(cmd);
		}
	} catch ( const string &ex) {
		cout << ex << endl;
		action(cmd);
	}
	if (!stopWander) {
		list<Enemy *>::iterator x;
		for( x = enemies[floor].begin(); x != enemies[floor].end(); x++) {
			int eMove=(*x)->detect(&grid[floor]);
			if(eMove == 2) {
				(*x)->attack(player);
			} else if (eMove == 1) {
				(*x)->use(&grid[floor]);
			} else {
				(*x)->move(&grid[floor]);
			}
		}
	}
	if (!stopDeath && player->health() == 0) gameOver();
	if (player->advance()) { // temp
		nextFloor(); //advance
	} else {
		turn++;
	}
	L: ;
}
/*
void Game::findPlayer(int f, Enemy *en) {
	for (int i=0; i < 7; i++) {
		adjacent(en->x(), en->y(), f, i);
		if(grid[f]][loc.y][loc.x].display() == '@') {
			return true;
		}
	}
	return false;

}
*/
bool Game::win() { return done; }
bool Game::play() {return playAgain; }
void Game::nextFloor() {
	player->advance(false);
	if (floor  == 6) {
		cout << "At long last, you have outmatched the Great Cavernous Chambers. Great things await you."<< endl;
    	cout << "You achieved a score of"<<0<<"."<<endl;
    	done = true;
    	playAgain = true;
	} else {
		floor++;
		setPlayer(floor);
		cout << "You decended down to floor " << floor <<"." << endl;
	}
}



void Game::gameOver() {
	done = true;
	playAgain = true;
	cout << "You have been bested by the Great Cavernous Chambers. Good luck next time!"<< endl;
    	cout << "You achieved a score of"<<0<<"."<<endl;

}
string Game::type() {
	return player->getType();
}
void Game::display() {
	for (int y = 0; y < MAX_ROWS; y++) {
		for (int x = 0; x < MAX_COLS; x++) {
				cout<<grid[floor][y][x].display();
		}
		//cout<<endl;
	}
	cout<<endl;
	cout<<"           Class: " << setw(8) << type() << "       GP: " << setw(3) <<player->gold()<< "          Floor " << floor << endl;
	cout<<"           HP: " << setw(3) <<player->health() << "/" << player->maxHealth() <<"            Atk:" << setw(3) <<player->att() <<"          Def:" << setw(3) <<player->defence()<<'%' << "          Turn: " << turn << endl;

}

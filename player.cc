#include <string>
#include <cstdlib>
#include <iostream>
#include "PRNG.h"
#include "player.h"
#include "cell.h"
#include "unoccupied.h"
#include "game.h"
#include "item.h"
#include "character.h"

using std::string;
using std::cout;
using std::endl;

Player::Player( int x, int y, char _class )
	: Character(x,y), _gold(0) {
	if ( _class == 'k') {
		_job = 0;
		_maxHealth = _health = 100;
		_attack = _defense = 50;
	}else if ( _class == 'w' ) {
		_job = 1;
		_maxHealth = _health = 60;
		_attack = 25;
		_defense = 0;
	}else if ( _class == 's' ) {
		_job = 2;
		_maxHealth = _health = 80;
		_attack = 50;
		_defense = 15;
	}
}

string Player::getType() {
	switch ( _job ) {
		case 0:
			return "Knight";
		case 1:
			return "Wizard";
		case 2:
			return "Samurai";
	}
	return "";
}
int Player::gold() { return _gold; }

void Player::reset() {
	_stair = false;
	if ( _job == 0 ) {
		_attack = _defense = 50;
	}else if ( _job == 1 ) {
		_attack = 25;
		_defense = 0;
	}else if ( _job == 2 ) {
		_attack = 50;
		_defense = 15;
	}
}

//void Player::tick() {}


void Player::move( string dir, Cell **grid ) {
	int row = y(), col = x();
	string s = dir;
	if (s == "no") {
		row--; 
	} else if (s == "so") {
		row++;
	} else if (s == "ea") {
		col++;
	} else if (s == "we") {
		col--;
	} else if (s == "ne") {
		row--; col++;
	} else if (s == "nw") {
		row--; col--;
	} else if (s == "se") {
		row++; col++; 
	} else if (s == "sw") {
		row++; col--;
	} 
	if (grid[row][col].display() == '>') {
		advance(true);
	}else if ( grid[row][col].display() == '$' ) {
		grid[row][col].getContents()->itemEffect(this, true);
	}else if ( (grid[row][col].display() == ' ') ||
			  		 (grid[row][col].display() == '-') ||
			  		 (grid[row][col].display() == '|') ||
			  		 (grid[row][col].display() == '!') ||
			  		 (grid[row][col].display() == 'g') ||
			  		 (grid[row][col].display() == 'X') ||
			  		 (grid[row][col].display() == 'M') ||
			  		 (grid[row][col].display() == 'O') ||
			  		 (grid[row][col].display() == 'D') ) {
		throw std::ios_base::failure( "You can't move in that direction." );
	}else {
		char t = grid[row][col].display();
		grid[row][col].changeContents(this, '@');
		location(&grid[y()][x()]);
		Unoccupied *_unoccupied = new Unoccupied(x(), y(), true, true);
		int tmpX = y(), tmpY = x();
		y(row);
		x(col);
		grid[tmpX][tmpY].changeContents(_unoccupied, _current);
		_current = t;
	}
}
void Player::attack( string dir, Cell **grid ) {
	int row = y(), col = x();
	string s = dir;
	string skill;
	if (_job == 1) {			// wizard
		int door = 0;		// if there are two or more doors(+) on the way, you cannot attack
		while ( true ) {
			if (s == "no") {
				row--;
			} else if (s == "so") {
				row++;
			} else if (s == "ea") {
				col++;
			} else if (s == "we") {
				col--;
			} else if (s == "ne") {
				row--; col++;
			} else if (s == "nw") {
				row--; col--;
			} else if (s == "se") {
				row++; col++;
			} else if (s == "sw") {
				row++; col--;
			}
			char c = grid[row][col].display();
			if ( c == '+' ) door++;
			if ( (c == '|') || (c == '-') || (c == '>') || (c == ' ') || (door == 2) ) {
				throw std::ios_base::failure( "There is nothing there to attack!" );
			}else if ( (c == 'X') || (c == 'g') || (c == 'O') || (c == 'M') || (c == 'D') ) {
				int ceiling = grid[row][col].getContents()->getDefense() == 0 ? 0 : 1;
				int dmg = -(_attack * (100 - grid[row][col].getContents()->getDefense()) / 100 + ceiling);
				grid[row][col].getContents()->setHealth(dmg);
				if ( !grid[row][col].getContents()->isHostile() ) {
					grid[row][col].getContents()->becomeHostile( grid );
					cout << "This is an act of war to every " << grid[row][col].getContents()->getName() << "!" << endl;
				}
				cout << "You attack the " << grid[row][col].getContents()->getName();
				cout << " with your Inifinite Loop Laser for " << -dmg << " damage!" << endl;
				break;
			}else continue;
		}
	}else {							// knight & samurai
		skill = (_job == 0 ? "Sword of Segfault" : "Memory Corruption Katana");
		if (s == "no") {
			row--;
		} else if (s == "so") {
			row++;
		} else if (s == "ea") {
			col++;
		} else if (s == "we") {
			col--;
		} else if (s == "ne") {
			row--; col++;
		} else if (s == "nw") {
			row--; col--;
		} else if (s == "se") {
			row++; col++;
		} else if (s == "sw") {
			row++; col--;
		} 
	
		char c = grid[row][col].display();
		if ( (c == '.') || (c == '|') || (c == '+') || (c == '#') || (c == '>') || (c == '-') ) {
			throw std::ios_base::failure( "There is nothing there to attack!" );
		}
		int ceiling = grid[row][col].getContents()->getDefense() == 0 ? 0 : 1;
		int dmg = -(_attack * (100 - grid[row][col].getContents()->getDefense()) / 100 + ceiling);
		grid[row][col].getContents()->setHealth(dmg);
		if ( !grid[row][col].getContents()->isHostile() ) {
			grid[row][col].getContents()->becomeHostile( grid );
			cout << "This is an act of war to every " << grid[row][col].getContents()->getName() << "!" << endl;
		}
		cout << "You attack the " << grid[row][col].getContents()->getName();
		cout << " with your " << skill << " for " << -dmg << " damage!" << endl;
	}
}
void Player::use( string dir, Cell **grid ) {
	int row = y(), col = x();
	string s = dir;
	if (s == "no") {
		row--;
	} else if (s == "so") {
		row++;
	} else if (s == "ea") {
		col++;
	} else if (s == "we") {
		col--;
	} else if (s == "ne") {
		row--; col++;
	} else if (s == "nw") {
		row--; col--;
	} else if (s == "se") {
		row++; col++;
	} else if (s == "sw") {
		row++; col--;
	} 
	if ( (grid[row][col].display() == '$') || (grid[row][col].display() == '!') ) {
		grid[row][col].getContents()->itemEffect(this, true);
	}else {
		throw std::ios_base::failure( "There is nothing there to use!" );
	}
}

void Player::setHealth( int h ) {
	if ( health() + h > maxHealth() ) { _health = _maxHealth; }
	else if ( health() + h < 0 ) { _health = 0; }
	else { _health += h; }
}
void Player::setAttack( int a ) {
	if ( att() + a > 100 ) { _attack = 100; }
	else if ( att() + a < 0 ) { _attack = 0; }
	else { _attack += a; }
}
void Player::setDefense( int d ) {
	if ( defence() + d > 100 ) { _defense = 100; }
	else if ( defence() + d < 0 ) { _defense = 0; }
	else { _defense += d; }
}
void Player::setGold( int g ) { _gold += g; }

void Player::advance(bool b) { _stair = b; }
bool Player::advance() const { return _stair; }

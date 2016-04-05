#include "PRNG.h"
#include "enemy.h"
#include "game.h"
#include <string>

using std::string;
using std::cout;
using std::endl;

Enemy::Enemy( int x, int y, char c )
	: Character(x,y),_display( c ),_hostile(true) {
	if ( c == 'X' ) {							// Grid Bug
		_type = 0;
		_name = "Grid Bug";
		_health = _maxHealth = 50;
		_attack = 20;
		_defense = 10;
		drop = new Item (_x, _y, prng(6));
	} else if ( c == 'g' ) {				// Goblin
		_type = 1;
		_name = "Goblin";
		_health = _maxHealth = 75;
		_attack = 30;
		_defense = 20;
		//_gold = 10;
		drop = new Item (_x, _y, 6);
	} else if ( c == 'M' ) {				// Merchant
		_type = 2;
		_name = "Merchant";
		_health = _maxHealth = 100;
		_attack = 75;
		_defense = 5;
		//_gold = 10;
		_hostile = false;
		drop = new Item (_x, _y, 6);
	} else if ( c == 'O' ) {					// Orc
		_type = 3;
		_name = "Orc";
		_health = _maxHealth = 120;
		_attack = 30;
		_defense = 30;
		drop = new Item (_x, _y, 6);
	}	else {												// Dragon
		_type = 4;
		_name = "Dragon";
		_health = _maxHealth = 150;
		_attack = 50;
		_defense = 10;
	}
}

char Enemy::getType() { return _type; }
string Enemy::getName() { return _name; }
bool Enemy::isHostile() { return _hostile; }
bool Enemy::canWalk() { return _canWalk; }
bool Enemy::dead() { 
	return ( _health <= 0 ); 
}
int Enemy::detect( Cell **grid ) {
	int _nearby = 0; 				// 0 if nothing, 1 if potion, 2 if player
	if(!_dead) {
		int row = y(), col = x();
		if ( grid[row][col].display() == 'g' ) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (grid[row+i-1][col+j-1].display() == '!') _nearby = 1;
				}
			}
		}
		if ( _hostile ) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (grid[row+i-1][col+j-1].display() == '@') _nearby = 2;
				}
			}
		}
	}
	return _nearby;
}

// Moves enemies in random direction
void Enemy::move( Cell **grid ) {
	int row = y(), col = x();
	int space = 0;
	if (_health > 0) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if ((i == 1) && (j == 1)) continue;
				if (grid[row+i-1][col+j-1].display() == '.') space++;
			}
		}
		if (space != 0) {
			while ( grid[row][col].display() != '.' ) {
				int i = prng(2)-1;			// i, j = [-1,1]
				int j = prng(2)-1;
				row = y()+i;						// Enemy moves randomly vertically
				col = x()+j;						// 					``					horizontally
			}
		}
		if (grid[y()][x()].display() == 'D') {}
		else {
			delete grid[row][col].getContents();
			grid[row][col].changeContents(this, _display);
			location(&grid[row][col]);
			Unoccupied *_unoccupied = new Unoccupied(x(), y(), true, true);
			int tmpY = y(), tmpX = x();
			y(row);
			x(col);
			grid[tmpY][tmpX].changeContents(_unoccupied, '.');
		}
	}
}
// calculates the damage done by the enemy
// and changes the player's HP
void Enemy::attack(Character *player) {
	if ( _hostile ) {
		int ceiling = ( player->getDefense() == 0 ? 0 : 1 );
		int dmg = -((_attack * (100 - player->getDefense()) / 100) + ceiling);
		player->setHealth(dmg);
		cout << "The evil " << _name << " strikes you for " << -dmg << " damage!" << endl;
	}
}
void Enemy::use(Cell **grid) {
	int row =y(), col=x();
	for (int i = 0; i < 9; i++) {
		if (grid[row][col].display() == '!') {
			row = y() + (i % 3 - 1);
			col = x() + (i / 3 - 1);
		}
	}
	if ( _type == 'g' ) grid[row][col].getContents()->itemEffect(this, false);
}
// for Merchants, and Enemies while playing Samurai
void Enemy::becomeHostile(Cell **grid) {
	for (int i = 0; i < MAX_ROWS; i++) {
		for (int j = 0; j < MAX_COLS; j++) {
			if ( grid[i][j].display() == _display ) {
				grid[i][j].getContents()->hostile(true);
			}
		}
	}
}

void Enemy::hostile(bool b) {
	_hostile=b;
}

void Enemy::setAttack( int a ) {
	if ( att() + a > 100 ) { _attack = 100; }
	else if ( att() + a < 0 ) { _attack = 0; }
	else { _attack += a; }
}

void Enemy::setDefense( int d ) {
	if ( defence() + d > 100 ) { _defense = 100; }
	else if ( defence() + d < 0 ) { _defense = 0; }
	else { _defense += d; }
}
// changes the enemy's HP when attacked by the player
// or when goblin drinks a potion
void Enemy::setHealth( int h ) {
	if ( _health + h > _maxHealth ) _health = _maxHealth; 
	else if ( _health + h < 0 ) _health = 0;
	else _maxHealth += h;
}
void Enemy::die() {
	if(!_dead) {
	_dead = true;
		cout << "The " << _name << " has died." << endl;
		if ( _type == 0 ) {							// Grid Bug
			//Item *_item = new Item (x(), y(), prng(6));
			location()->changeContents(drop,'!');
		}else if ( _type == 1 ) {				// Goblin
			//Item _item = new Item (x(), y(), 6);
			location()->changeContents(drop,'$');
		}else if ( _type == 2 ) {				// Merchant
			//Item _item = new Item (x(), y(), 6);
			location()->changeContents(drop,'$');
		}else if ( _type == 3 ) {					// Orc
			//Item _item = new Item (x(), y(), 6);
			location()->changeContents(drop,'$');
		}else {												// Dragon
			Unoccupied *_unoccupied = new Unoccupied(_x, _y, true, true);
			location()->changeContents(_unoccupied,'.');
		}
	}
	//~GameObject();

}

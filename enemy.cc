#include "PRNG.h"
#include "enemy.h"
#include "game.h"
#include <string>

Enemy::Enemy( char c )
	: _hostile( true ), _display( c ) {
	if ( c == 'X' ) {							// Grid Bug
		_type = 0;
		_health = _maxHealth = 50;
		_attack = 20;
		_defense = 10;
		drop = new Item (x(), y(), prng(6));
	}else if ( c == 'g' ) {				// Goblin
		_type = 1;
		_health = _maxHealth = 75;
		_attack = 30;
		_defense = 20;
		_gold = 10;
		drop = new Item (x(), y(), 6)
	}else if ( c == 'M' ) {				// Merchant
		_type = 2;
		_health = _maxHealth = 100;
		_attack = 75;
		_defense = 5;
		_gold = 10;
		hostile = false;
		drop = new Item (x(), y(), 6)
	}else if ( c == 'O' ) {					// Orc
		_type = 3;
		_health = _maxHealth = 120;
		_attack = 30;
		_defense = 30;
		drop = new Item (x(), y(), 6)
	}	else {												// Dragon
		_type = 4;
		_health = _maxHealth = 150;
		_attack = 50;
		_defense = 10;
	}
}

char Enemy::getType() { return _type; }
bool Enemy::isHostile() { return _hostile; }
bool Enemy::canWalk() { return _canWalk; }

// Moves enemies in random direction
void Enemy::move( **Cell grid ) {
	int row = x(), col = y();
	int space = 0;
	for (int i = 0; i < 9; i++) {
		if (grid[x()+(i%3-1)][y()+(i/3-1)].display()) space++;
	}
	while ( !grid[getLocation()->x()][getLocation()->y()].display() != '.' ) {
		if (space == 0) break;
		int i = prng(2)-1;			// i = [-1,1]
		row = x()+i;						// Enemy moves randomly vertically
		col = y()+i;						// 					``					horizontally
	}
	delete grid[row][col].getContents();
	grid[row][col].changeContents(*this, _display);
	location(grid[x()][y()]);
	Unoccupied _unoccupied = new Unoccupied(x(), y(), true, true);
	grid[x()][y()].changeContents(_unoccupied, '.');
	x(row);
	y(col);
}
// for Merchants, and Enemies while playing Samurai
void Enemy::becomeHostile(**Cell grid) {
	for (int i = 0; i <= MAX_ROWS; i++) {
		for (int j = 0; j <= MAX_COLS; j++) {
			if ( grid[i][j].display() == _display ) {
				grid[i][j].getContents->_hostile = true;
			}
		}
	}
}
// calculates the damage done by the enemy
// and changes the player's HP
void Enemy::attack() {
	bool _playerNearby = false;
	int x, y;
	for (int i = 0; i < 9; i++) {
		if (grid[x()+(i%3-1)][y()+(i/3-1)].display() == '@') {
			x = x() + (i % 3 - 1);
			y = y() + (i / 3 - 1);
			_playerNearby = true;
		}
	}
	if ( _hostile && _playerNearby ) {
		int ceiling = ( grid[x][y]->getDefense() == 0 ? 0 : 1 );
		int dmg = -(_attack * (100 - grid[x][y]->getDefense()) / 100 + ceiling);
		grid[x][y]->setHealth(dmg);
	}
}
// changes the enemy's HP when attacked by the player
// or when goblin drinks a potion
void Enemy::setHealth( int h ) {
	if ( _health + h > _maxHealth ) _health = _maxHealth; 
	else if ( _health + h < 0 ) _health = 0;
	else _maxHealth += h;
}
void Enemy::die() {
	if ( _type == 0 ) {							// Grid Bug
		Item _item = new Item (x(), y(), prng(6));
		getLocation()->changeContents(_item);
	}else if ( _type == 1 ) {				// Goblin
		Item _item = new Item (x(), y(), 6);
		getLocation()->changeContents(_item);
	}else if ( _type == 2 ) {				// Merchant
		Item _item = new Item (x(), y(), 6);
		getLocation()->changeContents(_item);
	}else if ( _type == 3 ) {					// Orc
		Item _item = new Item (x(), y(), 6);
		getLocation()->changeContents(_item);
	}	else {												// Dragon
		Unoccupied _unoccupied = new Unoccupied(x(), y(), true, true);
		getLocation()->changeContents(_unoccupied);
	}
	~GameObject();
}

#include "PRNG.h"
#include "enemy.h"
#include <string>

Enemy::Enemy( int i )
	: _hostile( true ) {
	if ( (i == 0) || (i == 1) ) {							// Grid Bug
		type = 0;
		_health = _maxHealth = 50;
		_attack = 20;
		_defense = 10;
		drop = new Item (x(), y(), prng(6));
	}else if ( (i == 2) || (i == 3) ) {				// Goblin
		type = 1;
		_health = _maxHealth = 75;
		_attack = 30;
		_defense = 20;
		_gold = 10;
		drop = new Item (x(), y(), 6)
	}else if ( i == 4 ) {											// Merchant
		type = 2;
		_health = _maxHealth = 100;
		_attack = 75;
		_defense = 5;
		_gold = 10;
		hostile = false;
		drop = new Item (x(), y(), 6)
	}else if ( i == 5 ) {											// Orc
		type = 3;
		_health = _maxHealth = 120;
		_attack = 30;
		_defense = 30;
		drop = new Item (x(), y(), 6)
	}	else {																	// Dragon
		type = 4;
		_health = _maxHealth = 150;
		_attack = 50;
		_defense = 10;
	}
}

char Enemy::getType() { return _type; }
int Enemy::health() { return _health; }
int Enemy::maxHealth() { return _maxHealth; }
int Enemy::attack() { return _attack; }
int Enemy::defense() { return _defense; }
bool Enemy::isHostile() { return _hostile; }
bool Enemy::canWalk() { return _canWalk; }

// Moves enemies in random direction
void Enemy::move() {
	while ( flr[_location->x()][_location->y()] != NULL ) {
		PRNG prng;
		prng.seed(getpid());
		int i = prng(2)-1;			// i = [-1,1]
		x(x()+i);						// Enemy moves randomly vertically
		y(y()+i);						// 					``					horizontally
	}
	setLocation = &this;
}
// for Merchants, and Enemies while playing Samurai
void Enemy::becomeHostile() {
	for (int i = 0; i <= 25; i++) {
		for (int j = 0; j <= 79; j++) {
			if ( (flr[i][j] != NULL) && (flr[i][j]->getType() == getType()) ) {
				floor[i][j]->hostile = true;
			}
		}
	}
}
// calculates the damage taken by the player
// and changes the player's HP
void Enemy::attack( Player p ) {
	if ( _hostile ) {		// && if player is around
		int ceiling = ( p->getDefense() == 0 ? 0 : 1 );
		int dmg = -(atk * (100 - p->getDefense()) / 100 + ceiling);
		p->setHealth(dmg);
	}
}
// changes the enemy's HP when attacked by the player
// or when goblin drinks a potion
void Enemy::setHealth( int h ) {
	if ( _health + h > _maxHealth ) _health = _maxHealth; 
	else if ( _health + h < 0 ) _health = 0;
	else _maxHealth += h;
}

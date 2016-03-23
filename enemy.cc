#include "PRNG.h"
#include "enemy.h"

Enemy::Enemy( int i )
	: hostile( true ) {
	PRNG s;
	if ( (i == 0) || (i == 1) ) {
		type = 'X';
		HP = maxHP = 50;
		atk = 20;
		def = 10;
		loc.row = s();		//
		loc.col = s();		//
	}else if ( (i == 2) || (i == 3) ) {
		type = 'g';
		HP = maxHP = 75;
		atk = 30;
		def = 20;
		loc.row = s();		//
		loc.col = s();		//
	}else if ( i == 4 ) {
		type = 'M';
		HP = maxHP = 100;
		atk = 75;
		def = 5;
		loc.row = s();		//
		loc.col = s();		//
		hostile = false;
	}else if ( i == 5 ) {
		type = 'O';
		HP = maxHP = 120;
		atk = 30;
		def = 30;
		loc.row = s();		//
		loc.col = s();		//
	}	else {
		type = 'D';
		HP = maxHP = 150;
		atk = 50;
		def = 10;
		// loc.row = ;		//
		// loc.col = ;		//
	}
}

char Enemy::getType() {
	return type;
}
Location Enemy::getLocation() {
	return loc;
}
void Enemy::move() {
	PRNG s;
	// ...
}
void Enemy::becomeHostile() {
	hostile = true;
}
void Enemy::attack( Player p ) {
	p->changeHP((atk * (100 - p->getDef()) / 100) + (p->getDef() == 0 ? 0 : 1));
}
void Enemy::changeHP( int h ) {
	if ( HP + h > maxHP ) HP = maxHP;
	else if ( HP + h < 0 ) HP = 0;
	else HP += h;
}
void Enemy::gainPotion( Potion P ) {
	// ...
}
Item dropItem() {
	return drop;
}

#include <string>
#include "player.h"

using std::string;

Player::Player( string cl )
	: gold( 0 ) {
	if ( cl == "Knight" ) {
		job = 0;
		maxHP = HP = 100;
		atk = def = 50;
	}else if ( cl == "Wizard" ) {
		job = 1;
		maxHP = HP = 60;
		atk = 25;
		def = 0;
	}else if ( cl == "Samurai" ) {
		job = 2;
		maxHP = HP = 80;
		atk = 50;
		def = 15;
	}
}

int Player::getCurrentHP() {
	return HP;
}
int Player::getMaxHP() {
	return maxHP;
}
int Player::getAtk() {
	return atk;
}
int Player::getDef() {
	return def;
}
int Player::getGold() {
	return gold;
}
string Player::getClass() {
	return job;
}
Location getLocation() {
	return loc;
}

void changeHP( int h ) {
	if ( HP + h > maxHP ) HP = maxHP;
	else if ( HP + h < 0 ) HP = 0;
	else HP += h;
}
void gainPotion( Potion p ) {
	// ...
}
void gainGold( int g ) {
	gold += g;
}
void move( string dir ) {
	// row = r; col = c; flr = f;
}
void attack( string dir ) {
	if ( dir == "" ) {
		// ...
	}
	
}

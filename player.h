#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include "combat.h"

using std::string;

class Player : public Combat {
	int job;		// 0 - Knight, 1 - Wizard, 2 - Samurai
	int HP, maxHP, atk, def, gold;
	struct Location {
		int row, col, flr;
	}loc;

 public:
	Player( string choice );
	~Player();

	int getCurrentHP();
	int getMaxHP();
	int getAtk();
	int getDef();
	int getGold();
	string getClass();
	Location getLocation();

	void changeHP( int h );
	void gainPotion( Potion p );
	// void endPotion( Potion p );
	void gainGold( int g );
	void move( string dir );
	void attack( string dir );

	void notify();
	bool isWon();
};

#endif

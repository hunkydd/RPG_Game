#ifndef __ENEMY_H__
#define __ENEMY_H__
#include <string>
#include "combat.h"

using std::string;

class Enemy : public Combat {
	char type;				// X - Grid Bug, g - Goblin, M - Merchant
										// O - Orc, D - Dragon
	int HP, maxHP, atk, def;
	bool hostile;
	struct Location {
		int row, col;
	}loc;
	// Item drop;		// ...

	Enemy( int i );
	~Enemy();

	char Enemy::getType();
	Location getLocation();
	void move();
	void attack( &Player p );
	void changeHP( int h );
	void gainPotion();
	Item dropItem();
};
#endif

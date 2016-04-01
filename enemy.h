#ifndef __ENEMY_H__
#define __ENEMY_H__
#include <string>
#include "character.h"

using std::string;

class Enemy : public Character {
	int _type;
	// 0 - Grid Bug, 1 - Goblin, 2 - Merchant, 3 - Orc, 4 - Dragon
	bool _hostile, _canWalk = false, _dead = false;
	Item drop;
	
 public:
	Enemy( int i );
	~Enemy();

	char getType();
	int getAttack();
	int getDefense();
	bool isHostile();
	bool canWalk();
	bool dead();

	void move();
	void becomeHostile();
	void attack( &Player p );
	void changeHealth( int h );
	void gainPotion();
	void die();
};
#endif

#ifndef __ENEMY_H__
#define __ENEMY_H__
#include <string>
#include "character.h"
#include "item.h"

using std::string;

class Enemy : public Character {
	int _type;
	// 0 - Grid Bug, 1 - Goblin, 2 - Merchant, 3 - Orc, 4 - Dragon
	string _name;
	char _display;
	bool _canWalk = false, _dead = false, _canMove;
	bool _hostile;
	GameObject *drop;

	const int MAX_ROWS = 25;
    	const int MAX_COLS = 79;
 public:
	Enemy( int x, int y, char c );
	void hostile(bool b);
	char getType();
	string getName();
	bool isHostile();
	bool canWalk();
	bool dead();
	int detect( Cell **grid );

	void move(Cell **grid);
	void attack (Character *player);
	void use(Cell **grid);
	void becomeHostile(Cell **grid);
	void setAttack( int a );
	void setDefense( int d );
	void setHealth( int h );
	void gainPotion();
	void die();
};
#endif

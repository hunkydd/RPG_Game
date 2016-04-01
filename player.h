#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "character.h"

using std::string;

class Player : public Character {
	int _job;			// 0 - Knight, 1 - Wizard, 2 - Samurai
	int _floor;		// if (flr == 5) && (player enters the stair) game = win;
	int _gold;

 public:
	Player( char _class );
	~Player();

	string getType();
	int health();
	int naxHealth();
	int attack();
	int defense();
	int gold();
	*Cell location();

	void move( string dir, Cell **grid );
	void attack( string dir, Cell **grid );
	void setHealth( int h );
};

#endif

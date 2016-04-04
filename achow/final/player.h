#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "character.h"

using std::string;

class Player : public Character {
	int _job;			// 0 - Knight, 1 - Wizard, 2 - Samurai
	int _gold;
	bool _stair = false;
 public:
	Player(int x, int y, char _class );
	~Player();

	string getType();
	int gold();
	//Cell * location();
	//void tick();
	void reset();
	void move( string dir, Cell ***grid );
	void attack( string dir, Cell ***grid );
	void use( string dir, Cell ***grid );
	void setHealth( int h );
	void setAttack( int a );
	void setDefense( int d );
	void setGold( int g );

	bool advance() const;
	void advance(bool b);
};

#endif

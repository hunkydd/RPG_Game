#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include "cell.h"
//#include "item.h"
//#include "character.h"
//#include "unoccupied.h"
//#include "player.h"
//#include "enemy.h"
// forward declaration because mutual reference
class Cell;

// add public/private/protected members as necessary
class GameObject {
    Cell * _location;
    protected: int _x,_y;
    public:
        GameObject(int x, int y);
	GameObject();
        virtual ~GameObject();

	virtual void itemEffect(GameObject *character);
        virtual void addDragon(GameObject *en);
	virtual int item();
	virtual int getDefense();
	virtual void setHealth(int h);
	virtual bool isHostile();
	virtual void becomeHostile(Cell ***grid);
	virtual bool dead();
	virtual std::string getName();
	virtual void hostile(bool b);

	int x() const;  // getters
        int y() const;

        void x(int x);  // setters
        void y(int y);
        void location(Cell *location);
        Cell *location();
        // Called after every turn
        virtual void tick() = 0;
        virtual bool canWalk() = 0; //was occupied
        virtual bool canSpawn() = 0;     
        //virtual bool canAttack() = 0;
};

#endif

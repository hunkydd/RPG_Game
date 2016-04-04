//Unoccupied is path, walls, empty spaces and stairs
#ifndef UNOCCUPIED_H
#define UNOCCUPIED_H

#include "gameobject.h"

class Unoccupied : public GameObject {
    bool _canWalk; //T-able to walk, F-unable to walk
    bool _canSpawn;
    bool _stair;
    public:
        Unoccupied(int x, int y, bool canWalk, bool canSpawn); // For others
        Unoccupied();
	//Unoccupied(bool canWalk, bool canSpawn); // For stairs
        void tick();
        bool stair();
	void isStair();
        bool canWalk();
        bool canSpawn();
        //bool canAttack();
};

#endif

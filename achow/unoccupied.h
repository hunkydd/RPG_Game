//Unoccupied is path, walls, empty spaces and stairs
#ifndef ITEM_H
#define ITEM_H

#include "gameobject.h"

class Unoccupied : public GameObject {
    bool canWalk //T-able to walk, F-unable to walk
    bool canSpawn;
    bool stair;
    public:
        Unoccupied(int x, int y, bool canWalk, bool canSpawn); // For others
        //Unoccupied(bool canWalk, bool canSpawn); // For stairs
        void tick();
        void stair();
        bool canWalk();
        bool canSpawn();
        //bool canAttack();
};

#endif

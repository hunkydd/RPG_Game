#ifndef ITEM_H
#define ITEM_H

#include "gameobject.h"

class Unoccupied : public GameObject {
    bool valid //F-able to walk, T-unable to walk

    public:
        Unoccupied(int x, int y, bool valid);
        void tick();
        bool occupied();
};

#endif

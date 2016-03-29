#ifndef ITEM_H
#define ITEM_H

#include "gameobject.h"

class Item : public GameObject {
    int item;
    /*
    *0-RH
    *1-BA
    *2-BD
    *3-PH
    *4-WA
    *5-WD
    *6-Gold pile
    *7-Dragon Hoard
    */
    public:
        Item(int x, int y, int item);
        void tick();
};

#endif

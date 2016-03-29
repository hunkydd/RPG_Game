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
    	int itemEffect();  
    	void tick();
    	bool occupied();
};

/*
class Potion : public Item {
	public:
		Potion(int x, int y, int item);
		int itemEffect();
};

class Gold : public Item {
	public:
		Gold(int x, int y, int item);
		int itemEffect();
};
*/
#endif

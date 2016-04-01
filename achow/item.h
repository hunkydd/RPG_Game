#ifndef ITEM_H
#define ITEM_H

#include "gameobject.h"
#include "player.h"

class Item : public GameObject {
    int item;

    //bool gold;
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
    	Item(int item);

    	int item();

    	void itemEffect(Player *player);  
    	void tick(); // dunno
    	bool canWalk();
    	bool canSpawn();
        //bool canAttack();
        bool canPickup();
};

/*
class Potion : public Item {
	public:
		Potion(int x, int y, int item);
		int itemEffect();
};
*/
class DragonGold : public Item {
	Enemy *dragon;
    public:
		DragonGold(int x, int y, int item);
        DragonGold(int item);
        void addDragon(Enemy *dr);
		bool canPickup();
};

#endif

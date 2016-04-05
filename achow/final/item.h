#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include "gameobject.h"
#include "player.h"
#include "character.h"
#include "enemy.h"
#include "unoccupied.h"

class Item : public GameObject {
    protected: int _item;

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
	void item(int i);

    	void itemEffect(Character *character);  
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
	GameObject *dragon;
    public:
	DragonGold(int x, int y, int item);
        DragonGold(int item);
	~DragonGold();
        void addDragon(GameObject *dr);
	bool canPickup();
};

#endif

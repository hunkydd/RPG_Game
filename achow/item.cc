#include <iostream>
#include "item.h"

Item::Item(int x, int y, int item) : GameObject(x,y), item(item){} //For read in generation

Item::Item(int item) : item(item){} //For random generation

void Item::itemEffect(Character *character) {
	switch (item) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
	}
	Unoccupied *tile = new Unoccupied(x,y,true,true);
	_location->changeContents(tile,'.');
}

void Item::item() { return item; }
bool Item::canSpawn() { return false; }
bool Item::canWalk() { return false; }
bool Item::canPickup() { return true; }
//bool Item::canAttack() { return true; }

DragonGold::DragonGold(int x, int y, int item) : Item(x,y,item){}

DragonGold::DragonGold(int item) : item(item){}

void DragonGold::addDragon(Enemy *dr) { dragon = dr; }

bool DragonGold::canPickup() {
	return dragon->dead(); 
}

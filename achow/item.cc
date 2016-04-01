#include <iostream>
#include "item.h"

Item::Item(int x, int y, int item) : GameObject(x,y), item(item){} //For read in generation

Item::Item(int item) : item(item){} //For random generation

void Item::itemEffect(Player *player) {
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
bool Item::canWalk() { return true; }
#include <iostream>
#include "item.h"

using std::cout;
using std::endl;

Item::Item(int x, int y, int item) : GameObject(x,y), item(item){} //For read in generation

Item::Item(int item) : item(item){} //For random generation

void Item::itemEffect(Character *character) {
	switch (item) {
		case 0:
			if(character->location()->display() == '@') cout<< "You chug the Retore Health potion." << endl;
			character->setHealth(30);
			break;
		case 1:
			if(character->location()->display() == '@') cout<< "You chug the Boost Atk potion." << endl;
			character->setAttack(30);
			break;
		case 2:
			if(character->location()->display() == '@') cout<< "You chug the Boost Def potion." << endl;
			character->setDefense(30);
			break;
		case 3:
			if(character->location()->display() == '@') cout<< "You chug the Poison Health potion." << endl;
			character->setHealth(-15);
			break;
		case 4:
			if(character->location()->display() == '@') cout<< "You chug the Wound Atk potion." << endl;
			character->setAttack(-5);
			break;
		case 5:
			if(character->location()->display() == '@') cout<< "You chug the Wound Def potion." << endl;
			character->setDefense(-5);
			break;
		case 6:
			if(character->location()->display() == '@') cout << "You pick up the Gold Pile worth 10GP." << endl;
			character->setGold(10);
			break;
		case 7:
			if (canPickup()) {
				if(character->location()->display() == '@') cout << "You successfully take the Dragon Hoard!" << endl;
				character->setGold(50);
			} else {
				cout << "It would be foolhardy to take the dragon's gold right now." << endl;
			}
			
			break;
	}
	if (canPickup()) {
		Unoccupied *tile = new Unoccupied(x,y,true,true);
		_location->changeContents(tile,'.');
	}
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

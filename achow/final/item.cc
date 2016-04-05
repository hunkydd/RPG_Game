#include <iostream>
#include "item.h"
#include "enemy.h"
#include "unoccupied.h"

using std::cout;
using std::endl;

Item::Item(int x, int y, int item) : GameObject(x,y), _item(item){} //For read in generation

Item::Item(int item) : _item(item){} //For random generation

void Item::itemEffect(Character *character) {
	switch (_item) {
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
		Unoccupied *tile = new Unoccupied(_x,_y,true,true);
		location()->changeContents(tile,'.');
	}
}
void Item::item(int i) { _item=i;}
int Item::item() { return _item; }
bool Item::canSpawn() { return false; }
bool Item::canWalk() { return false; }
bool Item::canPickup() { return true; }
//bool Item::canAttack() { return true; }
void Item::tick() {}
DragonGold::DragonGold(int x, int y, int item) : Item(x,y,item){}

DragonGold::DragonGold(int item): Item(item) {}

DragonGold::~DragonGold() { delete dragon; }

void DragonGold::addDragon(GameObject *dr) { dragon = dr; }

bool DragonGold::canPickup() {
	return dragon->dead(); 
}

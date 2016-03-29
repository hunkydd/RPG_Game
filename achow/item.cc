#include <iostream>
#include "item.h"

Item::Item(int x, int y, int item) : GameObject(x,y), item(item){}

int Item::itemEffect() {
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
}
bool Item::occupied() { return true; }
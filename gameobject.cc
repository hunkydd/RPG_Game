#include <iostream>
#include "gameobject.h"

GameObject::GameObject(int x,int y) : _x(x), _y(y) {
	/*
	Cell *cell = new Cell(x,y,c);
	_location=cell;
	*/
	_location = 0;
}

GameObject::GameObject(){ _location = 0;}

GameObject::~GameObject() {}

int GameObject::x() const {
	return _x;
}
int GameObject::y() const { 
	return _y;
}

void GameObject::x(int x) {
	_x = x;
}  // setters
void GameObject::y(int y) {
	_y = y;
}

void GameObject::location(Cell *location) {
	_location=location;
}

Cell *GameObject::location() { return _location; }

void GameObject::itemEffect(GameObject *character, bool player){}
void GameObject::addDragon(GameObject *en){}
int GameObject::item(){return -1;}
int GameObject::getDefense(){return -1;}
void GameObject::setHealth(int h){}
bool GameObject::isHostile(){return false;}
void GameObject::becomeHostile(Cell **grid){}
bool GameObject::dead(){return false;}
std::string GameObject::getName(){return "";}
void GameObject::hostile(bool b){}

void GameObject::setGold(int g) {}
void GameObject::setAttack(int a) {}
void GameObject::setDefense(int d) {}

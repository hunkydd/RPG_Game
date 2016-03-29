#include <iostream>
#include "gameobject.h"

GameObject::GameObject(int x,int y) : x(x), y(y) {
	/*
	Cell *cell = new Cell(x,y,c);
	_location=cell;
	*/
}
/*
GameObject::~GameObject() {
	delete _location
}
*/
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
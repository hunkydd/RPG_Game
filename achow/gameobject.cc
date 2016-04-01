#include <iostream>
#include "gameobject.h"

GameObject::GameObject( int x, int y, Cell *location )
	: _x(x), _y(y), _location(location) {}

GameObject::~GameObject() {
	delete _location;
}

int GameObject::x() const { return _x; }
int GameObject::y() const { return _y; }
*Cell GameObject::location() { return _location; }

void GameObject::x( int x ) {	_x = x; }  // setters
void GameObject::y( int y ) {	_y = y; }
void GameObject::location( Cell *location ) {
	_location = location;
}

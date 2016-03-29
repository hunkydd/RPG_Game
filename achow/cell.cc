#include <iostream>
#include "cell.h"

Cell::Cell (int x, int y, char display) : _x(x), _y(y), _display(display) {}

Cell::~Cell() {
	delete _contents;
}


int Cell::x() const { return _x; }
int Cell::y() const { return _y; }
char Cell::display() const { return _display; }

void Cell::changeContents(GameObject *contents){
	_contents = contents;
}

*GameObject Cell::getContents() {
	return _content;
}

#include <iostream>
#include "cell.h"

Cell::Cell (int x, int y, char display) : _x(x), _y(y), _display(display) {
	//_content=new Unoccupied(_x,_y,true,true);
}
Cell::Cell(){}
Cell::~Cell() {
	delete _contents;
}


int Cell::x() const { return _x; }
int Cell::y() const { return _y; }
char Cell::display() const { return _display; }

void Cell::changeContents(GameObject *contents, char display){
	_display=display;
	_contents = contents;
}

GameObject *Cell::getContents() {
	return _contents;
}

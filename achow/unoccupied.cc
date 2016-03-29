#include <iostream>
#include "unoccupied.cc"

Unoccupied::Unoccupied(int x, int y, bool valid): GameObject(x,y), valid(valid){}

bool Unoccupied::occupied() { return valid; }
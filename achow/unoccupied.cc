#include <iostream>
#include "unoccupied.cc"

Unoccupied::Unoccupied(int x, int y, bool canWalk, bool canSpawn): GameObject(x,y), canWalk(canWalk), canSpawn(canSpawn), stair(false){}

//Unoccupied::Unoccupied(bool canWalk, bool canSpawn) : canWalk(canWalk), canSpawn(canSpawn){}

bool Unoccupied::canWalk() { return canWalk; }
bool Unoccupied::canSpawn() { return canSpawn; } 
void Unoccupied::Unoccupied() { stair = true; }
bool Unoccupied::stair() { return stair; }

//bool Unoccupied::canAttack() {return false;}
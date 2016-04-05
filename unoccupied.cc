#include <iostream>
#include "unoccupied.h"

Unoccupied::Unoccupied(int x, int y, bool canWalk, bool canSpawn): GameObject(x,y), _canWalk(canWalk), _canSpawn(canSpawn), _stair(false){}
Unoccupied::Unoccupied(){}
//Unoccupied::Unoccupied(bool canWalk, bool canSpawn) : canWalk(canWalk), canSpawn(canSpawn){}

bool Unoccupied::canWalk() { return _canWalk; }
bool Unoccupied::canSpawn() { return _canSpawn; } 
void Unoccupied::isStair() { _stair = true; }
bool Unoccupied::stair() { return _stair; }
void Unoccupied::tick(){}
//bool Unoccupied::canAttack() {return false;}

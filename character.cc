#include "character.h"

Character::Character(int x, int y) : GameObject(x,y){}
  
int Character::health() const { return _health; }
int Character::maxHealth() const { return _maxHealth; }
int Character::att() const { return _attack; }
int Character::defence() const { return _defense; }
bool Character::canWalk() { return false; }
bool Character::canSpawn() { return false; }

void Character::tick(){}
void Character::move(){}
void Character::attack(){}
void Character::use(){}
void Character::setHealth( int h ){}
void Character::setAttack( int a ){}
void Character::setDefense( int d ){}
void Character::setGold( int g){}


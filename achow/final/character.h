#ifndef CHARACTER_H
#define CHARACTER_H
#include "gameobject.h"

class Character : public GameObject {
 protected:
  int _health, _maxHealth, _attack, _defense;
 public:
  Character(int x, int y);

  int health() const;
  int maxHealth() const;
  int att() const;
  int defence() const;
  
  bool canWalk();
  bool canSpawn();

  void tick();    // override from GameObject
  virtual void move();
  virtual void attack();
  virtual void use();
  virtual void setHealth( int h );
  virtual void setAttack( int a );
  virtual void setDefense( int d );
  virtual void setGold( int g);
};

#endif

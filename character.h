#ifndef CHARACTER_H
#define CHARACTER_H
#include "gameobject.h"

class Character : public GameObject {
 protected:
  int _health, _maxHealth, _attack, _defense;
 public:
  Character();

  int _health() const;
  int _maxHealth() const;
  int _attack() const;
  int _defence() const;

  virtual void tick();    // override from GameObject
  virtual void move();
  virtual void attack();
  virtual void setHealth( int h );
  virtual void setAttack( int a );
  virtual void setDefense( int d );
};

#endif

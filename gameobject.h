#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "cell.h"

// forward declaration because mutual reference
class Cell;

// add public/private/protected members as necessary
class GameObject {
  Cell *_location;
  int _x, _y;

 public:
  GameObject(int x, int y, Cell *location);
  ~GameObject();

  int x() const;  // getters
  int y() const;
  *Cell getLocation();

  void x(int);  // setters
  void y(int);
  void location( Cell *location );

  // Called after every turn
  virtual void tick() = 0;
  virtual void setDisplay() = 0;
};

#endif

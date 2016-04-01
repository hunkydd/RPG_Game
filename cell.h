#ifndef CELL_H
#define CELL_H
#include "gameobject.h"

// forward declaration because mutual reference
class GameObject;

class Cell {
  int _x, _y;
  char _display;
  GameObject *_contents;

 public:
  Cell(int x, int y, char display);
  ~Cell();

  int x() const;
  int y() const;
  char display() const;
  *GameObject getContents();

  void changeContents(GameObject *contents);
};

#endif

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fsteram>
#include <string>
#include <istream>
#include "gameobject.h"
#include "item.h"

class Game {
  Cell ***grid;
  int floor;
  int MAX_FLOORS const = 5;
  int MAX_ROWS const = 25;
  int MAX_COLS const = 79;
  int NUM_POTIONS const = 5;
  int NUM_GOLD const = 7;
  int NUM_ENEMIES const = 5;
 public:
	Game (fstream &file);
	~Game();

	bool checkOcc (int x, int y);
	*Item typePot(int x, int y);
	void generatePotion();
	*Item typeGold(int x, int y);
	void generateGold();

	
	void display();
};

#endif

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fsteram>
#include <string>
#include <istream>
#include <cstdlib>
#include "gameobject.h"
#include "item.h"

extern setSeed( uint32_t seed );

class Game {
    Cell ***grid;
    Player *player;
    int floor;
    int MAX_FLOORS const = 5;
    int MAX_ROWS const = 25;
    int MAX_COLS const = 80;
    int NUM_POTIONS const = 5;
    int NUM_GOLD const = 7;
    int NUM_ENEMIES const = 5;

    struct Location {
    	int x, y;
    } loc;
    public:
    	Game (fstream &file);
    	~Game();

    	
    	void genLocation(int f);
    	void spawnPlayer(int f);
    	void spawnStairs(int f);
    	void spawnPotion(int f);
    	void spawnGold(int f);
    	void spawnEnemy(int f);


    	bool canSpawn (int x, int y, int f);
    	bool canWalk(int x, int y);
    	
    	void actions(std::string s);
    	void display();
    	//void nextFloor()
    	//bool win()
};

#endif

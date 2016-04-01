#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fsteram>
#include <string>
#include <istream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include "gameobject.h"
#include "item.h"
#include "cell.h"
#include "unoccupied.h"
#include "character.h"
#include "player.h"
#include "enemy.h"

extern PRNG prng;
extern setSeed( uint32_t seed );

class Game {
    int MAX_FLOORS const = 5;
    int MAX_ROWS const = 25;
    int MAX_COLS const = 79;
    int NUM_POTIONS const = 5;
    int NUM_GOLD const = 7;
    int NUM_ENEMIES const = 5;

    Cell ***grid;
    Player *_player;
    std::list<Enemy *> *enemies;

    int floor;
    int playerRoom = -1;
    bool stopDeath = false;
    bool stopWander = false;

    struct Location {
    	int x, y;
    } loc;


    void genLocation(int f);
    void spawnPlayer(int f);
    void spawnStairs(int f);
    void spawnPotion(int f);
    void spawnGold(int f);
    void spawnEnemy(int f);
    void findHoard(int f,)
    //bool spawnDragon (int x, int y, int f);
    void adjacent(int x, int y, int f);

    public:
    	Game (fstream &file);
    	~Game();

    	

    	bool canSpawn (int x, int y, int f);
    	bool canWalk(int x, int y);
    	
    	void actions(std::string s);
    	void display();
    	//void nextFloor()
    	//bool win()
};

#endif

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include "PRNG.h"
#include "gameobject.h"
#include "item.h"
#include "cell.h"
#include "unoccupied.h"
#include "character.h"
#include "player.h"
#include "enemy.h"

extern PRNG prng;
extern void setSeed( uint32_t seed );

class Game {
    const int MAX_FLOORS = 5;
    const int MAX_ROWS = 25;
    const int MAX_COLS = 81;
    //const int NUM_POTIONS = 5;
    //const int NUM_GOLD = 7;
    //const int NUM_ENEMIES = 5;

    Cell ***grid;
    Player *player=0;
    Unoccupied *playerLoc;
    std::list<Enemy *> *enemies;

    int floor;
    int playerRoom = -1;
    int turn=1;
    bool stopDeath = false;
    bool stopWander = false;
    bool done = false;
    bool playAgain = false;
    
    struct Location {
    	int x = 0;
	int y = 0;
    } loc;

    void genLocation(int f, bool stairs);
    void spawnPlayer(int f);
    void spawnStairs(int f);
    void spawnPotion(int f);
    void spawnGold(int f);
    void spawnEnemy(int f);
    void findHoard(int f, Enemy *en);
    //void findplayer(int f, Enemy *en);
    void adjacent(int x, int y, int f, int centre);
    void setPlayer(int f);
    bool canSpawn (int x, int y, int f);
    bool canWalk(int x, int y);

public:
    Game(std::ifstream &file, bool d, char p);
    ~Game();
		
    void action(std::istream &cmd);
    void display();
    bool win();
    bool play();
    void nextFloor();
    void gameOver();
    std::string type();
};

#endif

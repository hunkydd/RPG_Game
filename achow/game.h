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
    	int x, y;
    } loc;

    void genLocation(int f);
    void spawnPlayer(int f);
    void spawnStairs(int f);
    void spawnPotion(int f);
    void spawnGold(int f);
    void spawnEnemy(int f);
    void findHoard(int f, Enemy *en);
    void findplayer(int f, Enemy *en);
    void adjacent(int x, int y, int f, int centre);
    void setPlayer(int f);
    bool canSpawn (int x, int y, int f);
    bool canWalk(int x, int y);

    public:
    	Game (fstream &file);
    	~Game();

    	


    	
    	void actions(std::string s);
    	void display();
        bool win();
        bool play();
    	void nextFloor();
        void gameOver();
        std::string type();
};

#endif

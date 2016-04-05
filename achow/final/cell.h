#ifndef CELL_H
#define CELL_H

#include "gameobject.h"
//#include "unoccupied.h"
// forward declaration because mutual reference
class GameObject;

class Cell {
    int _x=0;
    int _y=0;
    char _display=' ';
    GameObject *_contents = 0;

    public:
        Cell(int x, int y, char display);
        Cell();
	~Cell();

        int x() const; //getters
        int y() const;
        char display() const;

        void changeContents(GameObject *contents, char display); 
        GameObject * getContents();

};

#endif

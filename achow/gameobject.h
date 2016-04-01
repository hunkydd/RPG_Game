#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// forward declaration because mutual reference
class Cell;

// add public/private/protected members as necessary
class GameObject {
    Cell * _location;
    int _x,_y
    public:
        GameObject(int x, int y);
        ~GameObject();
        int x() const;  // getters
        int y() const;

        void x(int x);  // setters
        void y(int y);
        void location(Cell *location);
        *Cell location();
        // Called after every turn
        virtual void tick() = 0;
        virtual bool canWalk() = 0; //was occupied
        virtual bool canSpawn() = 0;     
        //virtual bool canAttack() = 0;
};

#endif

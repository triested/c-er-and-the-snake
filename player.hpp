#ifndef PLAYER_HPP
#define PLAYER_HPP

/*
 * This file outlines the player class
 * 
 */

#include "grid.hpp"
#include "tools.hpp"
const char icon = '@';

class Player
{
    private:
        int         x;
        int         y;
        int         health;
        int         wealth;
        Grid        *grid;
        //bool        hitInvuln;    //not yet implemented
    public:
        //constructor               //no destructor because Grid handles itself
        Player(Grid *aGrid, const int row, const int col);
        void move(Direction direction);
        //deal player one HP of damage
        void damage();
        void heal();
        int getHealth();
        int getWealth();
        Coords getLocation();
};
#endif

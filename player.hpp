/*
 * This file outlines the player class
 * */

#include "grid.hpp"
#include "tools.cpp"
const char icon = '@';

class Player
{
    private:
        int         x;
        int         y;
        //int         health;
        Grid        *grid;
        //for multiple-heart runs, implement a buffer period after getting
        //hit... maybe flash icon between @ and o?
        //bool        hitInvuln;
    public:
        Player(Grid *aGrid, const int row, const int col);
        //no destructor needed for grid member since it's not allocated here
        void move(Direction direction);
        Coordinates getLocation();
};

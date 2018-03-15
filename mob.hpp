#ifndef MOB_HPP
#define MOB_HPP

/*
 * This class outlines the games mobs: may serve as base class for others
 * later
 * */

#include "grid.hpp"

class Mob
{
    private:
        int     x;
        int     y;
        char    display;
        Grid    *grid;
    public:
        void move();
};
#endif

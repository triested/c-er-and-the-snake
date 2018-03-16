/* Defines stuff you shoot!
 *
 * */
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "tools.hpp"
#include "grid.hpp"

class Projectile
{
    private:
        Grid        *grid;
        char        display;
        Coords      location;
        Direction   direction;
    public:
        Projectile(Grid *grid, Coords location, const Direction direction, const char display = 'c');
        //move one space in the direction it's been fired
        //return false if it hits a wall or mob so that it can be destroyed 
        bool move();
};

#endif

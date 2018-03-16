/* Defines stuff you shoot!
 *
 * */

#include "tools.hpp"

class Projectile
{
    private:
        char        display;
        Coords      location;
        Direction   direction;
    public:
        Projectile(Coords location, const Direction direction, const char display = 'c');
        //move one space in the direction it's been fired
        //return false if it hits a wall or mob so that it can be destroyed 
        bool move();
};

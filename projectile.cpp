#include "projectile.hpp"
/* Data members:
private:
Grid        *grid;
char        display;
Coords      location;
Direction   direction;
*/

Projectile::Projectile(Grid *grid, Coords location, const Direction direction, const char display)
{
    this->grid = grid;
    this->location = location;
    this->direction = direction;
    this->display = display;
    //put the projectile on the board
    grid->setSquare(location.first, location.second, display);
}

//move one space in the direction it's been fired
//return false if it hits a wall or mob so that it can be destroyed 
bool Projectile::move()
{
    bool stillGoing = true;
    grid->setSquare(location.first, location.second, '.');
    //optional: add logic for not stopping at health or gold
    switch(direction)
    {
        case RIGHT:
            location.second++;
            if (grid->isFloor(location.first, location.second))
                grid->setSquare(location.first, location.second, display);
            else if(grid->isMob(location.first, location.second))
            {
                grid->setSquare(location.first, location.second, '.');
                stillGoing = false;
            }
            else
                stillGoing = false;
            break;
        case UP:
            location.first--;
            if (grid->isFloor(location.first, location.second))
                grid->setSquare(location.first, location.second, display);
            else if(grid->isMob(location.first, location.second))
            {
                grid->setSquare(location.first, location.second, '.');
                stillGoing = false;
            }
            else
                stillGoing = false;           
            break;
        case LEFT:
            location.second--;
            if (grid->isFloor(location.first, location.second))
                grid->setSquare(location.first, location.second, display);
            else if(grid->isMob(location.first, location.second))
            {
                grid->setSquare(location.first, location.second, '.');
                stillGoing = false;
            }
            else
                stillGoing = false;
            break;
        case DOWN:
            location.first++;
            if (grid->isFloor(location.first, location.second))
                grid->setSquare(location.first, location.second, display);
            else if(grid->isMob(location.first, location.second))
            {
                grid->setSquare(location.first, location.second, '.');
                stillGoing = false;
            }
            else
                stillGoing = false;
    }
    return stillGoing;
}

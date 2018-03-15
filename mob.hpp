#ifndef MOB_HPP
#define MOB_HPP

/*
 * This class outlines the games mobs.
 * May serve as base class for others later.
 */

#include <utility>
#include <functional>
#include <queue>
#include <cmath>
#include <map>
#include "grid.hpp"
#include "tools.hpp"

using namespace std;

class Mob
{
    // Constructor
    Mob(int x_coord, int y_coord, char repr, Grid *grid);
    // Destructor
    ~Mob();

    private:
        int     mobX;
        int     mobY;
        char    display;
        char    underMob;
        Grid    *grid;
        bool    adjacentToPlayer(Coords location);
        vector<Coords>  pathableNeighbors(Coords location);
    public:
        void move();
};
#endif

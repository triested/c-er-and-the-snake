/* This class manages the overall game state:
 * it controls mobs, the player, projectiles, and the grid.
 * */

#ifndef CLASS_HPP
#define CLASS_HPP

#include "player.hpp"
#include "grid.hpp"
#include "mob.hpp"
#include "projectile.hpp"
#include "tools.hpp"
#include "dun_gen/dungeon.hpp"
#include <vector>
#include <list>
#include <ncurses.h>
using std::vector;
using std::list;

class Game
{
    private:
        Grid                *board;
        Player              *player;
        vector<Mob>         *mobList;
        list<Projectile>    *projList;
    public:
        //instantiate the dungeon
        Game();
        ~Game();
        //move each mob, if a move is available to them
        void moveMobs();
        void print();
        //move or perform other player action for a given key input
        void playerAction(const int key);
};

#endif

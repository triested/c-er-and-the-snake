/* This class manages the overall game state:
 * it controls mobs, the player, projectiles, and the grid.
 * */

#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "grid.hpp"
#include "mob.hpp"
#include "projectile.hpp"
#include "tools.hpp"
#include "dun_gen/dungeon.hpp"
#include <list>
#include <ncurses.h>
using std::list;

class Game
{
    private:
        Grid                *board;
        Player              *player;
        list<Mob>           mobList;
        list<Projectile>    projList;
    public:
        //instantiate the dungeon
        Game();
        ~Game();
        //move each mob, if a move is available to them; delete dead ones
        void moveMobs();
        //move each proj, if a move is available to them
        //delete them if hit wall or mob
        void moveProjectiles();
        //determine if player takes damage this step. returns true if player dies
        bool checkHealth();
        void print();
        //move or perform other player action for a given key input
        void playerAction(const int key);
        //fire a projectile if possible, and add to projList
        void fire(Direction direction);
};

#endif

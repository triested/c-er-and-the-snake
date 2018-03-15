/* This class manages the overall game state:
 * it controls mobs, the player, and the grid.
 * */

#ifndef CLASS_HPP
#define CLASS_HPP

#include "player.hpp"
#include "grid.hpp"
#include "mob.hpp"
#include "tools.hpp"
#include "dun_gen/dungeon.hpp"
#include <vector>

class Game
{
    private:
        Grid        *board;
        Player      *player;
        vector<Mob> mobList;
    public:
        //instantiate the dungeon
        Game();
        ~Game();
        //move each mob, if a move is available to them
        void moveMobs();
        void print();
        //move or perform other player action for a given key input
        void playerAction(const char key);
};

#endif

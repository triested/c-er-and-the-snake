#ifndef GRID_HPP
#define GRID_HPP

/*
 * This file outlines the grid class, which stores the game board.
 * The values are initialized from a file to which generated dungeons
 * have been saved.
 * */
#include <vector>
#include <iostream>
#include <utility>
#include "ncurses.h"
using std::vector;

//define display characters
const char STAIRS = 'S', WALL = '#', DOOR = 'D', FLOOR = '.', PLAYER = '@', MOB = 'x', HEALTH = 'H', GOLD = 'G';
//the amount of map to display on each side of player icon
const int V_OFFSET = 20, H_OFFSET = 40;

class Grid
{
    private:
        vector<vector<char> >  grid;
        int width;
        int length;
        int x_center;
        int y_center;
    public:
        Grid(vector<vector<char> > &board, const int row, const int col);
        bool isStairs(const int &row, const int &col) const;
        bool isWall(const int &row, const int &col) const;
        bool isDoor(const int &row, const int &col) const;
        bool isFloor(const int &row, const int &col) const;
        bool isPlayer(const int &row, const int &col) const;
        bool isMob(const int &row, const int &col) const;
        bool isHealth(const int &row, const int &col) const;
        bool isGold(const int &row, const int &col) const;
        std::pair<int, int> playerLocation() const;
        bool mobsAdjacent() const;
        void recenter(const int row, const int col);
        void setSquare(const int row, const int col, const char aChar);
        void printGrid(const int health);
};

#endif

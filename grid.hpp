#ifndef GRID_HPP
#define GRID_HPP

/*
 * This file outlines the grid class, which stores the game board.
 * The values are initialized from a file to which generated dungeons
 * have been saved.
 * */
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <utility>
using std::vector;
using std::string;
using std::ifstream;

//define display characters
const char WALL = '#', FLOOR = '.', PLAYER = '@', MOB = 'x', HEALTH = 'H', GOLD = 'G';
//the amount of map to display on each side of player icon
const int OFFSET = 20;

class Grid
{
    private:
        vector<string>  grid;
        int width;
        int length;
        int x_center;
        int y_center;
    public:
        Grid(ifstream &inFile);
        bool isWall(const int &row, const int &col) const;
        bool isFloor(const int &row, const int &col) const;
        bool isPlayer(const int &row, const int &col) const;
        bool isMob(const int &row, const int &col) const;
        bool isHealth(const int &row, const int &col) const;
        bool isGold(const int &row, const int &col) const;
        std::pair<int, int> playerLocation() const;
        bool mobsAdjacent(const int &row, const int &col) const;
        void recenter(const int row, const int col);
        void setSquare(const int row, const int col, const char aChar);
        void printGrid();
};

#endif

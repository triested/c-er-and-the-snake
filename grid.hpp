/*
 * This file outlines the grid class, which stores the game board.
 * The values are initialized from a file to which generated dungeons
 * have been saved.
 * */
#include <vector>
#include <fstream>
using std::vector;
using std::ifstream;
//define display characters
const char WALL = '#', FLOOR = '.', MOB = 'x', HEALTH = 'H';
//the amount of map to display on each side of player icon
const int OFFSET = 20;

class Grid
{
    private:
        vector<string>  grid;
        int width;
        int length;
        int x_player;
        int y_player;
    public:
        Grid(ifstream &inFile);
        bool isWall(const int &row, const int &col) const;
        bool isFloor(const int &row, const int &col) const;
        bool mobsAdjacent(const int &row, const int &col) const;
        void setSquare(const int row, const int col, const char aChar);
        void printGrid();
};

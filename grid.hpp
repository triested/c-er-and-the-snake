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
const char WALL = '#', FLOOR = '.';

class Grid
{
    private:
        vector< vector<char> >  grid;
    public:
        Grid(ifstream &inFile);
        bool isWall(const int &row, const int &col) const;
        bool isFloor(const int &row, const int &col) const;
        bool mobsAdjacent(const int &row, const int &col) const;
        void setSquare(const int row, const int col, const char aChar);
};

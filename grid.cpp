#include "grid.hpp"

Grid::Grid(vector<vector<char> > &board, const int row, const int col)
{
    grid = board;
    x_center = row;
    y_center = col;    
}

bool Grid::isWall(const int &row, const int &col) const
{
    return grid[row][col] == WALL;
}


bool Grid::isFloor(const int &row, const int &col) const
{
    return grid[row][col] == FLOOR;
}

bool Grid::isPlayer(const int &row, const int &col) const
{
    return grid[row][col] == PLAYER;
}

bool Grid::isMob(const int &row, const int &col) const
{
    return grid[row][col] == MOB;
}

bool Grid::isHealth(const int &row, const int &col) const
{
    return grid[row][col] == HEALTH;
}

bool Grid::isGold(const int &row, const int &col) const
{
    return grid[row][col] == GOLD;
}

std::pair<int, int> Grid::playerLocation() const
{
    std::pair<int, int> loc (x_center, y_center);
    return loc;
}

bool Grid::mobsAdjacent(const int &row, const int &col) const
{
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if(grid[i][j] == MOB)
            {
                return true;
            }
        }
    }
    return false;
}

void Grid::recenter(const int row, const int col)
{
    x_center = row;
    y_center = col;
}

void Grid::setSquare(const int row, const int col, const char aChar)
{
    grid[row][col] = aChar;
}

void Grid::printGrid()
{
    //print a square with a side length OFFSET*2+1, centered on player
    for(int i = x_center - OFFSET; i < x_center + OFFSET; i++)
    {
        for(int j = y_center - OFFSET; j < y_center + OFFSET; j++)
        {
            printw("%c", grid[i][j]);
        }
        printw("\n");
    }
}

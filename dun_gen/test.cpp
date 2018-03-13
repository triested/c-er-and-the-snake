// Test random room generation.
// Sam Champer
// CIS 330

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "room.hpp"
#include "dungeon.hpp"

using namespace std;

int main()
{
    srand(time(NULL));
    vector< vector<char> > grid;
    Dungeon D = Dungeon();
    grid = D.getGrid();

    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }
    return 0;
}

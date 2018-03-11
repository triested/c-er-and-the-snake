Grid::Grid(ifstream &inFile)
{
    string tempString;
    while(!inFile.eof())
    {
        getline(inFile, tempString);
        grid.push_back(tempString);
    }
    width = tempString.length();
    length = grid.length();
    //find player's starting position
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(grid[i][j] == '@')
            {
                x_player = i;
                y_player = j;
            }
        }
    }
}

bool Grid::isWall(const int &row, const int &col) const
{
    return grid[row][col] == WALL;
}


bool Grid::isFloor(const int &row, const int &col) const
{
    return grid[row][col] == FLOOR;
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


void Grid::setSquare(const int row, const int col, const char aChar)
{
    grid[row][col] = aChar;
}

void Grid::printGrid()
{
    //print a square with a side length OFFSET*2+1, centered on player
    for(int i = x_player - OFFSET; i < x_player + OFFSET; i++)
    {
        for(int j = y_player - OFFSET; j < y_player + OFFSET; j++)
        {
            cout << grid[i][j];
        }
    }
}

// Implementation of room to make a dungeon for the final project.
// Sam Champer
// CIS 330

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <stdlib.h>
#include "room.hpp"


using namespace std;

Room::Room(char floor)
{
    // Set class variables.
    this->maxDim = randint(8, 22);
    this->height = maxDim;
    this->width = maxDim;
    this->floortype = floor;

    // Start the grid as array of ' 's.
    grid.resize(maxDim, vector<char>(width, ' '));

    // Room is going to be a composition of 1 to 4 rectangular areas:
    int num_rects = randint(1,4);
    int placed_rects = 0;

    while (placed_rects < num_rects)
    {
        // Generate a start seed to place this rect:
        Coords seed (randint(0, maxDim - 1), randint(0, maxDim - 1));
        int w = randint(int(maxDim / num_rects), int((1.6 * maxDim) / num_rects));
        int h = randint(int(maxDim / num_rects), int((1.6 * maxDim) / num_rects));
        bool retval;
        if (placed_rects == 0)
        {
            retval = makeFirstRect(seed, w, h);
        }
        else
        {
            retval = makeRect(seed, w, h);
        }
        if (retval)
            placed_rects += 1;
    }
    // Rects have been placed.

    // Because of placement logic, rooms tend to have a somewhat predictable arrangement,
    // so lets flip them around a bit, for a more even distribution.
    int flip_x = randint(0, 1);
    int flip_y = randint(0, 1);
    if (flip_x){
        for (int i = 0; i < height; ++i) {
            reverse(grid[i].begin(), grid[i].end());
        }
    }
    if (flip_y){
        reverse(grid.begin(), grid.end());
    }

    // Now add some walls with doors.
    makeWalls();
    // Finally, trim down unused space in the vectors.
    trim();
}

Room::~Room(){}

int Room::randint(int low, int high)
{
    // Just a helper function to return a random range.
    int x = low + (rand() % (high-low+1));
    return x;
}

vector< vector<char> > Room::getGrid()
{
    // Public function for returning the final room.
    return grid;
}

vector<char> Room::withinN(Coords coord, int n)
{
    // Returns a vector of all tiles within n distance of a coordinate.
    vector<char> v;
    for (int y = coord.second - n; y < coord.second + n; ++y)
    {
            for (int x = coord.first - n; x < coord.first + n; ++x)
            {
                if (x >= 0 && y >= 0 && y < height && x < width && (x != 0 || y != 0))
                    v.push_back(grid[y][x]);
            }
    }
    return v;
}

vector<char> Room::neighbors(Coords coord)
{
    // Returns a vector of all tiles adjacent to a coordinate.
    return withinN(coord, 1);
}

vector<char> Room::orthogNeighbors(Coords coord)
{
    // Returns a vector of all tiles orthogonally adjacent to a coordinate.
    vector<char> v;
    for (int y = coord.second - 1; y < coord.second + 1; ++y)
    {
            for (int x = coord.first - 1; x < coord.first + 1; ++x)
            {
                if (x >= 0 && y >= 0 && y < height && x < width && (x != 0 || y != 0) && (x == 0 || y == 0))
                    v.push_back(grid[y+1][x+1]);
            }
    }
    return v;
}

bool Room::setLocPadded(Coords coord, int padding, char tile)
{
    // Function to set the value of a coordinate in the grid.
    // Function has a padding feature to restrict setting the value
    // of tiles that are next to the edge of the grid, as edge tiles
    // need to be reserved in order to make walls and hallways next
    // to the floor of the room.
    if (coord.second >= padding && coord.second < height - padding &&
            coord.first >= padding && coord.first < width - padding)
    {
        grid[coord.second][coord.first] = tile;
        return true;
    }
    return false;
}

char Room::getLoc(Coords coord)
{
    if (coord.second >= 0 && coord.second < width && coord.first >= 0 && coord.first < height)
        return grid[coord.second][coord.first];
    else
        return ' ';
}

bool Room::makeFirstRect(Coords coord, int w, int h)
{
    // Function to draw the first rect.
    bool retval = false;
    for (int y = coord.second - int(w/2 + 0.5) ; y < coord.second + int(w/2 + 0.5); ++y)
    {
        for (int x = coord.first - int(h/2 + 0.5) ; x < coord.first + int(h/2 + 0.5); ++x)
        {
            Coords loc (x,y);
            bool tilePlaced = setLocPadded(loc, 2, floortype);
            if (tilePlaced)
                retval = true;
        }
    }
    return retval;
}

bool Room::makeRect(Coords coord, int w, int h)
{
    // Function to draw additional rects that are guaranteed to overlap with one already drawn.
    // First check to make sure the square we will draw will overlap:
    bool overlap = false;
    for (int y = coord.second - int(w/2 + 0.5) ; y < coord.second + int(w/2 + 0.5); ++y)
    {
        for (int x = coord.first - int(h/2 + 0.5) ; x < coord.first + int(h/2 + 0.5); ++x)
        {
            Coords loc (x,y);
            if (getLoc(loc) != ' ')
                overlap = true;
        }
    }
    // If the square won't overlap, we don't want to add it.
    if (not overlap)
        return false;

    // If the square will overlap, we can add it.
    for (int y = coord.second - int(w/2 + 0.5) ; y < coord.second + int(w/2 + 0.5); ++y)
    {
        for (int x = coord.first - int(h/2 + 0.5) ; x < coord.first + int(h/2 + 0.5); ++x)
        {
            Coords loc (x,y);
            setLocPadded(loc, 2, floortype);
        }
    }
    return true;
}

void Room::makeWalls()
{
    // Function to make walls around the floor of the room.
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Coords loc (x,y);
            vector<char> n = neighbors(loc);
            int floor = count(n.begin(), n.end(), floortype);
            if (floor != 0 && getLoc(loc) == ' ')
                setLocPadded(loc, 1, '#');
        }
    }
}

vector< vector<char> > Room::trim()
{
    return grid;
}



/*
void Board::run(int numSteps) {
    // First display starting condition.
    cout << "Starting world:" << endl;
    display(even);
    for (int i = 0; i < numSteps; ++i) {
        // Check if this is an even or odd step.
        curStep += 1;
        cout << "Step " << curStep << ":" << endl;
        if (curStep % 2 == 1){
            // Take a step, then display the board.
            step(odd, even);
            display(odd);
        }else{
            // Take a step, then display the board.
            step(even, odd);
            display(even);
        }
    }
    cout << endl;
}

void Board::step(vector< vector<char> > & grid, vector< vector<char> > & prev) {
    // Iterate through the grid and apply
    // all of the rules for predation and reproduction.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            // Figure out some stuff about neighboring tiles:
            vector<char> n = neighbors(prev, x, y);
            int sheepCount = count(n.begin(), n.end(), 'S');
            int wolfCount = count(n.begin(), n.end(), 'W');
            int farmerCount = count(n.begin(), n.end(), 'F');

            // Rule 1.1: Sheep overpopulation.
            if (prev[y][x] == 'S'){
                if (sheepCount > 3) {
                    grid[y][x] = '.';
                }
            }
            // Rule 1.2: Wolf overpopulation.
            if (prev[y][x] == 'W'){
                if (wolfCount > 3) {
                    grid[y][x] = '.';
                }
            }
            // Rule 2: Wolves predate sheep.
            if (prev[y][x] == 'S'){
                if (wolfCount > 0) {
                    grid[y][x] = '.';
                }
            }
            // Rule 3: Reproduction.
            if (prev[y][x] == '.'){
                if (sheepCount == 2) {
                    grid[y][x] = 'S';
                }else if (wolfCount == 2) {
                    grid[y][x] = 'W';
                }else if (farmerCount == 2) {
                    grid[y][x] = 'F';
                }else{
                    grid[y][x] = '.';
                }
            }
            // Rule 4: Farmers predate wolves.
            if (prev[y][x] == 'W'){
                if (farmerCount > 0) {
                    grid[y][x] = '.';
                }
            }
            // Rule 5: Wolf starvation.
            if (prev[y][x] == 'W'){
                if (sheepCount == 0) {
                    grid[y][x] = '.';
                }
            }
        }
    }

    */
/*I decided that farmer movement should be based on the current grid,
    * rather than on the state of the previous grid. Thus, farmer movement
    * occurs in a separate pass through the grid.*//*


    // Rule 6: Farmer movement.
    // Do a pass through the current board to have farmers move.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (prev[y][x] == 'F') {
                vector<char> n = neighbors(grid, x, y);
                int emptyCount = count(n.begin(), n.end(), '.');
                if (emptyCount > 0) {
                    grid[y][x] = '.';

                    // This is such a hideous way to do this...
                    vector< vector<int> > targets;
                    if (y != 0) { // Add the upper neighbor.
                        if (grid[y-1][x] == '.'){ // If that spot is empty.
                            targets.push_back({y-1,x});
                        }
                    }
                    if (y != height - 1){ // Add lower neighbor.
                        if (grid[y+1][x] == '.'){ // If that spot is empty.
                            targets.push_back({y+1,x});
                        }
                    }
                    if (x != 0) { // Add left.
                        if (grid[y][x-1] == '.'){ // If that spot is empty.
                            targets.push_back({y,x-1});
                        }
                    }
                    if (x != width - 1) { // Add right.
                        if (grid[y][x+1] == '.'){ // If that spot is empty.
                            targets.push_back({y,x+1});
                        }
                    }
                    if (y != 0 && x!= 0){ // Add ul
                        if (grid[y-1][x-1] == '.'){ // If that spot is empty.
                            targets.push_back({y-1,x-1});
                        }
                    }
                    if (y != 0 && x!= width){ // Add ur
                        if (grid[y-1][x+1] == '.'){ // If that spot is empty.
                            targets.push_back({y-1,x+1});
                        }
                    }
                    if (y != height - 1 && x!= 0){ // Add ll
                        if (grid[y+1][x-1] == '.'){ // If that spot is empty.
                            targets.push_back({y+1,x-1});
                        }
                    }
                    if (y != height - 1 && x!= width - 1){ // Add ll
                        if (grid[y+1][x+1] == '.'){ // If that spot is empty.
                            targets.push_back({y+1,x+1});
                        }
                    }
                    // Randomly choose one of the possible targets added to the vector.
                    int choice = rand() % targets.size();
                    // Set the coordinates of that target to a farmer.
                    grid[targets[choice][0]][targets[choice][1]] = 'F';
                }
            }
        }
    }
}

void Board::display(vector< vector<char> > & grid) {
    // Print all data from the board.
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

vector<char> Board::neighbors(vector< vector<char> > & grid, int x, int y) {
    // Collects all neighbors for a given tile and returns them as a vector.
    vector<char> v;

    if (y != 0) // Add the upper neighbor.
        v.push_back(grid[y-1][x]);
    if (y != height - 1) // Add lower neighbor.
        v.push_back(grid[y+1][x]);

    if (x != 0) // Add left.
        v.push_back(grid[y][x-1]);
    if (x != width - 1) // Add right.
        v.push_back(grid[y][x+1]);

    if (y != 0 && x!= 0) // Add ul.
        v.push_back(grid[y-1][x-1]);
    if (y != 0 && x!= width - 1) // Add ur.
        v.push_back(grid[y-1][x+1]);

    if (y != height - 1 && x!= 0) // Add ll.
        v.push_back(grid[y+1][x-1]);
    if (y != height - 1 && x!= width - 1) // Add lr.
        v.push_back(grid[y+1][x+1]);

    return v;
}
*/

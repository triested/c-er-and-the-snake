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

Room::Room(char floor, vector<char> objs)
{
    // Set class variables.
    this->maxDim = randint(8, 22);
    this->height = maxDim;
    this->width = maxDim;
    this->floortype = floor;
    this->objects = objs;
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
    // Next, trim down unused space in the vectors that make up the grid.
    grid = trim();

    //Finally, decorate the room with the objects we want in it:
    decorate();
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
    for (int y = coord.second - n; y < coord.second + n + 1; ++y)
    {
        for (int x = coord.first - n; x < coord.first + n + 1; ++x)
        {
            if (x >= 0 && y >= 0 && y < height && x < width && (x != coord.first || y != coord.second))
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
    for (int y = coord.second - 1; y < coord.second + 2; ++y)
    {
        for (int x = coord.first - 1; x < coord.first + 2; ++x)
        {
            if (x >= 0 && y >= 0 && y < height && x < width &&
                    (x != coord.first || y != coord.second) && (x == coord.first || y == coord.second))
                v.push_back(grid[y][x]);
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
    vector<Coords> walls;
    // Function to make walls around the floor of the room.
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Coords loc (x,y);
            vector<char> n = neighbors(loc);
            int floor = count(n.begin(), n.end(), floortype);
            if (floor != 0 && getLoc(loc) == ' ')
            {
                // Every tile that has an adjacent floor and is empty gets set to a wall.
                setLocPadded(loc, 1, '#');
                walls.push_back(loc);
            }
        }
    }
    // Now that a vector of the coordinates of the wall tiles has been created, lets place some doors.
    int numDoors = randint(1,4);
    int placedDoors = 0;

    // Make twenty attempts to place n doors.
    for (int i = 0; i < 20; ++i)
    {
        int choice = randint(0, walls.size() - 1);
        vector<char> n = orthogNeighbors(walls[choice]);
        int blanks = count(n.begin(), n.end(), ' ');
        int floors = count(n.begin(), n.end(), floortype);
        // Don't place doors within five spaces of other doors.
        vector<char> withinFive = withinN(walls[choice], 5);
        int doors = count(withinFive.begin(), withinFive.end(), 'D');
        if (blanks != 0 && floors != 0 && doors == 0)
        {
            setLocPadded(walls[choice], 1, 'D');
            placedDoors += 1;
        }
        if (placedDoors == numDoors)
            break;
    }

    //Spaces are also reserved around the floor in order to make sure corridors can be created later.
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Coords loc (x,y);
            vector<char> n = neighbors(loc);
            int wall = count(n.begin(), n.end(), '#');
            int door = count(n.begin(), n.end(), 'D');
            if (wall + door != 0 && getLoc(loc) == ' ')
            {
                // Every tile that has an adjacent wall and is empty gets reserved for hallway.
                setLocPadded(loc, 0, 'R');
            }
        }
    }
}

vector< vector<char> > Room::trim()
{
    // Since the room is generated in a larger grid, there may
    // be a bunch of empty spaces, so those can be trimmed out.
    int min_y = height;
    int max_y = 0;
    int min_x = width;
    int max_x = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Coords loc (x,y);
            if (getLoc(loc) != ' ')
            {
                if (y < min_y)
                    min_y = y;
                if (x < min_x)
                    min_x = x;
                if (y > max_y)
                    max_y = y;
                if (x > max_x)
                    max_x = x;
            }
        }
    }
    // The size of the room has now been determined.
    this->height = max_y - min_y + 1;
    this->width = max_x - min_x + 1;

    vector< vector<char> > newGrid;
    newGrid.resize(height, vector<char>(width, '~'));

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            newGrid[y][x] = grid[y + min_y][x + min_x];
        }
    }
    return newGrid;
}

void Room::decorate()
{
    // Try to place all the objects in the object list class variable to random locations.
    // Try 40 times the number of objects to be placed before giving up.
    int placed = 0;
    for (int i = 0; i < 40 * objects.size() ; ++i) {
        Coords loc (randint(2, width - 2), randint(2, height - 2));
        if (getLoc(loc) == floortype)
        {
            setLocPadded(loc, 0, objects[placed]);
            placed += 1;
        }
        if (placed == objects.size())
            break;
    }
}

void Room::print()
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            cout << grid[y][x];
        }
        cout << endl;
    }
}
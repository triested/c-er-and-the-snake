// Implementation of room to make a dungeon for the final project.
// Sam Champer
// CIS 330

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <cmath>
#include <queue>
#include <stdlib.h>
#include <functional>
#include "room.hpp"
#include "dungeon.hpp"

using namespace std;


template<typename T, typename priority_t>
struct PQ
{
  typedef pair<priority_t, T> PQElement;
  priority_queue <PQElement, vector<PQElement>,
        greater<PQElement>> elements;

  inline bool empty() const
  {
     return elements.empty();
  }

  inline void push(T el, priority_t priority)
  {
    elements.emplace(priority, el);
  }

  T pop()
  {
    T best = elements.top().second;
    elements.pop();
    return best;
  }
};


Dungeon::Dungeon()
{
    // Set class variables.
    this->numRooms = 80;
    this->height = 400;
    this->width = 400;

    // For maybe implementing multiple types of room later.
    this->floortypes = {'.'};
    this->commonEntities = {'G'};
    this->uncommonEntities = {'M','H'};

    // Start the grid as array of ' 's.
    grid.resize(height, vector<char>(width, ' '));

    // First add an entrance and an exit:
    enterExit();
    cout << startLocation.first << " " << startLocation.second << endl;

    // Try to add rooms. Many will fail and not actually be added.
    int placedRooms = 0;
    for (int i = 0; i < 4000; ++i)
    {
        placedRooms += makeRoom();
        if (placedRooms == numRooms)
            break;
    }

    // Now that rooms have been made, clean off reserved tiles.
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Coords loc (x, y);
            if (getLoc(loc) == 'R')
                setLoc(loc, ' ');
        }
    }

    // Now the hard part: connect all the rooms.
    connect();
}

Dungeon::~Dungeon(){}

void Dungeon::enterExit()
{
    // Entrance and exit rooms are boring prefabs:
    vector< vector<char> > exit;
    exit =
          {{'R','R','R','R','R','R','R','R','R','R','R','R'},
           {'R','#','#','#','#','D','#','#','#','#','#','R'},
           {'R','#','.','.','.','.','.','.','.','.','#','R'},
           {'R','#','.','.','.','.','.','.','.','.','#','R'},
           {'R','#','.','.','#','#','#','.','.','.','#','R'},
           {'R','#','.','.','#','S','#','.','.','.','#','R'},
           {'R','#','.','.','.','.','.','.','.','.','#','R'},
           {'R','#','.','.','.','.','.','.','.','.','#','R'},
           {'R','#','#','#','#','#','#','#','#','#','#','R'},
           {'R','R','R','R','R','R','R','R','R','R','R','R'}};
    vector< vector<char> > entrance;
    entrance =
          {{'R','R','R','R','R','R','R','R','R','R','R','R'},
           {'R','#','#','#','#','D','#','#','#','#','#','R'},
           {'R','#','G','H','.','.','.','.','.','.','#','R'},
           {'R','#','G','G','.','.','.','.','.','.','#','R'},
           {'R','#','.','.','H','@','.','G','.','.','#','R'},
           {'R','#','H','.','.','.','G','.','.','.','#','R'},
           {'R','#','.','.','.','.','.','.','G','.','#','R'},
           {'R','#','.','.','.','.','.','.','.','.','#','R'},
           {'R','#','#','#','#','#','#','#','#','#','#','R'},
           {'R','R','R','R','R','R','R','R','R','R','R','R'}};

    // Make sure entrance isn't spawned too close to exit.
    Coords spawnEntrance;
    Coords spawnExit;
    while (true)
    {
        Coords temp1 (randint(50, width - 63), randint(50, height - 63));
        Coords temp2 (randint(50, width - 63), randint(50, height - 63));
        int dist = distance(temp1, temp2);
        if (dist > 50)
        {
            spawnEntrance.first = temp1.first;
            spawnEntrance.second = temp1.second;
            spawnExit.first = temp2.first;
            spawnExit.second = temp2.second;
            break;
        }
    }
    this->startLocation.first = spawnEntrance.first + 6;
    this->startLocation.second = spawnEntrance.second + 5;
    // Now put the rooms on the map.
    for (int y = 0; y < 10; ++y)
    {
        for (int x = 0; x < 12; ++x)
        {
            grid[y + spawnExit.second][x + spawnExit.first] = exit[y][x];
            grid[y + spawnEntrance.second][x + spawnEntrance.first] = entrance[y][x];
        }
    }
}

int Dungeon::makeRoom()
{
    // Make a random room in the dungeon.
    // Choose a random floor type.
    char floor = floortypes[randint(0, floortypes.size() - 1)];

    // Now make a random list of stuff to put in the dungeon.
    vector<char> stuff;
    // Maximum numbers of things to spawn.
    int common = randint(0, 8);
    int uncommon = randint(0, 5);
    int percent = 15;
    for (int i = 0; i < common; ++i)
    {
        stuff.push_back(commonEntities[randint(0, commonEntities.size() - 1)]);
        // randint has an even distrubution, wheras I want
        // a decreasing distribution.
        int r = randint(0, 99);
        percent += 10;
        if (r < percent)
            break;
    }
    percent = 15;
    for (int i = 0; i < uncommon; ++i)
    {
        stuff.push_back(uncommonEntities[randint(0, uncommonEntities.size() - 1)]);
        int r = randint(0, 99);
        percent += 10;
        if (r < percent)
            break;
    }
    vector< vector<char> > roomGrid;
    // Make a room with the floortype
    // and the entities we've randomly chosen.
    Room rm = Room(floor, stuff);
    roomGrid = rm.getGrid();

    int roomWidth = roomGrid[0].size();
    int roomHeight = roomGrid.size();
    Coords roomStartCoord (randint(50, width - 50 - roomWidth),
                           randint(50, height - 50 - roomHeight));

    // If the room overlaps with any
    // previously placed room, don't place it.
    for (int y = 0; y < rm.height; ++y)
    {
        for (int x = 0; x < rm.width; ++x)
        {
            Coords loc (x + roomStartCoord.first, y + roomStartCoord.second);
            if (getLoc(loc) != ' ' && getLoc(loc) != 'R')
            {
                return 0;
            }
        }
    }

    // If the room is too far from any other room, I don't want it.
    vector<char> closeBy = withinN(roomStartCoord, 12);
    int walls = count(closeBy.begin(), closeBy.end(), '#');
    if (walls == 0)
        {
            return 0;
        }

    // If the room didn't overlap, then we add it to the dungeon.
    for (int y = 0; y < rm.height; ++y)
    {
        for (int x = 0; x < rm.width; ++x)
        {
            Coords loc (x + roomStartCoord.first, y + roomStartCoord.second);
            char setTo = roomGrid[y][x];
            setLoc(loc, setTo);
        }
    }
    return 1;
}

vector<Coords> Dungeon::pathableNeighbors(Coords coord)
{
    // Returns a vector of coordinates of tiles adjacent to a tile.
    vector<Coords> v;
    for (int y = coord.second - 1; y < coord.second + 2; ++y)
    {
        for (int x = coord.first - 1; x < coord.first + 2; ++x)
        {
            if (x != coord.first || y != coord.second)
            {
                Coords loc (x, y);
                if (getLoc(loc) == ' ' || getLoc(loc) == 'D')
                    v.push_back(loc);
            }
        }
    }
    return v;
}

void Dungeon::connect()
{
/*Vector of all the unfound doors.
 * Starting door.
 * Function to look for things in an ever expanding circle called f.
 * add start door to a vactor of stuff we have already reached.
 * do f on the start door until we find a dorr
 * make a path to the drr add it to vactor of found things, remove it from the vector of unfound doors.
 * set search location to avg(x,y) vacter of things.
 * search for the next thing.
 * */

    vector<Coords> unfoundDoors;
    vector<Coords> foundDoors;
    vector<Coords> nodes;  // This will contain all of the coordinates that we will be storing to walk from.

    // Step one: make a vector of the coords of all the doors.
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Coords loc(x, y);
            if (getLoc(loc) == 'D')
                unfoundDoors.push_back(loc);
        }
    }
    foundDoors.push_back(unfoundDoors[0]);
    nodes.push_back(unfoundDoors[0]);
    Coords centerPoint (unfoundDoors[0].first, unfoundDoors[0].second);

    unfoundDoors.erase(unfoundDoors.begin());

    while (unfoundDoors.size() > 0)
    {
        // First, find the closest unfound door to the center point of the found doors.
        // Then, draw a path to that door from the closest point
        Coords closestDoor = closest(unfoundDoors, centerPoint, true);
        Coords startPoint = closest(nodes, closestDoor, false);
        vector<Coords> route =  path(closestDoor, startPoint);

        break;
    }

    // Now that corridors have been made, make walls around them.
//    makeWalls();
}

Coords Dungeon::closest(vector <Coords> &nodes, Coords point, bool erase)
{
    // Function to find the node closest to a specified point.
    // Initialise min distance to the maximum possible distance.
    int minDistance = width + height;
    int min_Index;
    for (int i = 0; i < nodes.size(); ++i)
    {
        int dist = distance(nodes[i], point);
        if (dist < minDistance)
        {
            minDistance = dist;
            min_Index = i;
        }
    }
    Coords close;
    close.first = nodes[min_Index].first;
    close.second = nodes[min_Index].second;
    if (erase)
        nodes.erase(nodes.begin() + min_Index);
    return close;
}

vector<Coords> Dungeon::path(Coords start, Coords finish)
{
    // Use some A*-ish pathfinding to get a path from a to b.
    // A* is like Dijkstra's, but with the additional heuristic
    // that nodes that are closer to the destination are given
    // a higher priority in the priority queue.
    vector<Coords> p;  // Vector to return with the path.
    map <Coords, Coords> fromLoc;
    map <Coords, int> costTo;
    PQ <Coords, int> frontier;
    frontier.push(start, 0);

    fromLoc[start] = start;
    costTo[start] = 0;

    while(!frontier.empty())
    {
        Coords current = frontier.pop();

        if (current == finish)
            break;

        vector<Coords> pendingCoords = pathableNeighbors(current);

        for (int i = 0; i < pendingCoords.size(); ++i)
        {
            Coords pending = pendingCoords[i];
            int costToPending = costTo[current] + 1;
            if (costTo.find(pending) == costTo.end() || costToPending < costTo[pending])
            {
                costTo[pending] = costToPending;
                int priorityOfPending = costToPending + distance(pending, finish);
                fromLoc[pending] = current;
                frontier.push(pending, priorityOfPending);
            }
        }
    }

    // Now we can trace back from the end point to the start point
    // in the fromLoc dictionary.

    return p;
}

void Dungeon::makeWalls()
{
    // After corridors have been made, make walls next to them.
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Coords loc (x,y);
            vector<char> n = neighbors(loc);
            int floor = count(n.begin(), n.end(), '.');
            if (floor != 0 && getLoc(loc) == ' ')
                setLoc(loc, '#');
        }
    }
}

void Dungeon:: trim()
{

}

int Dungeon::randint(int low, int high)
{
    // Just a helper function to return a random range.
    int x = low + (rand() % (high-low+1));
    return x;
}

int Dungeon::distance(Coords a, Coords b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vector< vector<char> > Dungeon::getGrid()
{
    // Public function for returning the final dungeon.
    return grid;
}

vector<char> Dungeon::withinN(Coords coord, int n)
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

vector<char> Dungeon::neighbors(Coords coord)
{
    // Returns a vector of all tiles adjacent to a coordinate.
    return withinN(coord, 1);
}

vector<char> Dungeon::orthogNeighbors(Coords coord)
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

void Dungeon::setLoc(Coords coord, char tile)
{
    // Function to set the value of a coordinate in the grid.
    if (coord.second >= 0 && coord.second < height
            && coord.first >= 0 && coord.first < width)
        grid[coord.second][coord.first] = tile;
}

char Dungeon::getLoc(Coords coord)
{
    if (coord.second >= 0 && coord.second < width && coord.first >= 0 && coord.first < height)
        return grid[coord.second][coord.first];
    else
        return ' ';
}
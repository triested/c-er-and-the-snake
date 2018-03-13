#ifndef DUNGEON_HPP_
#define DUNGEON_HPP_

#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> Coords;
typedef pair<Coords, int> PQEntry;


class Dungeon
{
public:
    // Constructor
    Dungeon(int rooms);
    // Destructor
    ~Dungeon();

    // The only public method is one that returns the final dungeon.
    vector< vector<char> > getGrid();

    Coords startLocation;

private:
    // Private data:
    int width, height, numRooms;
    vector< vector<char> > grid;
    vector<Coords> doors;
    vector<char> floortypes;
    vector<char> commonEntities;
    vector<char> uncommonEntities;

    // Helper methods:
    vector<char> withinN(Coords coord, int n);
    vector<char> neighbors(Coords coord);
    vector<char> orthogNeighbors(Coords coord);
    void setLoc(Coords coord, char tile);
    char getLoc(Coords coord);
    int randint(int low, int high);
    int distance(Coords a, Coords b);
    vector<Coords> pathableNeighbors(Coords coord);


	// Methods to do the important things:
    void enterExit();
    int makeRoom();
    void connect();

    Coords closest(vector<Coords> &nodes, Coords point, bool erase);
    vector<Coords> path(Coords a, Coords b);

    void makeWalls();
};

#endif

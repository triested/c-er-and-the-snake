#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> Coords;

class Room
{
public:
    // Constructor
    Room(char floortype);
    // Destructor
    ~Room();

    // The only public method is one that returns the final room.
    vector< vector<char> > getGrid();

private:
    // Private data:
    int maxDim, width, height;
    char floortype;
    vector< vector<char> > grid;

    // Helper methods:
    vector<char> withinN(Coords coord, int n);
    vector<char> neighbors(Coords coord);
    vector<char> orthogNeighbors(Coords coord);
    bool setLocPadded(Coords coord, int padding, char tile);
    char getLoc(Coords coord);
    int randint(int low, int high);

	// Methods to do the important things:
    bool makeFirstRect(Coords coord, int w, int h);
    bool makeRect(Coords coord, int w, int h);
    void makeWalls();
    vector< vector<char> > trim();
};

#endif

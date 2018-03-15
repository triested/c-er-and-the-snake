#include "mob.hpp"



Mob::Mob(int x_coord, int y_coord, char repr)
{
    this->mobX = x_coord;
    this->mobY = y_coord;
    this->display = 'x';
    this->underMob = '.';
//    this->grid = ??
}


~Mob() {}


vector<Coords> Mob::pathableNeighbors(Coords location)
{
    // Returns a vector of the coordinates of tiles adjacent
    // to a given tile into which a mob can try to move.
    vector<Coords> neighbors;
    for (int y = coord.second - 1; y < coord.second + 2; ++y)
    {
        for (int x = coord.first - 1; x < coord.first + 2; ++x)
        {
            // Only want orthogonal tiles, don't want the tile we're starting from.
            if ((x != coord.first || y != coord.second) && (x == coord.first || y == coord.second))
            {
                if (grid->isFloor(y, x) || grid->isGold(y, x) || grid->isHealth(y, x))
                {
                    Coords loc (x, y);
                    neighbors.push_back(loc);
                }
            }
        }
    }
    return neighbors;
}


bool Mob::adjacentToPlayer(Coords location)
{
    // Returns a vector of the coordinates of tiles adjacent
    // to a given tile into which a mob can try to move.
    Coords player;
    player.first = grid->playerLocation().first;
    player.second = grid->playerLocation().second;

    for (int y = coord.second - 1; y < coord.second + 2; ++y)
    {
        for (int x = coord.first - 1; x < coord.first + 2; ++x)
        {
            // Don't want the tile we're starting from.
            if (x != coord.first || y != coord.second)
            {
                Coords loc (x, y);
                if (loc == player)
                    return true;
            }
        }
    }
    return false;
}


void Mob::move()
{
    // A* pathfinding to get a path from the mob to the player.
    // A* is like Dijkstra's, but with the additional heuristic
    // that nodes that are orthogonally closer to the destination
    // are given a higher priority in the priority queue when
    // searching for the route.
    vector<Coords> pathStartToFinish;
    map <Coords, Coords> fromLoc; // map to trace back the path from start to finish.
    map <Coords, int> costTo; // Map to do A* pathfinding with.
    PQ <Coords, int> frontier; // A priority queue to use in pathfinding.

    // Init start and finish to current mob location and player location.
    Coords start;
    Coords finish;
    start.first = mobX;
    start.second = mobY;
    finish.first = grid->playerLocation().first;
    finish.second = grid->playerLocation().second;

    // If the mob is next to the player, it won't move, but will attack instead.
    if (adjacentToPlayer(start))
    {
            //attack();
            return;
    }

    // If mob is not adjacent, it's pathfinding time.
    frontier.push(start, 0);
    fromLoc[start] = start;
    costTo[start] = 0;

    Coords current;
    while(!frontier.empty())
    {
        current = frontier.pop();

        if (current == finish)
            break;

        vector<Coords> pendingCoords = pathableNeighbors(current);

        for (int i = 0; i < pendingCoords.size(); ++i)
        {
            // For each orthogonal neighboring tile the mob can walk to, it will
            // cost one more to get to that tile than to get to the previous tile.
            Coords pending = pendingCoords[i];
            int costToPending = costTo[current] + 1;
            // If that tile is being considered for the first time, or
            // if this route is better, update the cost to that tile.
            if (costTo.find(pending) == costTo.end() || costToPending < costTo[pending])
            {
                costTo[pending] = costToPending;
                // The priority of pending nodes is equal to the base cost to get
                // there plus the orthogonal distance between that tile and the target.
                int distance = abs(pending.first - finish.first) + abs(pending.second - finish.second);
                int priorityOfPending = costToPending + distance;
                fromLoc[pending] = current;
                frontier.push(pending, priorityOfPending);
            }
        }
    }

    if (current =! finish)
        // The most recently considered current coordinate will only be not equal
        // to finish in the event that there is no viable route between the mob
        // and the player, in which case the mob isn't going to move.
        return;

    // Otherwise, trace back to the first tile in the route between the mob and
    // the player, and set the mobs coordinates to that tile.

    // Trace back from the end point to the start point in the fromLoc dictionary.
    Coords next = fromLoc[finish];
    while(next != start)
    {
        current = next;
        next = fromLoc[current];
    }
    // Current is now the tile adjacent to the mob that is on the A* path from the mob to the player.

    // Remember what is on the tile the mob is about to move to.
    if (grid->isFloor(current.second, current.first))
        this->underMob = FLOOR;
    if(grid->isGold(current.second, current.first))
        this->underMob = GOLD;
    if (grid->isHealth(current.second, current.first))
        this->underMob = HEALTH;

    // Update the mob's position.
    this->mobX = current.first;
    this->mobY = current.second;
}

/* Member variables:
Grid                *board;
Player              *player;
list<Mob>           mobList;
list<Projectile>    projList;
*/
#include "game.hpp"

//instantiate the dungeon
Game::Game()
{
    int numRooms = 40; //set with random stuff if desired
    Dungeon d(numRooms);
    vector<vector<char> > grid = d.getGrid();
    board = new Grid(grid, d.startLocation.first, d.startLocation.second);
    player = new Player(board, d.startLocation.first, d.startLocation.second);
    //find mobs and initialize mobList
    int length = grid.size();
    if(length != 0)
    {
        int width = grid[0].size();
        for(int i = 0; i < length; i++)
        {
            for(int j = 0; j < width; j++)
            {
                if(grid[i][j] == 'x')
                    mobList.push_back(Mob(i, j, board));
            }
        }
    }
}

Game::~Game()
{
    if(board)
        delete board;
    if(player)
        delete player;
}

//move each mob, if a move is available to them; delete dead ones
void Game::moveMobs()
{
    std::list<Mob>::iterator it = mobList.begin();
    for(; it != mobList.end(); it++)
    {
        if(it->isDead())
            mobList.erase(it);
        else
            it->move();
    }
}

//move each projectile, if a move is available to them
//delete them if hit wall or mob
void Game::moveProjectiles()
{
    std::list<Projectile>::iterator it = projList.begin();
    while(it != projList.end())
    {
        if(!it->move())
            it = projList.erase(it);
        else
            it++;
    }
}

void Game::print()
{
    board->printGrid();
}

//move or perform other player->action for a given key input
void Game::playerAction(const int key)
{
    switch(key)
    {
        case 'd':
            player->move(RIGHT);
            break;
        case 'w':
            player->move(UP);
            break;
        case 'a':
            player->move(LEFT);
            break;
        case 's':
            player->move(DOWN);
            break;
        case KEY_RIGHT:
            fire(RIGHT);
            break;
        case KEY_UP:
            fire(UP);
            break;
        case KEY_LEFT:
            fire(LEFT);
            break;
        case KEY_DOWN:
            fire(DOWN);
            break;
        //default:
    } 
}

//fire a projectile if possible, and add to projList
void Game::fire(Direction direction)
{
    int x = player->getLocation().first;
    int y = player->getLocation().second;
    switch(direction)
    {
        //if square is mob, just kill and don't spawn projectile
        case RIGHT:
            if(board->isMob(x, y+1))
                board->setSquare(x, y+1, '.');
            else if(board->isFloor(x, y+1))
                projList.push_back(Projectile(board, std::make_pair(x, y+1), RIGHT));
            break;
        case UP:
            if(board->isMob(x-1, y))
                board->setSquare(x-1, y, '.');
            else if(board->isFloor(x-1, y))
                projList.push_back(Projectile(board, std::make_pair(x-1, y), UP));
            break;
        case LEFT:
            if(board->isMob(x, y-1))
                board->setSquare(x, y-1, '.');
            else if(board->isFloor(x, y-1))
                projList.push_back(Projectile(board, std::make_pair(x, y-1), LEFT));
            break;
        case DOWN:
            if(board->isMob(x+1, y))
                board->setSquare(x+1, y, '.');
            else if(board->isFloor(x+1, y))
                projList.push_back(Projectile(board, std::make_pair(x+1, y), DOWN));
        //default:
    }
}

/* Member variables:
Grid        *board;
Player      *player;
vector<Mob> mobList;
*/
#include "game.hpp"
#include <fstream> //delete this once directly constructing dungeon
#include <cstdlib> //delete this once directly constructing dungeon
using std::ifstream; //same
using std::cout;
using std::endl;

//instantiate the dungeon
Game::Game()
{
    ifstream inFile;
    inFile.open("testMap.txt");
    if(!inFile)
    {
        cout << "Map file not found! Exiting." << endl;
        exit(0);
    }
    board = new Grid(inFile);
    inFile.close();
    player = new Player(&board, 33, 45); //magic numbers from testMap.txt
    //mobList logic goes here
}

Game::~Game()
{
    if(board)
        delete board;
    if(player)
        delete player;
}

//move each mob, if a move is available to them
void Game::moveMobs()
{
    int numMobs = mobList.size();
    for(int i = 0; i < numMobs; i++)
        mobList[i].move();
}

void Game::print()
{
    board->printGrid();
}

//move or perform other player action for a given key input
void Game::playerAction(const char key)
{
    switch(key)
    {
        case 'd':
            player.move(RIGHT);
            break;
        case 'w':
            player.move(UP);
            break;
        case 'a':
            player.move(LEFT);
            break;
        case 's':
            player.move(DOWN);
            break;
        case KEY_RIGHT:
            player.fire(RIGHT);
            break;
        case KEY_UP:
            player.fire(UP);
            break;
        case KEY_LEFT:
            player.fire(LEFT);
            break;
        case KEY_DOWN:
            player.fire(DOWN);
            break;
        default:
}

#include "player.hpp"

Player::Player(Grid *aGrid, const int row, const int col): 
grid(aGrid), x(row), y(col), health(3), wealth(0) {}
    
void Player::move(Direction direction)
{
    switch(direction)
    {
        case RIGHT:
            if (grid->isFloor(x, y+1) || grid->isDoor(x, y+1))
            {
                grid->setSquare(x, y, '.');
                y++;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isHealth(x, y+1))
            {
                heal();
                grid->setSquare(x, y, '.');
                y++;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isGold(x, y+1))
            {
                wealth++;
                grid->setSquare(x, y, '.');
                y++;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isStairs(x, y+1))
                throw "Win condition!";
            break;
        case UP:
            if (grid->isFloor(x-1, y) || grid->isDoor(x-1,y))
            {
                grid->setSquare(x, y, '.');
                x--;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isHealth(x-1, y))
            {
                heal();
                grid->setSquare(x, y, '.');
                x--;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isGold(x-1, y))
            {
                wealth++;
                grid->setSquare(x, y, '.');
                x--;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isStairs(x-1, y))
                throw "Win condition!";
            break;
        case LEFT:
            if (grid->isFloor(x, y-1) || grid->isDoor(x, y-1))
            {
                grid->setSquare(x, y, '.');
                y--;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isHealth(x, y-1))
            {
                heal();
                grid->setSquare(x, y, '.');
                y--;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isGold(x, y-1))
            {
                wealth++;
                grid->setSquare(x, y, '.');
                y--;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isStairs(x, y-1))
                throw "Win condition!";
            break;
        case DOWN:
            if (grid->isFloor(x+1, y) || grid->isDoor(x+1, y))
            {
                grid->setSquare(x, y, '.');
                x++;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isHealth(x+1, y))
            {
                heal();
                grid->setSquare(x, y, '.');
                x++;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isGold(x+1, y))
            {
                wealth++;
                grid->setSquare(x, y, '.');
                x++;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            else if(grid->isStairs(x+1, y))
                throw "Win condition!";
    }
}

//damage player one HP
void Player::damage()
{
    health--;
}

//heal player one HP
void Player::heal()
{
    health++;
}

int Player::getWealth()
{
    return wealth;
}

int Player::getHealth()
{
    return health;
}

Coords Player::getLocation()
{
    return std::make_pair(x, y);
}

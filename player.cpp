#include "player.hpp"

Player::Player(Grid *aGrid, const int row, const int col): 
grid(aGrid), x(row), y(col), health(3) {}
    
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
            break;
        case UP:
            if (grid->isFloor(x-1, y) || grid->isDoor(x-1,y))
            {
                grid->setSquare(x, y, '.');
                x--;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            break;
        case LEFT:
            if (grid->isFloor(x, y-1) || grid->isDoor(x, y-1))
            {
                grid->setSquare(x, y, '.');
                y--;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
            break;
        case DOWN:
            if (grid->isFloor(x+1, y) || grid->isDoor(x+1, y))
            {
                grid->setSquare(x, y, '.');
                x++;
                grid->setSquare(x, y, '@');
                grid->recenter(x, y);
            }
    }
}

//damage player one HP
void Player::damage()
{
    health--;
}

int Player::getHealth()
{
    return health;
}

Coords Player::getLocation()
{
    return std::make_pair(x, y);
}

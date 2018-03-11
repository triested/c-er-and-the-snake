#include "player.hpp"

Player::Player(Grid *aGrid, const int row, const int col): 
grid(aGrid), x(row), y(col) {}
    
void Player::move(Direction direction)
{
    switch(Direction)
    {
        case RIGHT:
            if (!grid->isFloor(x, y+1))
            {
                grid->setSquare(x, y, '.');
                y++;
                grid->setSquare(x, y, '@');
            }
            break;
        case UP:
            if (!grid->isFloor(x-1, y))
            {
                grid->setSquare(x, y, '.');
                x--;
                grid->setSquare(x-1, y, '@');
            }
            break;
        case LEFT:
            if (!grid->isFloor(x, y-1))
            {
                grid->setSquare(x, y, '.');
                y--;
                grid->setSquare(x, y, '@');
            }
            break;
        case DOWN:
            if (!grid->isFloor(x+1, y))
            {
                grid->setSquare(x, y, '.');
                y++;
                grid->setSquare(x, y, '@');
            }
    }
}

Coordinates Player::getLocation()
{
    return make_pair(x, y);
}

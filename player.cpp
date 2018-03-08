#include "player.hpp"

Player::Player(Grid *aGrid, const int row, const int col): 
grid(aGrid), x(row), y(col) {}
    
void Player::move(Direction direction)
{
    switch(Direction)
    {
        case RIGHT:
            if (!grid->isWall(x, y+1))
            {
                y++;
                grid->setSquare()
            }
        case UP:
        case LEFT:
        case DOWN:
    }
}

Coordinates Player::getLocation()
{
    return make_pair(x, y);
}

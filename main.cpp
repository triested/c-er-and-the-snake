#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
//#include<unistd.h> //for sleep()
#include<ncurses.h>
#include"game.hpp"
#include"./screens/screens.hpp"

using namespace std;

void displayTitle(int height, int width);

int main()
{
    srand(time(NULL));
    Game game;
    int width, height;
    WINDOW *win;            //initialize ncurses window
    getmaxyx(win, height, width);
    int key;

    if((win = initscr()) == nullptr)
    {
        cerr << "Error initializing ncurses." << endl;
        exit(EXIT_FAILURE);
    }
    keypad(win, 1);         //enable full keyboard use

    /////////display title stuff here
    screens::printIntroSequence(win);

    try
    {
        while(true)
        {
            clear();
            game.print();
            key = wgetch(win);
            game.moveProjectiles();
            if(game.checkHealth())
            {
                break;
            }
            game.playerAction(key);
            game.moveMobs();
        }
        screens::printLoseScreen(win);
    }
    catch(...)
    {
        screens::printWinScreen(win);
    }

    //ncurses cleanup
    delwin(win);
    endwin();
    refresh();

    return 0;
}

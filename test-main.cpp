#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cstring>
#include<unistd.h> //for sleep()
#include<ncurses.h>
#include"grid.hpp"
#include"player.hpp"

using namespace std;

void displayTitle(int height, int width);

int main()
{
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
//    nodelay(stdscr, 1);     //keep user input from pausing program

//    displayTitle(height, width);

    while(true)
    {
        clear();
        game.print();
        key = wgetch(win);
        Game.playerAction(key);
    }

    //ncurses cleanup
    delwin(win);
    endwin();
    refresh();

    return 0;
}

void displayTitle(int height, int width)
{
    /*
    mvaddstr(height/2, width/2 - 6, "Title screen?");
    refresh();
    getch();
    clear();
    mvaddstr(height/2, width/2 - 4, "Authors?");
    refresh();
    char title[] = "The C-er and the Snake";
    char instruct1[] = "Go for the stairs!\n";
    char instruct2[] = "Avoid everything else...";
    //center cursor
    mvaddstr(height/2, width/2 - strlen(title), title);
    refresh();
    getch();
    clear();
    mvaddstr(height/2, width/2 - strlen(instruct1), instruct1);
    refresh();
    getch();
    mvaddstr(height/2 - 1, width/2 - strlen(instruct2), instruct2);
    refresh();
    */
}

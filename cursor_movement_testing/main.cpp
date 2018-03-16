/*
This curses library looks pretty good for what we need to
do. Which is: get user input from arrow keys, and print
over things in the console.
Here are some good documenting sites I found for it:

https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/
http://www.paulgriffiths.net/program/c/curses.php
http://www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html
*/


#include "screens.hpp"

using namespace std;

int main()
{
    //////////////////////////////////////
    // Initialization, moving cursor, and clearing screen.
    //////////////////////////////////////
    // Make a new window thing.
    WINDOW * mainwin;
    if ( (mainwin = initscr()) == NULL ) {
       fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
    }
//    int width; int height;
//    getmaxyx(mainwin,height,width); //Determine window size.
//    // Move the cursor to center of screen.
//    mvaddstr(height/2, width/2 - 6, "Title screen?");
//    refresh(); // Display stuff.
//    getch(); // Wait for user input.
//    clear();
//    mvaddstr(height/2, width/2 - 4, "Authors?");
//    refresh(); // Display the stuff.
//
//    getch(); // Wait for user input.
//    clear();

    screens::printIntroSequence(mainwin);

    ////////////////////////////////////////
    // Printing a grid
    ////////////////////////////////////////
    vector< vector<char> > grid;
    grid.resize(20, vector<char>(20, '.'));
    int movingThing = 0; // Just something to show that.
    int prevThing=0;     // Grid is reprinting as intended.
    char ch;
    while((ch = getch()) != '1')
    {
        clear();
        printw("Press '1' to quit\n");
        prevThing = movingThing;
        movingThing = (movingThing + 1) % 20;
        grid[prevThing][prevThing]= '.';
        grid[movingThing][movingThing] = 'M';

        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                printw("%c ", grid[i][j]);
            }
            printw("\n");
        }
    }

    ///////////////////////////////////////
    // Cleanup
    ///////////////////////////////////////
    delwin(mainwin);
    endwin();
    refresh();
    return 0;
}

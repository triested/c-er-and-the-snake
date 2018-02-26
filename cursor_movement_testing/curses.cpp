/*
This curses library looks pretty good for what we need to
do. Which is: get user input from arrow keys, and print
over things in the console.
Here are some good documenting sites I found for it:

https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/
http://www.paulgriffiths.net/program/c/curses.php
http://www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html
*/

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    // Make a new window thing.
    WINDOW * mainwin;
    if ( (mainwin = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }
    // Move the cursor to address 13,33.
    mvaddstr(13, 33, "1,2,3");
    mvaddstr(14, 33, "4,5,6");
    refresh(); // Display the stuff.
    getch(); // Wait for user input.
    mvaddstr(13, 33, "7,8,9");
    mvaddstr(14, 33, "10,11,12");
    refresh(); // Display the stuff.
    getch();
    delwin(mainwin);
    endwin();
    refresh();

	return 0;
}
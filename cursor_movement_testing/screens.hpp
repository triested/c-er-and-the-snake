// Function to print the intro screens:
// the title, authors, and then tutorial.

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>


namespace screens
{
    void printIntroSequence(WINDOW * win);
    void printWinScreen(WINDOW * win);
    void printLoseScreen(WINDOW * win);

    void printTxtFile(WINDOW * win, const char*  fileName);
}

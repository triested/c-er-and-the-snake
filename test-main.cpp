#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<ncurses.h>
#include"grid.hpp"
#include"player.hpp"

using namespace std;

int main()
{
    string filename = "testMap.txt";
    ifstream inFile;
    if(!inFile)
    {
        cout << "Map file not found! Exiting." << endl;
        exit(0);
    }
    inFile.open(filename);
    Grid board(inFile);
    inFile.close();
    Player player(&board, 33, 45); //magic numbers from TESTMAP
    WINDOW *win;
    char key;

    if((win = initscr()) == nullptr)
    {
        cerr << "Error initializing ncurses." << endl;
        exit(EXIT_FAILURE);
    }

    while(true)
    {
        clear();
        board.printGrid();
        key = wgetch(win);
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
            //default:
            //    player.move(UP);
         }
    }

    //ncurses cleanup
    delwin(win);
    endwin();
    refresh();

    return 0;
}

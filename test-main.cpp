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
    int width, height;
    Player player(&board, 33, 45); //magic numbers from TESTMAP
    WINDOW *win;            //initialize ncurses window
    getmaxyx(win, height, width);
    int key;

    if((win = initscr()) == nullptr)
    {
        cerr << "Error initializing ncurses." << endl;
        exit(EXIT_FAILURE);
    }
    keypad(win, 1);         //enable full keyboard use
    //nodelay(stdscr, 1);     //keep user input from pausing program

    displayTitle(height, width);

    while(true)
    {
        clear();
        key = wgetch(win);
        board.printGrid();
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
            case KEY_RIGHT:
                player.fire(RIGHT);
                break;
            case KEY_UP:
                player.fire(UP);
                break;
            case KEY_LEFT:
                player.fire(LEFT);
                break;
            case KEY_DOWN:
                player.fire(DOWN);
                break;
            //default:
        }
        sleep(5);
    }

    //ncurses cleanup
    delwin(win);
    endwin();
    refresh();

    return 0;
}

void displayTitle(int height, int width)
{
    mvaddstr(height/2, width/2 - 6, "Title screen?");
    refresh();
    getch();
    clear();
    mvaddstr(height/2, width/2 - 4, "Authors?");
    refresh();
    /*
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

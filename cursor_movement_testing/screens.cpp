// Function to print the intro screens:
// the title, authors, and then tutorial.

#include "screens.hpp"

using namespace std;

void screens::printIntroSequence(WINDOW * win)
{
    screens::printTxtFile(win, "title.txt");
    getch(); // Wait for user input.
    screens::printTxtFile(win, "snake.txt");
    getch(); // Wait for user input.
    screens::printTxtFile(win, "authors.txt");
    getch(); // Wait for user input.
    screens::printTxtFile(win, "tutorial.txt");
}

void screens::printTxtFile(WINDOW * win, const char* fileName)
{
    clear(); // Clear the previous screen.

    // Determine window size.
    int width; int height;
    getmaxyx(win, height, width);
    // Have to use nasty C char* to play well with ncurses.
    vector<const char*> fileContents;

    string line;
    // Open specified file.
    ifstream f;
    f.open(fileName);
    while (getline(f, line))
    {
        char *curLine = new char[line.length() + 1];
        strcpy(curLine, line.c_str());
        fileContents.push_back(curLine);
    }
    f.close();
    int numLines = fileContents.size();

    // Get some position stuff for centering the output.
    int startLine = int(height / 2 - numLines / 2);
    for (int i = 0; i < numLines; ++i) {
        int startCol = int(width / 2 - strlen(fileContents[i]) / 2);
        mvaddstr(startLine, startCol, fileContents[i]);
        startLine++;
    }

    // Clear allocated memory.
    for (int i = 0; i < numLines; ++i)
    {
        delete[] fileContents[i];
    }
    refresh(); // Display stuff.

}

void screens::printWinScreen(WINDOW * win)
{
    screens::printTxtFile(win, "win.txt");
    getch(); // Wait for user input.
}
void screens::printLoseScreen(WINDOW * win)
{
    screens::printTxtFile(win, "lose.txt");
    getch(); // Wait for user input.
}


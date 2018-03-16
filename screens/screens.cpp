// Function to print the intro screens:
// the title, authors, and then tutorial.

#include "screens.hpp"

using namespace std;

void screens::printTxtFile(WINDOW * win, const char* fileName)
{
    clear(); // Clear the previous screen.

    // Determine window size.
    int width; int height;
    getmaxyx(win, height, width);
    // Have to use nasty C style char* to play well with ncurses.
    vector<const char*> fileContents;

    string line;
    // Open specified file.
    ifstream f;
    f.open(fileName);
    while (getline(f, line))
    {
        // Add all lines from the file to a vector.
        char *curLine = new char[line.length() + 1];
        strcpy(curLine, line.c_str());
        fileContents.push_back(curLine);
    }
    f.close();
    int numLines = fileContents.size();

    // Print the file contents centered in the window.
    int startLine = int(height / 2 - numLines / 2);
    for (int i = 0; i < numLines; ++i) {
        int startCol = int(width / 2 - strlen(fileContents[i]) / 2);
        mvaddstr(startLine, startCol, fileContents[i]);
        startLine++;
    }

    // Clear memory allocated for the char*s.
    for (int i = 0; i < numLines; ++i)
    {
        delete[] fileContents[i];
    }
    refresh(); // Display stuff.

}

void screens::printIntroSequence(WINDOW * win)
{
    // Print a series of screens on game start.
    screens::printTxtFile(win, "title.txt");
    getch(); // Wait for user input.
    screens::printTxtFile(win, "snake.txt");
    getch(); // Wait for user input.
    screens::printTxtFile(win, "authors.txt");
    getch(); // Wait for user input.
    screens::printTxtFile(win, "tutorial.txt");
    getch(); // Wait for user input.
}

void screens::printWinScreen(WINDOW * win)
{
    // Print the victory screen.
    screens::printTxtFile(win, "win.txt");
    getch(); // Wait for user input.
}
void screens::printLoseScreen(WINDOW * win)
{
    // Print a screen when you lose.
    screens::printTxtFile(win, "lose.txt");
    getch(); // Wait for user input.
}


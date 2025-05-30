#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

// Functions
void showMainMenu(void);
void map(void);
void resetMap(void);
void singlePlay(int);
void compPlay(int);

// Global Variables
const short int rows = 5;
const short int cols = 5;
short int numberofBoats = 5;
short int boatsLeft = numberofBoats;
char mapMain[rows][cols];
char mapCopy[rows][cols];

// MAIN
int main()
{
    system("cls");
    srand(time(0));
    int turns = 10;
    char mainOption;
    char innerOption;

    while (true)
    {
        showMainMenu();
        mainOption = getche();
        system("cls");

        switch (mainOption)
        {
        case '1':
            singlePlay(turns);
            break;
        case '2':
            cout << "Not released yet.\n\nPress any key to go back =>";
            innerOption = getche();
            system("cls");
            break;
        case '3':
            compPlay(turns);
            break;
        case '4':
            cout << "\nINSTRUCTIONS:\n\n";
            cout << "Shoot down all ships within your cannonballs.\n";
            cout << "Enter coordinates (Row Column) to shoot.\n";
            cout << "\nSymbols:\n";
            cout << "  \033[1;32mX\033[0m : Hit\n";
            cout << "  \033[1;31mO\033[0m : Miss\n";
            cout << "  \033[1;33mB\033[0m : Unhit Boat (shown only at end)\n\n";
            cout << "Press any key to return => ";
            innerOption = getche();
            system("cls");
            break;
        default:
            break;
        }
    }

    return 0;
}

// MENU

void showMainMenu()
{
    cout << "\nBattleship : Search and Destroy!\n\n";
    cout << "Main Menu\n\n";
    cout << "1. Single Player\n";
    cout << "2. Multi Player (Coming Soon)\n";
    cout << "3. VS Computer\n";
    cout << "4. How To Play\n\n";
}

// RESET MAP

void resetMap()
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            mapMain[i][j] = mapCopy[i][j] = ' ';
}

// MAP DISPLAY

void map()
{
    system("cls");
    cout << endl << "\t    ";
    for (int j = 1; j <= cols; j++)
        cout << j << "   ";
    cout << endl << endl;

    for (int i = 0; i < rows; i++)
    {
        cout << "\t" << i + 1 << "   ";
        for (int j = 0; j < cols; j++)
        {
            if (mapCopy[i][j] == 'X')
                cout << "\033[1;32m" << mapCopy[i][j] << "\033[0m | ";
            else if (mapCopy[i][j] == 'O')
                cout << "\033[1;31m" << mapCopy[i][j] << "\033[0m | ";
            else
                cout << mapCopy[i][j] << " | ";
        }
        cout << endl << "\t    ";
        if (i < rows - 1)
            for (int j = 0; j < (cols * 4) - 1; j++)
                cout << "-";
        cout << endl;
    }
    cout << endl;
}

// SINGLE PLAYER

void singlePlay(int turns)
{
    resetMap();
    boatsLeft = numberofBoats;
    for (int i = 0; i < numberofBoats; ++i)
    {
        int row, col;
        do {
            row = rand() % rows;
            col = rand() % cols;
        } while (mapMain[row][col] == '1');
        mapMain[row][col] = '1';
    }

    short int score = 0;
    map();
    cout << "Captain, you have " << turns << " cannonballs and " << numberofBoats << " targets. ENGAGE PRECISELY!\n";

    while (turns > 0 && boatsLeft > 0)
    {
        int a, b;
        cout << "Enter coordinates to shoot (row col): ";
        cin >> a >> b;

        // Validate input range
        if (a < 1 || a > rows || b < 1 || b > cols) {
            cout << "Invalid coordinates! Please try again.\n";
            continue;
        }

        a--; b--; // Convert to 0-based indexing

        // Already targeted
        if (mapCopy[a][b] == 'X' || mapCopy[a][b] == 'O') {
            cout << "You already fired at this location. Try again.\n";
            continue;
        }

        if (mapMain[a][b] == '1') {
            mapCopy[a][b] = 'X';
            cout << "\033[1;32mHit!\033[0m\n";
            score++;
            boatsLeft--;
        } else {
            mapCopy[a][b] = 'O';
            cout << "\033[1;31mMiss!\033[0m\n";
        }

        turns--;
        map();
        cout << "Score: " << score << " | Boats Left: " << boatsLeft << " | Turns Left: " << turns << "\n\n";
    }

    // Show final map
    cout << "\nFinal Board (B = boat not hit):\n";
    cout << "\t    ";
    for (int j = 1; j <= cols; j++)
        cout << j << "   ";
    cout << endl << endl;

    for (int i = 0; i < rows; i++)
    {
        cout << "\t" << i + 1 << "   ";
        for (int j = 0; j < cols; j++)
        {
            if (mapCopy[i][j] == 'X')
                cout << "\033[1;32mX\033[0m | ";
            else if (mapCopy[i][j] == 'O')
                cout << "\033[1;31mO\033[0m | ";
            else if (mapMain[i][j] == '1')
                cout << "\033[1;33mB\033[0m | ";
            else
                cout << "  | ";
        }
        cout << endl << "\t    ";
        if (i < rows - 1)
            for (int j = 0; j < (cols * 4) - 1; j++)
                cout << "-";
        cout << endl;
    }

    if (boatsLeft == 0)
        cout << "\nVictory! All enemy ships destroyed!\n";
    else
        cout << "\nMission Failed! Out of cannonballs.\n";
}

// VS COMPUTER 
void compPlay(int turns)
{
    cout << "\nComputer Mode is under construction.\nPress any key to return to the menu => ";
    getch();
}



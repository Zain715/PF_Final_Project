////Project Details

// Group Members:
//  Zain Tariq         (24F-0558)
//  Sania Basharat     (24F-0546)
//  Ammar Nadeem       (24F-0733)

#include <iostream>
#include <Windows.h> //for CLS
#include <stdlib.h>  //for coloured output
#include <conio.h>   //to take input from keyboard
#include <ctime>     // to get the current time in seconds for randomisation
#include <chrono>    //to get the current time in milliseconds for randomisation of real-time processes
using namespace std;

// Global variables
int enemySpeed = 2;
const int numOfEnemies = 6, ebColSize = 4;
int ebArr[numOfEnemies][ebColSize] = {0};
const int row_size = 20, col_size = 50;
char map[row_size][col_size];
int ethanposY = 0, ethanposX = 0;                                           // ethan's torsos x,y coordinates
int obstacleX = 0, obstacleY = 0;                                           // obstacles x and y coordinates
int m = (row_size / 2) + 2, n = row_size - 3;                               // m = starting point, n = end point for random function
int EnemyPos1X, EnemyPos2X, EnemyPos3X, EnemyPos4X, EnemyPos5X, EnemyPos6X; // ask sir if srand can produce the same number
int EnemyPos1Y, EnemyPos2Y, EnemyPos3Y, EnemyPos4Y, EnemyPos5Y, EnemyPos6Y;
int solomonPosX, solomonPosY;
int bulletPosX, bulletPosY;
bool isActive = false;
bool isNotOver = true;
char direction = ' ';
int score;
const int ENTER = 13;
const int KEY_DOWN = 80;
const int KEY_UP = 72;
const int KEY_RIGHT = 77;
const int KEY_LEFT = 75;
const int SPACEBAR = 32;
const int ESCAPE = 27;

// Function prototypes
void displayTitle();
void displayHelp();
void displayMenu();
void initializeMap1(char map[][col_size]);
void initializeMap2(char map[][col_size]);
void initializeRandomMap();
void initializeEnemies(char map[][col_size], int level);
void ethan(char arr[][col_size]);                 // for ethan hunt
void move(char arr[][col_size], char &direction); // to move ethan
void level1Obstacles(char arr[][col_size]);
void level2Obstacles(char arr[][col_size]);
void level3Obstacles(char arr[][col_size]);
void level4Obstacles(char arr[][col_size]);
void level5Obstacles(char arr[][col_size]);
bool solomonCollision(int posY, int posX);
void initialiseSolomon(char map[][col_size]);
void PrintMap();
int RandomMap();
int RandomNumber(int start, int end);
bool collisionCheck(int row, int col);
void trackingEthan(int level);
void updatingEnemyPos(int EnemyPosX, int EnemyPosY, int enemyNumber);
bool enemyCollision(int PosY, int PosX);
bool ethanCollision(int PosY, int PosX);
void updatingSolomonPos(int PosY, int PosX);
void ethanShoot(char arr[][col_size], char direction);
void bulletMovement(char swen);
void enemyKill(int bulletY, int bulletX);
void enemyDisappear(int posX, int posY);
int randomDirection();
void setColor(int color);
bool doorCheck(int PosY, int PosX);
void enemyShoot(int rowY, int colX, int enemyNumber);
void enemyBulletMovement(int rowNum);
void checkHealth(int &health);                                          // add this
void displayHealth(int &health);                                        // add this
void checkingTouchWithEthan(int ethanPosY, int ethanPosX, int &health); // add this
void gameOver();

int main()
{

    int health = 3;
    int level = 1;
    char swen = 'q';
    initializeRandomMap();
    // displayTitle();                 //Called to display the title of the game
    // displayMenu();                  //Called to display the menu
    // system("cls");
    level3Obstacles(map);
    initializeEnemies(map, level);
    initialiseSolomon(map);
    ethan(map);

    setColor(03);
    PrintMap();
    displayHealth(health);
    while (isNotOver)
    {
        direction = _getch();
        // system("cls");
        if (!isActive && (tolower(direction) == 'w' || tolower(direction) == 's' || tolower(direction) == 'a' || tolower(direction) == 'd'))
        {
            ethanShoot(map, direction);
            swen = direction;
        }
        bulletMovement(swen);
        for (int i = 0; i < numOfEnemies; i++)
        {
            if (ebArr[i][0] == 1)
            {
                enemyBulletMovement(i);
            }
        }
        move(map, direction);
        trackingEthan(level);
        enemySpeed++;
        // checkingTouchWithEthan(ethanposY, ethanposX, health); //add this here
        setColor(03);
        PrintMap();
        // displayHealth(health);
        // Sleep(99);
    }
    gameOver();
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// in the move function remove else statements
void checkHealth(int &health)
{
    health--; // Deduct health when Ethan can't move
    if (health == 0)
    {
        isNotOver = false;
    }
}
void displayHealth(int &health)
{
    cout << R"(
  ??????????????????????????????????????????????????????????????
  ?                                                            ?
  ?                                                            ?
         Health: )";
    cout << health;
    cout << R"(                                
  ?                                                            ?
  ?                                                            ?
  ??????????????????????????????????????????????????????????????
)";

    /*cout << "Health: " << health << endl; // Display health in top-left corner*/
}
void checkingTouchWithEthan(int ethanPosY, int ethanPosX, int &health)
{
    // checking around ethan
    if (map[ethanposY - 1][ethanposX - 1] != ' ' || map[ethanposY - 1][ethanPosX + 1] != ' ' || map[ethanposY - 1][ethanposX + 1] != ' ')
    {
        checkHealth(health); // Reduce health
    }
    if (map[ethanposY + 2][ethanposX + 1] != ' ' || map[ethanposY + 2][ethanposX - 1] != ' ' || map[ethanposY + 1][ethanposX] != ' ')
    {
        checkHealth(health); // Reduce health
    }
    if (map[ethanposY][ethanposX - 2] != ' ' || map[ethanposY + 1][ethanposX - 2] != ' ' || map[ethanposY - 1][ethanposX - 1] != ' ')
    {
        checkHealth(health); // Reduce health
    }
    if (map[ethanposY][ethanposX + 2] != ' ' || map[ethanposY + 1][ethanposX + 2] != ' ' || map[ethanposY - 1][ethanposX + 1] != ' ')
    {
        checkHealth(health); // Reduce health
    }
}

bool doorCheck(int PosY, int PosX)
{
    if (((PosY >= (row_size / 2) - 5) && (PosY <= (row_size / 2) + 3)) && (PosX == 0 || PosX == col_size - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void enemyBulletMovement(int rowNum)
{
    int PosY = ebArr[rowNum][1];
    int PosX = ebArr[rowNum][2];
    switch (ebArr[rowNum][3])
    {
    case 'w':
        if (collisionCheck(PosY - 1, PosX))
        {
            map[PosY][PosX] = ' ';
            PosY--;
            map[PosY][PosX] = '*';
            ebArr[rowNum][1] = PosY;
            ebArr[rowNum][2] = PosX;
            break;
        }
        else
        {
            map[PosY][PosX] = ' ';
            ebArr[rowNum][0] = 0;
            // enemyKill(PosY - 1, PosX);
        }
        break;

    case 's':
        if (collisionCheck(PosY + 1, PosX))
        {
            map[PosY][PosX] = ' ';
            PosY++;
            map[PosY][PosX] = '*';
            ebArr[rowNum][1] = PosY;
            ebArr[rowNum][2] = PosX;
            break;
        }
        else
        {
            map[PosY][PosX] = ' ';
            ebArr[rowNum][0] = 0;
            // enemyKill(PosY + 1, PosX);
        }
        break;

    case 'a':
        if (collisionCheck(PosY, PosX - 1) && !(doorCheck(PosY, PosX - 1)))
        {
            map[PosY][PosX] = ' ';
            PosX--;
            map[PosY][PosX] = '*';
            ebArr[rowNum][1] = PosY;
            ebArr[rowNum][2] = PosX;
            break;
        }
        else
        {
            map[PosY][PosX] = ' ';
            ebArr[rowNum][0] = 0;
            // enemyKill(PosY, PosX - 1);
        }
        break;

    case 'd':
        if (collisionCheck(PosY, PosX + 1) && !(doorCheck(PosY, PosX + 1)))
        {
            map[PosY][PosX] = ' ';
            PosX++;
            map[PosY][PosX] = '*';
            ebArr[rowNum][1] = PosY;
            ebArr[rowNum][2] = PosX;
            break;
        }
        else
        {
            map[PosY][PosX] = ' ';
            ebArr[rowNum][0] = 0;
            // enemyKill(PosY, PosX + 1);
        }
        break;
    }
}

void bulletMovement(char swen)
{
    if (isActive)
    {
        switch (swen)
        {
        case 'w':
        case 'W':
            if (collisionCheck(bulletPosY - 1, bulletPosX))
            {
                map[bulletPosY][bulletPosX] = ' ';
                bulletPosY--;
                map[bulletPosY][bulletPosX] = '+';
                break;
            }
            else
            {
                map[bulletPosY][bulletPosX] = ' ';
                isActive = false;
                enemyKill(bulletPosY - 1, bulletPosX);
            }
            break;

        case 's':
        case 'S':
            if (collisionCheck(bulletPosY + 1, bulletPosX))
            {
                map[bulletPosY][bulletPosX] = ' ';
                bulletPosY++;
                map[bulletPosY][bulletPosX] = '+';
                break;
            }
            else
            {
                map[bulletPosY][bulletPosX] = ' ';
                isActive = false;
                enemyKill(bulletPosY + 1, bulletPosX);
            }
            break;

        case 'a':
        case 'A':
            if (collisionCheck(bulletPosY, bulletPosX - 1) && !(doorCheck(bulletPosY, bulletPosX - 1)))
            {
                map[bulletPosY][bulletPosX] = ' ';
                bulletPosX--;
                map[bulletPosY][bulletPosX] = '+';
                break;
            }
            else
            {
                map[bulletPosY][bulletPosX] = ' ';
                isActive = false;
                enemyKill(bulletPosY, bulletPosX - 1);
            }
            break;

        case 'd':
        case 'D':
            if (collisionCheck(bulletPosY, bulletPosX + 1) && !(doorCheck(bulletPosY, bulletPosX + 1)))
            {
                map[bulletPosY][bulletPosX] = ' ';
                bulletPosX++;
                map[bulletPosY][bulletPosX] = '+';
                break;
            }
            else
            {
                map[bulletPosY][bulletPosX] = ' ';
                isActive = false;
                enemyKill(bulletPosY, bulletPosX + 1);
            }
            break;
        }
    }
}

void enemyDisappear(int posX, int posY)
{

    if (posX == EnemyPos1X && posY == EnemyPos1Y)
    {
        EnemyPos1X = 0;
        EnemyPos1Y = 0;
    }
    else if (posX == EnemyPos2X && posY == EnemyPos2Y)
    {
        EnemyPos2X = 0;
        EnemyPos2Y = 0;
    }
    else if (posX == EnemyPos3X && posY == EnemyPos3Y)
    {
        EnemyPos3X = 0;
        EnemyPos3Y = 0;
    }
    else if (posX == EnemyPos4X && posY == EnemyPos4Y)
    {
        EnemyPos4X = 0;
        EnemyPos4Y = 0;
    }
    else if (posX == EnemyPos5X && posY == EnemyPos5Y)
    {
        EnemyPos5X = 0;
        EnemyPos5Y = 0;
    }
    else if (posX == EnemyPos6X && posY == EnemyPos6Y)
    {
        EnemyPos6X = 0;
        EnemyPos6Y = 0;
    }
    score = score + 10;
}

void enemyShoot(int rowY, int colX, int enemyNumber)
{

    char EBdirection;

    if (rowY == ethanposY)
    {
        if ((colX > ethanposX) && (collisionCheck(rowY, colX - 2)))
        {
            EBdirection = 'a';
            if (ebArr[enemyNumber - 1][0] == 0)
            {
                map[rowY][colX - 2] = '*';
                ebArr[enemyNumber - 1][0] = 1;
                ebArr[enemyNumber - 1][1] = rowY;
                ebArr[enemyNumber - 1][2] = colX - 2;
                ebArr[enemyNumber - 1][3] = EBdirection;
            }
        }
        else if (collisionCheck(rowY, colX + 2))
        {
            EBdirection = 'd';
            if (ebArr[enemyNumber - 1][0] == 0)
            {
                map[rowY][colX + 2] = '*';
                ebArr[enemyNumber - 1][0] = 1;
                ebArr[enemyNumber - 1][1] = rowY;
                ebArr[enemyNumber - 1][2] = colX + 2;
                ebArr[enemyNumber - 1][3] = EBdirection;
            }
        }
    }
    else if (colX == ethanposX)
    {
        if ((rowY > ethanposY) && (collisionCheck(rowY - 2, colX)))
        {
            EBdirection = 'w';
            if (ebArr[enemyNumber - 1][0] == 0)
            {
                map[rowY - 2][colX] = '*';
                ebArr[enemyNumber - 1][0] = 1;
                ebArr[enemyNumber - 1][1] = rowY - 2;
                ebArr[enemyNumber - 1][2] = colX;
                ebArr[enemyNumber - 1][3] = EBdirection;
            }
        }
        else if (collisionCheck(rowY + 2, colX))
        {
            EBdirection = 's';
            if (ebArr[enemyNumber - 1][0] == 0)
            {
                map[rowY + 1][colX] = '*';
                ebArr[enemyNumber - 1][0] = 1;
                ebArr[enemyNumber - 1][1] = rowY + 1;
                ebArr[enemyNumber - 1][2] = colX;
                ebArr[enemyNumber - 1][3] = EBdirection;
            }
        }
    }
}

void enemyKill(int contactY, int contactX)
{
    char contact = map[contactY][contactX];
    if (map[contactY][contactX] != '|')
    {
        switch (contact)
        {
        case 'V':
            map[contactY][contactX] = ' ';
            map[contactY][contactX - 1] = ' ';
            map[contactY][contactX + 1] = ' ';

            map[contactY - 1][contactX] = ' ';
            map[contactY - 1][contactX - 1] = ' ';
            map[contactY - 1][contactX + 1] = ' ';
            enemyDisappear(contactX, contactY);
            break;
        case '|':
            map[contactY][contactX] = ' ';
            map[contactY][contactX - 1] = ' ';
            map[contactY][contactX + 1] = ' ';

            map[contactY + 1][contactX] = ' ';
            map[contactY + 1][contactX - 1] = ' ';
            map[contactY + 1][contactX + 1] = ' ';
            enemyDisappear(contactX, contactY - 1);
            break;
        case '[':
            if (map[contactY][contactX + 1] == 'V')
            {
                map[contactY][contactX] = ' ';
                map[contactY][contactX + 2] = ' ';
                map[contactY][contactX + 1] = ' ';

                map[contactY - 1][contactX] = ' ';
                map[contactY - 1][contactX + 2] = ' ';
                map[contactY - 1][contactX + 1] = ' ';
                enemyDisappear(contactX + 1, contactY);
            }
            else if (map[contactY][contactX + 1] == '|')
            {
                map[contactY][contactX] = ' ';
                map[contactY][contactX + 2] = ' ';
                map[contactY][contactX + 1] = ' ';

                map[contactY + 1][contactX] = ' ';
                map[contactY + 1][contactX + 1] = ' ';
                map[contactY + 1][contactX + 2] = ' ';
                enemyDisappear(contactX + 1, contactY - 1);
            }
            break;
        case ']':
            if (map[contactY][contactX - 1] == '|')
            {
                map[contactY][contactX] = ' ';
                map[contactY][contactX - 1] = ' ';
                map[contactY][contactX - 2] = ' ';

                map[contactY + 1][contactX] = ' ';
                map[contactY + 1][contactX - 1] = ' ';
                map[contactY + 1][contactX - 2] = ' ';
                enemyDisappear(contactX - 1, contactY + 1);
            }
            else if (map[contactY][contactX - 1] == 'V')
            {
                map[contactY][contactX] = ' ';
                map[contactY][contactX - 1] = ' ';
                map[contactY][contactX - 2] = ' ';

                map[contactY - 1][contactX] = ' ';
                map[contactY - 1][contactX - 1] = ' ';
                map[contactY - 1][contactX - 2] = ' ';
                enemyDisappear(contactX - 1, contactY);
            }
            break;
        }
    }
}

// Adding enemies
void initializeEnemies(char map[][col_size], int level)
{
    int RandomRow, RandomCol;
    int startRow, endRow;
    int startCol, endCol;
    srand(time(0)); // seeding rand()
    for (int i = 0; i <= level; i++)
    {                                            // for loop to generate number of enemies according to level
        startRow = 2, endRow = row_size / 2 - 2; // bound for random enemy location
        startCol = 2, endCol = col_size - 3;
        do
        {
            RandomRow = RandomNumber(startRow, endRow);
            RandomCol = RandomNumber(startCol, endCol);
        } while (enemyCollision(RandomRow, RandomCol));
        map[RandomRow][RandomCol] = 'V';
        map[RandomRow - 1][RandomCol] = '|';

        map[RandomRow - 1][RandomCol - 1] = '[';
        map[RandomRow - 1][RandomCol + 1] = ']';

        map[RandomRow][RandomCol - 1] = '[';
        map[RandomRow][RandomCol + 1] = ']';

        switch (i)
        {
        case 0:
            EnemyPos1X = RandomCol;
            EnemyPos1Y = RandomRow;
            break;
        case 1:
            EnemyPos2X = RandomCol;
            EnemyPos2Y = RandomRow;
            break;
        case 2:
            EnemyPos3X = RandomCol;
            EnemyPos3Y = RandomRow;
            break;
        case 3:
            EnemyPos4X = RandomCol;
            EnemyPos4Y = RandomRow;
            break;
        case 4:
            EnemyPos5X = RandomCol;
            EnemyPos5Y = RandomRow;
            break;
        case 5:
            EnemyPos6X = RandomCol;
            EnemyPos6Y = RandomRow;
        }
    }
}

void ethanShoot(char arr[][col_size], char direction)
{

    switch (direction)
    {
    case 'w': // Shooting upwards
    case 'W':
        map[ethanposY - 2][ethanposX] = '+';
        bulletPosX = ethanposX;
        bulletPosY = ethanposY - 2;
        isActive = true;
        break;

    case 's': // Shooting downwards
    case 'S':
        map[ethanposY + 2][ethanposX] = '+';
        bulletPosX = ethanposX;
        bulletPosY = ethanposY + 2;
        isActive = true;
        break;

    case 'a': // Shooting left
    case 'A':
        map[ethanposY][ethanposX - 2] = '+';
        bulletPosX = ethanposX - 2;
        bulletPosY = ethanposY;
        isActive = true;
        break;

    case 'd': // Shooting right
    case 'D':
        map[ethanposY][ethanposX + 2] = '+';
        bulletPosX = ethanposX + 2;
        bulletPosY = ethanposY;
        isActive = true;
        break;
    }
}

// collision check for solomon
bool solomonCollision(int posY, int posX)
{

    if ((collisionCheck(posY, posX)) && (collisionCheck(posY - 1, posX - 1)) && (collisionCheck(posY - 1, posX + 1)) && (collisionCheck(posY, posX - 1)) && (collisionCheck(posY, posX + 1)) && (collisionCheck(posY, posX - 3)) && (collisionCheck(posY, posX - 2)) && (collisionCheck(posY, posX + 3)) && (collisionCheck(posY, posX + 2)) && (collisionCheck(posY + 1, posX - 1)) && (collisionCheck(posY + 1, posX + 1)))
    {
        return false;
    }
    else
    {
        return true;
    }
}

// intialising solomon
void initialiseSolomon(char map[][col_size])
{
    int RandomRow, RandomCol;
    int startRow = 3, endRow = row_size / 2 - 2; // ensuring bounds
    int startCol = 4, endCol = col_size - 5;     // ensuring bounds
    srand(time(0));

    do
    {
        solomonPosX = RandomNumber(startCol, endCol);
        solomonPosY = RandomNumber(startRow, endRow);
    } while (solomonCollision(solomonPosY, solomonPosX));

    // solomon
    map[solomonPosY - 1][solomonPosX - 1] = '['; // Top bracket
    map[solomonPosY - 1][solomonPosX + 1] = ']'; // Top bracket (closing)
    map[solomonPosY][solomonPosX - 1] = '[';     // Left bracket
    map[solomonPosY][solomonPosX] = 'x';         // Center
    map[solomonPosY][solomonPosX + 1] = ']';     // Right bracket
    map[solomonPosY][solomonPosX - 3] = '[';
    map[solomonPosY][solomonPosX - 2] = ']';
    map[solomonPosY][solomonPosX + 3] = ']';
    map[solomonPosY][solomonPosX + 2] = '[';
    map[solomonPosY + 1][solomonPosX - 1] = '['; // Bottom bracket
    map[solomonPosY + 1][solomonPosX + 1] = ']'; // Bottom bracket (closing)
}

void ethan(char arr[][col_size])
{
    int rowstart = m, rowend = n;
    int colstart = 3, colend = col_size - 3;

    do
    {
        ethanposY = rowstart + rand() % (rowend - rowstart + 1);
        ethanposX = colstart + rand() % (colend - colstart + 1);
    } while (ethanCollision(ethanposY, ethanposX));
    for (int row = 0; row < row_size; row++)
    {
        for (int col = 0; col < col_size; col++)
        {
            arr[ethanposY][ethanposX] = '|';
            arr[ethanposY][ethanposX - 1] = '/';
            arr[ethanposY][ethanposX + 1] = '\\';
            arr[ethanposY - 1][ethanposX] = 'O';
            arr[ethanposY + 1][ethanposX - 1] = '/';
            arr[ethanposY + 1][ethanposX + 1] = '\\';
        }
    }
}

void initializeMap1(char map[][col_size])
{
    system("cls");
    for (int row = 0; row < row_size; row++)
    {
        for (int col = 0; col < col_size; col++)
        {
            map[row][col] = ' ';                 // removing all garbage values
            if (col == 0 || col == col_size - 1) // adding borders to columns
            {
                map[row][col] = '|';
            }
            else if (row == 0 || row == row_size - 1) // adding borders to rows
            {
                map[row][col] = '-';
            }
            int midCol = (col_size / 2) - 5;
            for (int col = midCol; col < midCol + 8; col++) // for adding doors on the top and bottom
            {
                if (row == 0 || row == row_size - 1)
                {
                    map[row][col] = ' ';
                }
            }
        }
    }
}

void initializeMap2(char map[][col_size])
{
    system("cls");
    for (int row = 0; row < row_size; row++)
    {
        for (int col = 0; col < col_size; col++)
        {
            map[row][col] = ' ';                 // removing all garbage values
            if (col == 0 || col == col_size - 1) // adding borders to columns
            {
                map[row][col] = '|';
            }
            else if (row == 0 || row == row_size - 1) // adding borders to rows
            {
                map[row][col] = '-';
            }
            int midRow = (row_size / 2) - 5;
            for (int row = midRow; row < midRow + 8; row++) // adding doors on the top and bottom
            {
                if (col == 0 || col == col_size - 1)
                {
                    map[row][col] = ' ';
                }
            }
        }
    }
}

void PrintMap()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0});
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < col_size; j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

// ethans movement
void move(char arr[][col_size], char &direction)
{
    switch (direction)
    {
    case KEY_UP:                                                                                                                                           // to move up
        if (ethanposY > 2 && arr[ethanposY - 2][ethanposX] == ' ' && arr[ethanposY - 1][ethanposX - 1] == ' ' && arr[ethanposY - 1][ethanposX + 1] == ' ') // // prevent out-of-bounds
        {
            arr[ethanposY][ethanposX] = ' '; // clearing current position
            arr[ethanposY][ethanposX - 1] = ' ';
            arr[ethanposY][ethanposX + 1] = ' ';
            arr[ethanposY - 1][ethanposX] = ' ';
            arr[ethanposY + 1][ethanposX - 1] = ' ';
            arr[ethanposY + 1][ethanposX + 1] = ' ';
            ethanposY--;                     // move one row up
            arr[ethanposY][ethanposX] = '|'; // ethan at the new position
            arr[ethanposY][ethanposX - 1] = '/';
            arr[ethanposY][ethanposX + 1] = '\\';
            arr[ethanposY - 1][ethanposX] = 'O';
            arr[ethanposY + 1][ethanposX - 1] = '/';
            arr[ethanposY + 1][ethanposX + 1] = '\\';
        }
        break;
    case KEY_DOWN:
        if (ethanposY < row_size - 3 && arr[ethanposY + 2][ethanposX + 1] == ' ' && arr[ethanposY + 2][ethanposX - 1] == ' ' && arr[ethanposY + 1][ethanposX] == ' ')
        {
            arr[ethanposY][ethanposX] = ' '; // clearing current position
            arr[ethanposY][ethanposX - 1] = ' ';
            arr[ethanposY][ethanposX + 1] = ' ';
            arr[ethanposY - 1][ethanposX] = ' ';
            arr[ethanposY + 1][ethanposX - 1] = ' ';
            arr[ethanposY + 1][ethanposX + 1] = ' ';
            ethanposY++;                     // move down one row
            arr[ethanposY][ethanposX] = '|'; // ethan at the new position
            arr[ethanposY][ethanposX - 1] = '/';
            arr[ethanposY][ethanposX + 1] = '\\';
            arr[ethanposY - 1][ethanposX] = 'O';
            arr[ethanposY + 1][ethanposX - 1] = '/';
            arr[ethanposY + 1][ethanposX + 1] = '\\';
        }
        break;
    case KEY_LEFT:
        if (ethanposX > 2 && arr[ethanposY][ethanposX - 2] == ' ' && arr[ethanposY + 1][ethanposX - 2] == ' ' && arr[ethanposY - 1][ethanposX - 1] == ' ')
        {
            arr[ethanposY][ethanposX] = ' '; // clearing current position
            arr[ethanposY][ethanposX - 1] = ' ';
            arr[ethanposY][ethanposX + 1] = ' ';
            arr[ethanposY - 1][ethanposX] = ' ';
            arr[ethanposY + 1][ethanposX - 1] = ' ';
            arr[ethanposY + 1][ethanposX + 1] = ' ';
            ethanposX--;                     // move left one column
            arr[ethanposY][ethanposX] = '|'; // ethan at the new position
            arr[ethanposY][ethanposX - 1] = '/';
            arr[ethanposY][ethanposX + 1] = '\\';
            arr[ethanposY - 1][ethanposX] = 'O';
            arr[ethanposY + 1][ethanposX - 1] = '/';
            arr[ethanposY + 1][ethanposX + 1] = '\\';
        }
        break;
    case KEY_RIGHT:
        if (ethanposX < col_size - 3 && arr[ethanposY][ethanposX + 2] == ' ' && arr[ethanposY + 1][ethanposX + 2] == ' ' && arr[ethanposY - 1][ethanposX + 1] == ' ')
        {
            arr[ethanposY][ethanposX] = ' '; // clearing current position
            arr[ethanposY][ethanposX - 1] = ' ';
            arr[ethanposY][ethanposX + 1] = ' ';
            arr[ethanposY - 1][ethanposX] = ' ';
            arr[ethanposY + 1][ethanposX - 1] = ' ';
            arr[ethanposY + 1][ethanposX + 1] = ' ';
            ethanposX++;                     // move right one column
            arr[ethanposY][ethanposX] = '|'; // ethan at the new position
            arr[ethanposY][ethanposX - 1] = '/';
            arr[ethanposY][ethanposX + 1] = '\\';
            arr[ethanposY - 1][ethanposX] = 'O';
            arr[ethanposY + 1][ethanposX - 1] = '/';
            arr[ethanposY + 1][ethanposX + 1] = '\\';
        }
        break;
    case ESCAPE:
        isNotOver = false;
        break;
    default:
        // cout << "Invalid key. Use ARROW keys to move or 'Q' to quit." << endl;
        break;
    }
}

void level1Obstacles(char arr[][col_size])
{
    int rowstart = 3, rowend = row_size - 3;
    int colstart = 3, colend = col_size - 4;
    for (int obstaclecount = 1; obstaclecount <= 2; obstaclecount++) // Spawn 2 obstacles
    {
        do
        {
            obstacleX = rowstart + rand() % (rowend - rowstart + 1);
            obstacleY = colstart + rand() % (colend - colstart + 1);

        } while (arr[obstacleX][obstacleY] != ' ' || arr[obstacleX][obstacleY + 1] != ' ' || arr[obstacleX][obstacleY + 2] != ' '); // Check if spaces are free for obstacles
        arr[obstacleX][obstacleY] = '['; // Place obstacle after ensuring no overlap
        arr[obstacleX][obstacleY + 1] = '-';
        arr[obstacleX][obstacleY + 2] = ']';
    }
}
void level2Obstacles(char arr[][col_size])
{
    int rowstart = 3, rowend = row_size - 3;
    int colstart = 3, colend = col_size - 4;
    for (int obstaclecount = 1; obstaclecount <= 3; obstaclecount++) // Spawn 3 obstacles
    {
        do
        {
            obstacleX = rowstart + rand() % (rowend - rowstart + 1);
            obstacleY = colstart + rand() % (colend - colstart + 1);

        } while (arr[obstacleX][obstacleY] != ' ' || arr[obstacleX][obstacleY + 1] != ' ' || arr[obstacleX][obstacleY + 2] != ' '); // Check if spaces are free for obstacles
        arr[obstacleX][obstacleY] = '['; // Place obstacle after ensuring no overlap
        arr[obstacleX][obstacleY + 1] = '-';
        arr[obstacleX][obstacleY + 2] = ']';
    }
}
void level3Obstacles(char arr[][col_size])
{

    int rowstart = 3, rowend = row_size - 3;
    int colstart = 3, colend = col_size - 4;
    for (int obstaclecount = 1; obstaclecount <= 3; obstaclecount++) // Spawn 3 obstacles
    {
        do
        {
            obstacleX = rowstart + rand() % (rowend - rowstart + 1);
            obstacleY = colstart + rand() % (colend - colstart + 1);

        } while (arr[obstacleX][obstacleY] != ' ' || arr[obstacleX][obstacleY + 1] != ' ' || arr[obstacleX][obstacleY + 2] != ' ' || arr[obstacleX][obstacleY + 3] != ' '); // Check if spaces are free for obstacles
        arr[obstacleX][obstacleY] = '['; // Place obstacle after ensuring no overlap
        arr[obstacleX][obstacleY + 1] = '-';
        arr[obstacleX][obstacleY + 2] = '-';
        arr[obstacleX][obstacleY + 3] = ']';
    }
}
void level4Obstacles(char arr[][col_size])
{
    int rowstart = 3, rowend = row_size - 3;
    int colstart = 3, colend = col_size - 4;
    for (int obstaclecount = 1; obstaclecount <= 4; obstaclecount++) // Spawn 4 obstacles
    {
        do
        {
            obstacleX = rowstart + rand() % (rowend - rowstart + 1);
            obstacleY = colstart + rand() % (colend - colstart + 1);

        } while (arr[obstacleX][obstacleY] != ' ' || arr[obstacleX][obstacleY + 1] != ' ' || arr[obstacleX][obstacleY + 2] != ' ' || arr[obstacleX][obstacleY + 3] != ' '); // Check if spaces are free for obstacles
        arr[obstacleX][obstacleY] = '['; // Place obstacle after ensuring no overlap
        arr[obstacleX][obstacleY + 1] = '-';
        arr[obstacleX][obstacleY + 2] = '-';
        arr[obstacleX][obstacleY + 3] = ']';
    }
}
void level5Obstacles(char arr[][col_size])
{
    int rowstart = 3, rowend = row_size - 3;
    int colstart = 7, colend = col_size - 7;
    for (int obstaclecount = 1; obstaclecount <= 4; obstaclecount++) // Spawn 4 obstacles
    {
        do
        {
            obstacleX = rowstart + rand() % (rowend - rowstart + 1);
            obstacleY = colstart + rand() % (colend - colstart + 1);

        } while (arr[obstacleX][obstacleY] != ' ' || arr[obstacleX][obstacleY + 1] != ' ' || arr[obstacleX][obstacleY + 2] != ' ' || arr[obstacleX][obstacleY + 3] != ' ' || arr[obstacleX][obstacleY + 4] != ' ');
        ;                                // Check if spaces are free for obstacles
        arr[obstacleX][obstacleY] = '['; // Place obstacle after ensuring no overlap
        arr[obstacleX][obstacleY + 1] = '-';
        arr[obstacleX][obstacleY + 2] = '-';
        arr[obstacleX][obstacleY + 3] = '-';
        arr[obstacleX][obstacleY + 4] = ']';
    }
}

int RandomMap()
{
    srand(time(0));
    int r[2] = {1, 2};
    int l = rand() % (2);
    int Random = r[l];
    return Random;
}

int RandomNumber(int start, int end)
{
    int Random = start + rand() % (end - start + 1);
    return Random;
}

bool collisionCheck(int row, int col)
{
    if (map[row][col] == ' ')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool enemyCollision(int PosY, int PosX)
{
    if ((collisionCheck(PosY, PosX)) && (collisionCheck(PosY, PosX - 1)) && (collisionCheck(PosY, PosX + 1)) && (collisionCheck(PosY - 1, PosX - 1)) && (collisionCheck(PosY - 1, PosX + 1)) && (collisionCheck(PosY - 1, PosX)))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void updatingSolomonPos(int PosY, int PosX)
{
    if ((enemySpeed % 2 == 0) || ((solomonCollision(PosY, PosX)) && (PosX >= col_size - 26 && PosX <= col_size - 5) && (PosY >= row_size - 48 && PosY <= row_size - 3)))
    {
        int direction = randomDirection();
        int X = PosX, Y = PosY;

        map[PosY - 1][PosX - 1] = ' '; // Top bracket
        map[PosY - 1][PosX + 1] = ' '; // Top bracket (closing)
        map[PosY][PosX - 1] = ' ';     // Left bracket
        map[PosY][PosX] = ' ';         // Center
        map[PosY][PosX + 1] = ' ';     // Right bracket
        map[PosY][PosX - 3] = ' ';
        map[PosY][PosX - 2] = ' ';
        map[PosY][PosX + 3] = ' ';
        map[PosY][PosX + 2] = ' ';
        map[PosY + 1][PosX - 1] = ' '; // Bottom bracket
        map[PosY + 1][PosX + 1] = ' '; // Bottom bracket (closing)
        switch (direction)
        {
        case 1: // up
            PosY--;
            break;
        case 2: // down
            PosY++;
            break;
        case 3: // left
            PosX--;
            break;
        case 4: // right
            PosX++;
            break;
        }
        if ((!(solomonCollision(PosY, PosX)) && (PosX >= col_size - 26 && PosX <= col_size - 5) && (PosY >= row_size - 48 && PosY <= row_size - 3)))
        {

            solomonPosY = PosY;
            solomonPosX = PosX;

            map[PosY - 1][PosX - 1] = '['; // Top bracket
            map[PosY - 1][PosX + 1] = ']'; // Top bracket (closing)
            map[PosY][PosX - 1] = '[';     // Left bracket
            map[PosY][PosX] = 'x';         // Center
            map[PosY][PosX + 1] = ']';     // Right bracket
            map[PosY][PosX - 3] = '[';
            map[PosY][PosX - 2] = ']';
            map[PosY][PosX + 3] = ']';
            map[PosY][PosX + 2] = '[';
            map[PosY + 1][PosX - 1] = '['; // Bottom bracket
            map[PosY + 1][PosX + 1] = ']'; // Bottom bracket (closing)
        }
        else
        {
            map[Y - 1][X - 1] = '['; // Top bracket
            map[Y - 1][X + 1] = ']'; // Top bracket (closing)
            map[Y][X - 1] = '[';     // Left bracket
            map[Y][X] = 'x';         // Center
            map[Y][X + 1] = ']';     // Right bracket
            map[Y][X - 3] = '[';
            map[Y][X - 2] = ']';
            map[Y][X + 3] = ']';
            map[Y][X + 2] = '[';
            map[Y + 1][X - 1] = '['; // Bottom bracket
            map[Y + 1][X + 1] = ']'; // Bottom bracket (closing)
        }
    }
}

int randomDirection()
{
    int d[4] = {1, 2, 3, 4};
    srand(time(0));
    int random = rand() % 4;
    return d[random];
}

void trackingEthan(int level)
{
    // if (enemySpeed % 3 == 0) {
    updatingSolomonPos(solomonPosY, solomonPosX);
    //}

    if (enemySpeed % 4 == 0)
    {
        for (int i = 0; i <= level; i++)
        {
            switch (i)
            {
            case 0:
                updatingEnemyPos(EnemyPos1Y, EnemyPos1X, 1);
                break;
            case 1:
                updatingEnemyPos(EnemyPos2Y, EnemyPos2X, 2);
                break;
            case 2:
                updatingEnemyPos(EnemyPos3Y, EnemyPos3X, 3);
                break;
            case 3:
                updatingEnemyPos(EnemyPos4Y, EnemyPos4X, 4);
                break;
            case 4:
                updatingEnemyPos(EnemyPos5Y, EnemyPos5X, 5);
                break;
            case 5:
                updatingEnemyPos(EnemyPos6Y, EnemyPos6X, 6);
            }
        }
    }
}

void updatingEnemyPos(int EnemyPosY, int EnemyPosX, int enemyNumber)
{
    int x = EnemyPosX, y = EnemyPosY;
    if (x != 0 && y != 0)
    {
        map[y][x - 1] = ' ';
        map[y][x] = ' ';
        map[y][x + 1] = ' ';

        map[y - 1][x - 1] = ' ';
        map[y - 1][x] = ' ';
        map[y - 1][x + 1] = ' ';

        if (EnemyPosX > ethanposX)
        {
            EnemyPosX--;
        }
        else if (EnemyPosX < ethanposX)
        {
            EnemyPosX++;
        }
        if (EnemyPosY > ethanposY)
        {
            EnemyPosY--;
        }
        else if (EnemyPosY < ethanposY)
        {
            EnemyPosY++;
        }
        if (!(enemyCollision(EnemyPosY, EnemyPosX)))
        {

            map[EnemyPosY][EnemyPosX - 1] = '[';
            map[EnemyPosY][EnemyPosX] = 'V';
            map[EnemyPosY][EnemyPosX + 1] = ']';

            map[EnemyPosY - 1][EnemyPosX - 1] = '[';
            map[EnemyPosY - 1][EnemyPosX] = '|';
            map[EnemyPosY - 1][EnemyPosX + 1] = ']';

            switch (enemyNumber)
            {
            case 1:
                EnemyPos1X = EnemyPosX;
                EnemyPos1Y = EnemyPosY;
                enemyShoot(EnemyPosY, EnemyPosX, 1);
                break;
            case 2:
                EnemyPos2X = EnemyPosX;
                EnemyPos2Y = EnemyPosY;
                enemyShoot(EnemyPosY, EnemyPosX, 2);
                break;
            case 3:
                EnemyPos3X = EnemyPosX;
                EnemyPos3Y = EnemyPosY;
                enemyShoot(EnemyPosY, EnemyPosX, 3);
                break;
            case 4:
                EnemyPos4X = EnemyPosX;
                EnemyPos4Y = EnemyPosY;
                enemyShoot(EnemyPosY, EnemyPosX, 4);
                break;
            case 5:
                EnemyPos5X = EnemyPosX;
                EnemyPos5Y = EnemyPosY;
                enemyShoot(EnemyPosY, EnemyPosX, 5);
                break;
            case 6:
                EnemyPos6X = EnemyPosX;
                EnemyPos6Y = EnemyPosY;
                enemyShoot(EnemyPosY, EnemyPosX, 6);
                break;
            }
        }
        else
        {
            map[y][x - 1] = '[';
            map[y][x] = 'V';
            map[y][x + 1] = ']';

            map[y - 1][x - 1] = '[';
            map[y - 1][x] = '|';
            map[y - 1][x + 1] = ']';
        }
    }
}

void initializeRandomMap()
{
    int Random = RandomMap();
    if (Random == 1)
    {
        initializeMap1(map);
    }
    else if (Random == 2)
    {
        initializeMap2(map);
    }
}

bool ethanCollision(int PosY, int PosX)
{
    if ((collisionCheck(PosY, PosX)) && (collisionCheck(PosY - 1, PosX)) && (collisionCheck(PosY, PosX - 1)) && (collisionCheck(PosY, PosX + 1)) && (collisionCheck(PosY, PosX - 1)) && (collisionCheck(PosY + 1, PosX - 1)) && (collisionCheck(PosY + 1, PosX + 1)))
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Prints the title screen with the game's name
// no parameter values
// no return value

void displayTitle()
{
    setColor(0x05);
    cout << R"(
  _______ _________ _______  _______ _________ _______  _            _________ _______  _______  _______  _______  _______ _________ ______   _        _______ 
 (       )\__   __/(  ____ \(  ____ \\__   __/(  ___  )( (    /|     \__   __/(       )(  ____ )(  ___  )(  ____ \(  ____ \\__   __/(  ___ \ ( \      (  ____ \
 | () () |   ) (   | (    \/| (    \/   ) (   | (   ) ||  \  ( | _      ) (   | () () || (    )|| (   ) || (    \/| (    \/   ) (   | (   ) )| (      | (    \/
 | || || |   | |   | (_____ | (_____    | |   | |   | ||   \ | |(_)     | |   | || || || (____)|| |   | || (_____ | (_____    | |   | (__/ / | |      | (__    
 | |(_)| |   | |   (_____  )(_____  )   | |   | |   | || (\ \) |        | |   | |(_)| ||  _____)| |   | |(_____  )(_____  )   | |   |  __ (  | |      |  __)   
 | |   | |   | |         ) |      ) |   | |   | |   | || | \   | _      | |   | |   | || (      | |   | |      ) |      ) |   | |   | (  \ \ | |      | (      
 | )   ( |___) (___/\____) |/\____) |___) (___| (___) || )  \  |(_)  ___) (___| )   ( || )      | (___) |/\____) |/\____) |___) (___| )___) )| (____/\| (____/\
 |/     \|\_______/\_______)\_______)\_______/(_______)|/    )_)     \_______/|/     \||/       (_______)\_______)\_______)\_______/|/ \___/ (_______/(_______/
 )";

    setColor(0x0F);
    cout << "Press any key to continue to the main menu... ";
    setColor(0x07);
    _getch();
}

// prints the help menu
// no return value, no parameters
void displayHelp()
{
    system("cls");

    setColor(0x03); // This is how the following text's colour is set. Sets text colour to aqua
    cout << "Here is some information for the game :\n"
         << endl;
    cout << "1. Use the \"UP\" key to move up and the \"DOWN\" key to move down.\n"
         << endl;
    cout << "2. Use \"spacebar\" to fire the plasma cannon.\n"
         << endl;
    cout << "3. \"+\" denotes the unbreakable walls and \"0\" denotes the asteroid.\n"
         << endl;
    cout << "4. You have three hearts in total. \"Head-on collision\" OR \"Side-on collision\" with either walls will cost you one heart. \n"
         << endl;
    cout << "5. You will receive \"1000\" points if you destroy one asteroid.\n"
         << endl;
    cout << "6. Choose your difficulty wisely. Enjoy playing! :)\n"
         << endl;
    setColor(0x07); // Resets text colour

    setColor(0x0F); // Sets text colour to brilliant white
    cout << "Press any key to return to main menu . . . ";
    setColor(0x07);

    _getch();
}

/*
Displays the menu of the game.
No return value.
*/
void displayMenu()
{
    int keyhit = 0;
    int choice = 1;

    while (1)
    {
        system("cls");
        switch (choice)
        {
            // inversion of order is due to order of numbering being diff from order
        case 1:
        {
            setColor(0x04);
            cout << R"(
    _____   _                    _        _____                            
   / ____| | |                  | |      / ____|                           
  | (___   | |_    __ _   _ __  | |_    | |  __    __ _   _ __ ___     ___ 
   \___ \  | __|  / _` | | '__| | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
   ____) | | |_  | (_| | | |    | |_    | |__| | | (_| | | | | | | | |  __/
  |_____/   \__|  \__,_| |_|     \__|    \_____|  \__,_| |_| |_| |_|  \___|


 )" << endl;
            setColor(0x07);
            cout << R"(
   _    _          _         
  | |  | |        | |        
  | |__| |   ___  | |  _ __  
  |  __  |  / _ \ | | | '_ \ 
  | |  | | |  __/ | | | |_) |
  |_|  |_|  \___| |_| | .__/ 
                      | |    
                      |_|    
 )" << endl;
            cout << R"(
   ______          _   _        _____                            
  |  ____|        (_) | |      / ____|                           
  | |__    __  __  _  | |_    | |  __    __ _   _ __ ___     ___ 
  |  __|   \ \/ / | | | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
  | |____   >  <  | | | |_    | |__| | | (_| | | | | | | | |  __/
  |______| /_/\_\ |_|  \__|    \_____|  \__,_| |_| |_| |_|  \___|
 )" << endl;
            setColor(0x0F);
            cout << "Navigate using the up and down arrow keys. Press the enter key to select an option . . . ";
            setColor(0x07);
        }
        break;

        case 2:
        {
            cout << R"(
    _____   _                    _        _____                            
   / ____| | |                  | |      / ____|                           
  | (___   | |_    __ _   _ __  | |_    | |  __    __ _   _ __ ___     ___ 
   \___ \  | __|  / _` | | '__| | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
   ____) | | |_  | (_| | | |    | |_    | |__| | | (_| | | | | | | | |  __/
  |_____/   \__|  \__,_| |_|     \__|    \_____|  \__,_| |_| |_| |_|  \___|


 )" << endl;

            setColor(0x0E);
            cout << R"(
   _    _          _         
  | |  | |        | |        
  | |__| |   ___  | |  _ __  
  |  __  |  / _ \ | | | '_ \ 
  | |  | | |  __/ | | | |_) |
  |_|  |_|  \___| |_| | .__/ 
                      | |    
                      |_|    
 )" << endl;
            setColor(0x07);
            cout << R"(
   ______          _   _        _____                            
  |  ____|        (_) | |      / ____|                           
  | |__    __  __  _  | |_    | |  __    __ _   _ __ ___     ___ 
  |  __|   \ \/ / | | | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
  | |____   >  <  | | | |_    | |__| | | (_| | | | | | | | |  __/
  |______| /_/\_\ |_|  \__|    \_____|  \__,_| |_| |_| |_|  \___|
 )" << endl;
            setColor(0x0F);
            cout << "Navigate using the up and down arrow keys. Press the enter key to select an option . . . ";
            setColor(0x07);
        }
        break;
        case 3:
        {
            cout << R"(
    _____   _                    _        _____                            
   / ____| | |                  | |      / ____|                           
  | (___   | |_    __ _   _ __  | |_    | |  __    __ _   _ __ ___     ___ 
   \___ \  | __|  / _` | | '__| | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
   ____) | | |_  | (_| | | |    | |_    | |__| | | (_| | | | | | | | |  __/
  |_____/   \__|  \__,_| |_|     \__|    \_____|  \__,_| |_| |_| |_|  \___|


 )" << endl;
            cout << R"(
   _    _          _         
  | |  | |        | |        
  | |__| |   ___  | |  _ __  
  |  __  |  / _ \ | | | '_ \ 
  | |  | | |  __/ | | | |_) |
  |_|  |_|  \___| |_| | .__/ 
                      | |    
                      |_|    
 )" << endl;
            setColor(0x09);
            cout << R"(
   ______          _   _        _____                            
  |  ____|        (_) | |      / ____|                           
  | |__    __  __  _  | |_    | |  __    __ _   _ __ ___     ___ 
  |  __|   \ \/ / | | | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
  | |____   >  <  | | | |_    | |__| | | (_| | | | | | | | |  __/
  |______| /_/\_\ |_|  \__|    \_____|  \__,_| |_| |_| |_|  \___|
 )" << endl;
            setColor(0x07);
            ;
            setColor(0x0F);
            ;
            cout << "Navigate using the up and down arrow keys. Press the enter key to select an option . . . ";
            setColor(0x07);
        }
        }

        keyhit = _getch();

        if ((keyhit == KEY_DOWN) && (choice < 3)) // to validate any change upon pressing the down key when in main menu
        {
            choice++;
        }
        if ((keyhit == KEY_UP) && (choice > 1)) // to validate any change upon pressing the up key when in main menu
        {
            choice--;
        }
        if (keyhit == ENTER)
        {
            switch (choice)
            {
            case 1:
            {
                return;
            }
            break;

            case 2:
            {
                displayHelp();
            }
            break;
            case 3:
            {
                exit(0);
            }
            }
        }
    }
}

/*
Displays the game-over screen and print the final score
@param s represents the final score
no return value
*/
void gameOver()
{
    int keyhit = 0;

    system("cls");
    setColor(0x0A);
    cout << R"(
 _______  _______  _______  _______    _______           _______  _______ 
(  ____ \(  ___  )(       )(  ____ \  (  ___  )|\     /|(  ____ \(  ____ )
| (    \/| (   ) || () () || (    \/  | (   ) || )   ( || (    \/| (    )|
| |      | (___) || || || || (__      | |   | || |   | || (__    | (____)|
| | ____ |  ___  || |(_)| ||  __)     | |   | |( (   ) )|  __)   |     __)
| | \_  )| (   ) || |   | || (        | |   | | \ \_/ / | (      | (\ (   
| (___) || )   ( || )   ( || (____/\  | (___) |  \   /  | (____/\| ) \ \__
(_______)|/     \||/     \|(_______/  (_______)   \_/   (_______/|/   \__/
                                                                          
)" << endl;
    setColor(0xF);
    // cout << "YOUR SCORE IS: " << score << endl << endl;
    setColor(07);
    Sleep(1000);

    while (_kbhit())

        _getch();

    cout << "Press escape to exit, press any key to play again . . . ";

    keyhit = _getch();
    system("cls");
    if (keyhit == ESCAPE)
    {
        exit(0);
    }
    else
    {
        return;
    }
}

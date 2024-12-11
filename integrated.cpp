//Project Details

//Group Members:
  // Zain Tariq         (24F-0558)
  // Sania Basharat     (24F-0546)
  // Ammar Nadeem       (24F-0733)  
  

#include <iostream>
//#include <Windows.h> //for CLS
#include <stdlib.h>  //for coloured output
#include <conio.h>  //to take input from keyboard
#include <ctime>    // to get the current time in seconds for randomisation
#include <chrono>  //to get the current time in milliseconds for randomisation of real-time processes

using namespace std;

// Global variables
const int row_size = 50, col_size = 30;
char map[row_size][col_size];
int x = 0, y = 0; //ethan's torsos x,y coordinates
int obstacleX = 0, obstacleY = 0; // obstacles x and y coordinates
int m = (row_size / 2) + 2, n = row_size - 3; // m = starting point, n = end point for random function
int EnemyPos1X, EnemyPos2X, EnemyPos3X, EnemyPos4X, EnemyPos5X, EnemyPos6X;     //ask sir if srand can produce the same number
int EnemyPos1Y, EnemyPos2Y, EnemyPos3Y, EnemyPos4Y, EnemyPos5Y, EnemyPos6Y;
int ethanposX = col_size / 2 - 2, ethanposY = row_size - 4;
const int ENTER = 13 ;
const int KEY_DOWN = 80 ;
const int KEY_UP = 72 ;
const int SPACEBAR = 32 ;
const int ESCAPE = 27 ;


// Function prototypes
// void displayTitle();
// void displayHelp();
// void displayMenu();
void initializeMap1(char map[][col_size]);
void initializeMap2(char map[][col_size]);
void initializeRandomMap();
void initializeEnemies(char map[][col_size], int level);
void ethan(char arr[][col_size]); // for ethan hunt  
void move(char arr[][col_size], char& direction); // to move ethan
void level1Obstacles(char arr[][col_size]);
void level2Obstacles(char arr[][col_size]);
void level3Obstacles(char arr[][col_size]);
void level4Obstacles(char arr[][col_size]);
void level5Obstacles(char arr[][col_size]);
void PrintMap();
int RandomMap();
int RandomNumber(int start, int end);
bool collisionCheck(int row, int col);
void trackingEthan(int level);
void updatingEnemyPos(int EnemyPosX, int EnemyPosY, int enemyNumber);
bool enemyCollision(int PosY,int PosX);

int main(){
    int level = 1;
    initializeRandomMap();
    // displayTitle();                 //Called to display the title of the game
    // displayMenu();                  //Called to display the menu
    initializeEnemies(map, level);
    PrintMap();
}

//Prints the title screen with the game's name
//no parameter values
//no return value

//void displayTitle()
// {
//     SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x05 ); 
//     cout << R"(
//  _______ _________ _______  _______ _________ _______  _            _________ _______  _______  _______  _______  _______ _________ ______   _        _______ 
// (       )\__   __/(  ____ \(  ____ \\__   __/(  ___  )( (    /|     \__   __/(       )(  ____ )(  ___  )(  ____ \(  ____ \\__   __/(  ___ \ ( \      (  ____ \
// | () () |   ) (   | (    \/| (    \/   ) (   | (   ) ||  \  ( | _      ) (   | () () || (    )|| (   ) || (    \/| (    \/   ) (   | (   ) )| (      | (    \/
// | || || |   | |   | (_____ | (_____    | |   | |   | ||   \ | |(_)     | |   | || || || (____)|| |   | || (_____ | (_____    | |   | (__/ / | |      | (__    
// | |(_)| |   | |   (_____  )(_____  )   | |   | |   | || (\ \) |        | |   | |(_)| ||  _____)| |   | |(_____  )(_____  )   | |   |  __ (  | |      |  __)   
// | |   | |   | |         ) |      ) |   | |   | |   | || | \   | _      | |   | |   | || (      | |   | |      ) |      ) |   | |   | (  \ \ | |      | (      
// | )   ( |___) (___/\____) |/\____) |___) (___| (___) || )  \  |(_)  ___) (___| )   ( || )      | (___) |/\____) |/\____) |___) (___| )___) )| (____/\| (____/\
// |/     \|\_______/\_______)\_______)\_______/(_______)|/    )_)     \_______/|/     \||/       (_______)\_______)\_______)\_______/|/ \___/ (_______/(_______/
// )";

// SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0F ) ;
// cout << "Press any key to continue to the main menu... " ;
// SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 ) ;
// getch() ;

// }

//prints the help menu
//no return value, no parameters
//void displayHelp() {
//     system("cls") ;

//     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03); // This is how the following text's colour is set. Sets text colour to aqua
//     cout <<"Here is some information for the game :\n" << endl ;
//     cout <<"1. Use the \"UP\" key to move up and the \"DOWN\" key to move down.\n" << endl ;
//     cout <<"2. Use \"spacebar\" to fire the plasma cannon.\n" << endl ;
//     cout <<"3. \"+\" denotes the unbreakable walls and \"0\" denotes the asteroid.\n" << endl ;
//     cout <<"4. You have three hearts in total. \"Head-on collision\" OR \"Side-on collision\" with either walls will cost you one heart. \n" << endl ;
//     cout <<"5. You will receive \"1000\" points if you destroy one asteroid.\n" << endl ;
//     cout <<"6. Choose your difficulty wisely. Enjoy playing! :)\n" << endl ;
//     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07); // Resets text colour

//     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F); // Sets text colour to brilliant white
//     cout << "Press any key to return to main menu . . . " ; 
//     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07); // Resets text colour 

//     getch();
// }

/*
Displays the menu of the game.
No return value.
*/
// void displayMenu()
// {
//     int keyhit = 0 ;
//     int choice = 1 ;

//     while(1)
//     {
//         system("cls") ;
//         switch(choice)
//         {
//             // inversion of order is due to order of numbering being diff from order
//             case 1 : 
//             {
//                 SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x04) ; cout << R"(
//    _____   _                    _        _____                            
//   / ____| | |                  | |      / ____|                           
//  | (___   | |_    __ _   _ __  | |_    | |  __    __ _   _ __ ___     ___ 
//   \___ \  | __|  / _` | | '__| | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
//   ____) | | |_  | (_| | | |    | |_    | |__| | | (_| | | | | | | | |  __/
//  |_____/   \__|  \__,_| |_|     \__|    \_____|  \__,_| |_| |_| |_|  \___|
                                                                          
                                                                          
// )" << endl ; SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07) ;

// cout << R"(
//   _    _          _         
//  | |  | |        | |        
//  | |__| |   ___  | |  _ __  
//  |  __  |  / _ \ | | | '_ \ 
//  | |  | | |  __/ | | | |_) |
//  |_|  |_|  \___| |_| | .__/ 
//                      | |    
//                      |_|    
// )" << endl ; 
//                 cout << R"(
//   ______          _   _        _____                            
//  |  ____|        (_) | |      / ____|                           
//  | |__    __  __  _  | |_    | |  __    __ _   _ __ ___     ___ 
//  |  __|   \ \/ / | | | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
//  | |____   >  <  | | | |_    | |__| | | (_| | | | | | | | |  __/
//  |______| /_/\_\ |_|  \__|    \_____|  \__,_| |_| |_| |_|  \___|
// )" << endl ; 
//             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
//             cout << "Navigate using the up and down arrow keys. Press the enter key to select an option . . . " ; 
//             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
//             }
//             break ;

//             case 2 : 
//             {
//                 cout << R"(
//    _____   _                    _        _____                            
//   / ____| | |                  | |      / ____|                           
//  | (___   | |_    __ _   _ __  | |_    | |  __    __ _   _ __ ___     ___ 
//   \___ \  | __|  / _` | | '__| | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
//   ____) | | |_  | (_| | | |    | |_    | |__| | | (_| | | | | | | | |  __/
//  |_____/   \__|  \__,_| |_|     \__|    \_____|  \__,_| |_| |_| |_|  \___|
                                                                          
                                                                          
// )" << endl ;

// SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0E) ; 
// cout << R"(
//   _    _          _         
//  | |  | |        | |        
//  | |__| |   ___  | |  _ __  
//  |  __  |  / _ \ | | | '_ \ 
//  | |  | | |  __/ | | | |_) |
//  |_|  |_|  \___| |_| | .__/ 
//                      | |    
//                      |_|    
// )" << endl ; SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 ) ; cout << R"(
//   ______          _   _        _____                            
//  |  ____|        (_) | |      / ____|                           
//  | |__    __  __  _  | |_    | |  __    __ _   _ __ ___     ___ 
//  |  __|   \ \/ / | | | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
//  | |____   >  <  | | | |_    | |__| | | (_| | | | | | | | |  __/
//  |______| /_/\_\ |_|  \__|    \_____|  \__,_| |_| |_| |_|  \___|
// )" << endl; 
//             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
//             cout << "Navigate using the up and down arrow keys. Press the enter key to select an option . . . " ; 
//             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
//             }
//             break ;
//             case 3 : 
//             {
//                 cout << R"(
//    _____   _                    _        _____                            
//   / ____| | |                  | |      / ____|                           
//  | (___   | |_    __ _   _ __  | |_    | |  __    __ _   _ __ ___     ___ 
//   \___ \  | __|  / _` | | '__| | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
//   ____) | | |_  | (_| | | |    | |_    | |__| | | (_| | | | | | | | |  __/
//  |_____/   \__|  \__,_| |_|     \__|    \_____|  \__,_| |_| |_| |_|  \___|
                                                                          
                                                                          
// )" << endl ; 
// cout << R"(
//   _    _          _         
//  | |  | |        | |        
//  | |__| |   ___  | |  _ __  
//  |  __  |  / _ \ | | | '_ \ 
//  | |  | | |  __/ | | | |_) |
//  |_|  |_|  \___| |_| | .__/ 
//                      | |    
//                      |_|    
// )" << endl ;
//  SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x09) ;
//                 cout << R"(
//   ______          _   _        _____                            
//  |  ____|        (_) | |      / ____|                           
//  | |__    __  __  _  | |_    | |  __    __ _   _ __ ___     ___ 
//  |  __|   \ \/ / | | | __|   | | |_ |  / _` | | '_ ` _ \   / _ \
//  | |____   >  <  | | | |_    | |__| | | (_| | | | | | | | |  __/
//  |______| /_/\_\ |_|  \__|    \_____|  \__,_| |_| |_| |_|  \___|
// )" << endl ; SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07) ;
//             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
//             cout << "Navigate using the up and down arrow keys. Press the enter key to select an option . . . " ; 
//             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
//             }
//         }
                        

//         keyhit = getch() ;

//         if ((keyhit == KEY_DOWN) && (choice < 3) ) // to validate any change upon pressing the down key when in main menu
//         {
//             choice++ ;
//         }
//         if ((keyhit == KEY_UP) && (choice > 1) ) // to validate any change upon pressing the up key when in main menu
//         {   
//             choice-- ;
//         }
//         if (keyhit == ENTER)
//         {
//             switch(choice) 
//             {
//                 case 1 : 
//                 {
//                     return ;
//                 }
//                 break ;

//                 case 2 : 
//                 {
//                     displayHelp() ;
//                 }
//                 break ;
//                 case 3 : 
//                 {
//                     exit(0) ;
//                 }
//             }
//         }
//     }

// }

void ethan(char arr[][col_size])
{
	int rowstart = m, rowend = n;
	int colstart = 3, colend = col_size - 3;
	
	x = rowstart + rand() % (rowend - rowstart + 1);
	y = colstart + rand() % (colend - colstart + 1);
	for (int row = 0; row < row_size; row++)
	{
		for (int col = 0; col < col_size; col++)
		{
			arr[x][y] = '|';
			arr[x][y - 1] = '/';
			arr[x][y + 1] = '\\';
			arr[x - 1][y] = 'O';
			arr[x + 1][y - 1] = '/';
			arr[x + 1][y + 1] = '\\';
		}
	}
}




void initializeMap1(char map[][col_size]){
    // Removing all garbage values
    for (int i = 0; i < row_size;i++){
        for (int j = 0; j < col_size;j++){
            map[i][j] = ' ';
        }
    }
    //Adding border to columns
    for (int j = 0; j < col_size;j++){
        map[0][j] = '-';
        map[row_size - 1][j] = '-';
    }
    //Adding border to rows
    for (int j = 0; j < row_size;j++){
        map[j][0] = '|';
        map[j][col_size - 1] = '|';
    }
    // Adding doors on the top and bottom
    int midCol = (col_size / 2) - 5;
    for (int j = midCol; j < midCol + 8;j++){
        map[0][j] = ' ';
        map[row_size - 1][j] = ' ';
    }
}

void initializeMap2(char map[][col_size]){
     // Removing all garbage values
    for (int i = 0; i < row_size;i++){
        for (int j = 0; j < col_size;j++){
            map[i][j] = ' ';
        }
    }
    //Adding border to columns
    for (int j = 0; j < col_size;j++){
        map[0][j] = '-';
        map[row_size - 1][j] = '-';
    }
    //Adding border to rows
    for (int j = 0; j < row_size;j++){
        map[j][0] = '|';
        map[j][col_size - 1] = '|';
    }
    // Adding doors on the ledt and right
    int midRow = (row_size / 2) - 5;
    for (int j = midRow; j < midRow + 8;j++){
        map[j][0] = ' ';
        map[j][col_size - 1] = ' ';
    }
}

void move(char arr[][col_size], char& direction)
{
	switch (direction)
	{
	case 'w': // to move up
		if (x > 2) // // prevent out-of-bounds
		{
			arr[x][y] = ' '; // clearing current position
			arr[x][y - 1] = ' ';
			arr[x][y + 1] = ' ';
			arr[x - 1][y] = ' ';
			arr[x + 1][y - 1] = ' ';
			arr[x + 1][y + 1] = ' ';
			x--; // move one row up 
			arr[x][y] = '|';  // ethan at the new position
			arr[x][y - 1] = '/';
			arr[x][y + 1] = '\\';
			arr[x - 1][y] = 'O';
			arr[x + 1][y - 1] = '/';
			arr[x + 1][y + 1] = '\\';
		}
		break;
	case 's':
		if (x < row_size - 3)
		{
			arr[x][y] = ' '; // clearing current position
			arr[x][y - 1] = ' ';
			arr[x][y + 1] = ' ';
			arr[x - 1][y] = ' ';
			arr[x + 1][y - 1] = ' ';
			arr[x + 1][y + 1] = ' ';
			x++; // move down one row
			arr[x][y] = '|'; // ethan at the new position
			arr[x][y - 1] = '/';
			arr[x][y + 1] = '\\';
			arr[x - 1][y] = 'O';
			arr[x + 1][y - 1] = '/';
			arr[x + 1][y + 1] = '\\';
		}
		break;
	case 'a':
		if (y > 2)
		{
			arr[x][y] = ' '; // clearing current position
			arr[x][y - 1] = ' ';
			arr[x][y + 1] = ' ';
			arr[x - 1][y] = ' ';
			arr[x + 1][y - 1] = ' ';
			arr[x + 1][y + 1] = ' ';
			y--; // move left one column
			arr[x][y] = '|'; // ethan at the new position
			arr[x][y - 1] = '/';
			arr[x][y + 1] = '\\';
			arr[x - 1][y] = 'O';
			arr[x + 1][y - 1] = '/';
			arr[x + 1][y + 1] = '\\';
		}
		break;
	case 'd':
		if (y < col_size - 3)
		{
			arr[x][y] = ' '; // clearing current position
			arr[x][y - 1] = ' ';
			arr[x][y + 1] = ' ';
			arr[x - 1][y] = ' ';
			arr[x + 1][y - 1] = ' ';
			arr[x + 1][y + 1] = ' ';
			y++; // move right one column
			arr[x][y] = '|'; // ethan at the new position
			arr[x][y - 1] = '/';
			arr[x][y + 1] = '\\';
			arr[x - 1][y] = 'O';
			arr[x + 1][y - 1] = '/';
			arr[x + 1][y + 1] = '\\';
		}
		break;
	case 'q':
		exit(0);
		break;
	default:
		cout << "Invalid key. Use W, A, S, D to move or Q to quit." << endl;
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

		}
		while (arr[obstacleX][obstacleY] != ' ' || arr[obstacleX][obstacleY + 1] != ' ' || arr[obstacleX][obstacleY + 2] != ' '); // Check if spaces are free for obstacles 
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

		} while (arr[obstacleX][obstacleY] != ' ' || arr[obstacleX][obstacleY + 1] != ' ' || arr[obstacleX][obstacleY + 2] != ' ' || arr[obstacleX][obstacleY + 3] != ' ' || arr[obstacleX][obstacleY + 4] != ' ');; // Check if spaces are free for obstacles 
		arr[obstacleX][obstacleY] = '['; // Place obstacle after ensuring no overlap
		arr[obstacleX][obstacleY + 1] = '-';
		arr[obstacleX][obstacleY + 2] = '-';
		arr[obstacleX][obstacleY + 3] = '-';
		arr[obstacleX][obstacleY + 4] = ']';
	}
}


// Adding enemies
void initializeEnemies(char map[][col_size],int level){
    int RandomRow, RandomCol;
    int startRow, endRow;
    int startCol, endCol;
    srand(time(0));     //seeding rand()
    for (int i = 0; i <= level;i++){     //for loop to generate number of enemies according to level
        startRow = 2, endRow = row_size/2 -2 ;      //bound for random enemy location
        startCol = 2, endCol = col_size - 3;
        do{
            RandomRow = RandomNumber(startRow, endRow);
            RandomCol = RandomNumber(startCol, endCol);
        } while (enemyCollision(RandomRow,RandomCol));
        map[RandomRow][RandomCol] = 'V';
        map[RandomRow - 1][RandomCol] = '|';

        map[RandomRow - 1][RandomCol - 1] = '[';
        map[RandomRow - 1][RandomCol + 1] = ']';

        map[RandomRow][RandomCol - 1] = '[';
        map[RandomRow][RandomCol + 1] = ']';

        switch(i){
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
            default:
                cout << "Error in the swtich case for Enemy pos \n";
        }
    }
}

void PrintMap(){
    for (int i = 0; i < row_size;i++){
        for (int j = 0; j < col_size;j++){
            cout << map[i][j];
        }
        cout << endl;
    }
}

int RandomMap(){
    srand(time(0));
    int r[2] = {1, 2};
    int l = rand() % (2);
    int Random = r[l];
    return Random;
}

int RandomNumber(int start, int end){
    int Random = start + rand() % (end - start + 1);
    return Random;
}

bool collisionCheck(int row, int col){
    if (map[row][col] == ' '){
        return true;
    }
    else{
        return false;
    }
}

bool enemyCollision(int PosY, int PosX){
    if((collisionCheck(PosY,PosX)) && (collisionCheck(PosY,PosX-1)) && (collisionCheck(PosY,PosX+1)) && (collisionCheck(PosY-1,PosX-1)) && (collisionCheck(PosY-1,PosX+1)) && (collisionCheck(PosY-1,PosX))){
        return false;
    }
    else{
        return true;
    }
}

void trackingEthan(int level){
    for (int i = 0; i <= level;i++){
        switch(i){
            case 0:
                updatingEnemyPos(EnemyPos1Y, EnemyPos1X,1);
                break;
            case 1:
                updatingEnemyPos(EnemyPos2Y, EnemyPos2X,2);
                break;
            case 2:
                updatingEnemyPos(EnemyPos3Y, EnemyPos3X,3);
                break;
            case 3:
                updatingEnemyPos(EnemyPos4Y, EnemyPos4X,4);
                break;
            case 4:
                updatingEnemyPos(EnemyPos5Y, EnemyPos5X,5);
                break;
            case 5:
                updatingEnemyPos(EnemyPos6Y, EnemyPos6X,6);
            default:
                cout << "Error in the swtich case for Updating Enemy pos \n";
        }
    }
}

void updatingEnemyPos(int EnemyPosY, int EnemyPosX,int enemyNumber){
    map[EnemyPosY][EnemyPosX] = ' ';
    map[EnemyPosY - 1][EnemyPosX] = ' ';
    if(EnemyPosX>ethanposX){
        EnemyPosX--;
    }
    else if(EnemyPosX<ethanposX){
        EnemyPosX++;
    }
    if(EnemyPosY>ethanposY){
        EnemyPosY--;
    }
    else if(EnemyPosY<ethanposY){
        EnemyPosY++;
    }
    map[EnemyPosY][EnemyPosX] = 'V';
    map[EnemyPosY - 1][EnemyPosX] = '|';
    switch(enemyNumber){
            case 1:
                EnemyPos1X = EnemyPosX;
                EnemyPos1Y = EnemyPosY;
                break;
            case 2:
                EnemyPos2X = EnemyPosX;
                EnemyPos2Y = EnemyPosY;
                break;
            case 3:
                EnemyPos3X = EnemyPosX;
                EnemyPos3Y = EnemyPosY;
                break;
            case 4:
                EnemyPos4X = EnemyPosX;
                EnemyPos4Y = EnemyPosY;
                break;
            case 5:
                EnemyPos5X = EnemyPosX;
                EnemyPos5Y = EnemyPosY;
                break;
            case 6:
                EnemyPos6X = EnemyPosX;
                EnemyPos6Y = EnemyPosY;
            default:
                cout << "Error in the swtich case for Updating each Enemy pos \n";
        }
}

void initializeRandomMap(){
    int Random = RandomMap();
    if(Random == 1){
        initializeMap1(map);
    }
    else if(Random == 2){
        initializeMap2(map);
    }
    else{
        cout << "Error in random map generation \n";
    }
}
#include <stdio.h>
#include <time.h>// Manages time-related operations. Used to seed the random number generator with the current time.
#include <windows.h>// Provides access to Windows-specific functions and data types. Used for console manipulation and introducing delays.Sleep()
#include <conio.h>//Facilitates console input and output operations. Used for reading single characters from the console without echoing them.
//used for getch()
#define GOORANGE  "\x1b[38;5;208m" //  orange color
#define GOGREEN   "\x1b[32m" // Green color
#define GOBLUE    "\x1b[34m" //blue color
#define GORED     "\x1b[31m" //red color
#define GOYELLOW  "\x1b[33m" //yellow color
#define RESET "\033[0m" // Define RESET as the ANSI escape code to reset text color
void stable(int x, int y) //The stable function is a common utility function used to move the cursor to a specific position on the console window
{
    COORD coord;//represents 2d coordinate
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//sets the cursor position in the specified console screen buffer.

}



int G[26][76];        // represent game board
int X[1771], Y[1771]; // store coordinates of snake body
int l = 5;            // initial length of snake
int s = 0;            // initial score
int x;                // coordinates of food of snake
int y;
int f = 0; // control expansion and contraction of boundaries
int d = 1; // initial direction of snake


void print()
{

    int i, j;
    for (i = 1; i <= 25; i++)
    {
        for (j = 1; j <= 75; j++)
        {
            if ((i == 1 || i == 25) && (j < 35 - f || j > 39 + f))//35 - f and 39 + f are used in the boundary checks to create a range within which the boundary shouldn't be printed.Left to right
                printf(GOGREEN"|");
            // reperesent boundaries, i(row): top-bottom, j(columns):left to right.
            else if ((j == 1 || j == 75) && (i < 10 - f || i > 14 + f))//10-f and 14+f are used for creating a range within which boundary isn't there from top to bottom
                printf(GOGREEN"-");
            // checks for left and right boundary
            else if (G[i][j] == 1)
                printf(GOORANGE"*");
            // represent snake's body
            else if (G[i][j] == 2)
                printf(GOBLUE"O");
            // represent snake's food
            else if (G[i][j] == 3)
                printf(GOORANGE">");
            // snake's head in right
            else if (G[i][j] == 4)
                printf(GOORANGE"^");
            // snake's head in up
            else if (G[i][j] == 5)
                printf(GOORANGE"<");
            // snake's head left
            else if (G[i][j] == 6)
                printf(GOORANGE"v");
            // snake's head down
            else
                printf(" ");
        }
        printf("\n");
    }
    printf(GOBLUE"\nscore : %d", s); // prints current score
}

void snake()
{
    int i, j;
    // Clear the entire game board
    for (i = 1; i <= 25; i++)
    {
        for (j = 1; j <= 75; j++)
        {
            G[i][j] = 0;
        } // cells are initially empty
        // Boundary
    }
    // Draw the new boundary
    for (i = 1; i <= 25; i++)
    {
        for (j = 1; j <= 75; j++)
        {
            if ((i == 1 || i == 25) && (j < 35 - f || j > 39 + f))
                G[i][j] = 1;//we always keep G[i][j]=1 so that snake always remains within the boundary, as its tail would keep increasing
            else if ((j == 1 || j == 75) && (i < 10 - f || i > 14 + f))
                G[i][j] = 1;
        }
    } // sets the boundary cells of the game board to contain 1
    // Snake and food

    G[X[0]][Y[0]] = 1;
    if (d == 1)
        G[X[1]][Y[1]] = 3;//The corresponding value (3, 4, 5, or 6) is assigned to G[X[1]][Y[1]] to represent the snake's head facing in the appropriate direction.
    else if (d == 2)
        G[X[1]][Y[1]] = 4;
    else if (d == 3)
        G[X[1]][Y[1]] = 5;
    else if (d == 4)
        G[X[1]][Y[1]] = 6;
    for (i = 2; i <= l; i++)
    {
        G[X[i]][Y[i]] = 1;//remaining body segments of the snake (from index 2 to l) are placed on the game board by assigning the value 1 to G[X[i]][Y[i]]
    }
    if (f > 0)//if f>0, G is assigned a value of 2 so that food is still there
    {
     G[x][y] = 2;
        f = f - 1;//we then decrease its value by 1 to control expansion and contraction of boundaries
        //when f=1, it expands outwards, but when we apply f-1, it contracts, generating motion
    } // places of snake on the game board
}

int main()
{
    printf(GOBLUE"\t\t\t\t\t\t\tWELCOME TO TOUCH AND DIE\n");
    printf("\n");
    printf("  __        __   _                            \n");
    printf("  \\ \\      / /__| | ___ ___  _ __ ___   ___  \n");
    printf("   \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ \n");
    printf("    \\ V  V /  __/ | (_| (_) | | | | | |__(_)|\n");
    printf("     \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___ \n");


 printf("Press any key to start\n");
    getch();
    printf(GORED"RULES OF THE GAME\n");
    printf(RESET"The snake will move\n");
    printf(RESET"If you take up food, snake increases\n");
    printf(RESET"If snake touches wall, you are out\n");
    printf(RESET"If snake touches itself, then its out\n");
    printf(RESET"As you eat food, you get points\n");
    printf(GOGREEN"BEST OF LUCK!!\n");
    printf(RESET"Press any key\n");
    getch();//game starts after pressing any key
     printf(GOYELLOW"   SSSS   TTTTTT   AAA   RRRRR   TTTTTT  \n");
    printf(GOYELLOW"  S       T       A   A  R    R     T     \n");
    printf(GOYELLOW"   SSSS   T      AAAAAAA RRRRR      T     \n");
    printf(GOYELLOW"      S   T      A     A R    R     T     \n");
    printf(GOYELLOW"  SSSS    T      A     A R     R    T     \n");
    printf(RESET"");

    printf(GORED"Press Enter to start\n");
    getchar();//game starts after pressing enter only
    int i, j, k;
    srand(time(NULL)); // random number generator using current time to ensure different random number when the program runs
    X[0] = 0;
    Y[0] = 0;
    X[1] = 12;
    Y[1] = 12;
    X[2] = 12;
    Y[2] = 11;
    // Initializing snake's initial position
    X[3] = 12;
    Y[3] = 10;
    X[4] = 12;
    Y[4] = 9;
    X[5] = 12;
    Y[5] = 8;
    i = 12;
    j = 12;
    snake();
    while (G[X[0]][Y[0]] >= 1)
    {
        X[0] = rand() % 23 + 2;//assigning random position to snake initially
        Y[0] = rand() % 73 + 2;
    }
    snake(); // calling snake function
    print();
    getch();
    system("CLS");//to clear the console screen.
    while (1)// infinite loop, meaning it will continue to execute indefinitely until a break condition is encountered or the program is terminated externally
    {
        snake();
        print(); // prints initial state of game board
        if (d == 1)//when there is space b/w boundaries
        {
            if (Y[1] == 75)
                Y[1] = 0;
                // Check for Empty Cell Ahead
            if (G[X[1]][Y[1] + 1] == 0)
            {    // Move the snake forward
                for (k = l; k > 1; k--)
                {
                    X[k] = X[k - 1];//updates position of snake's body as it moves
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] + 1;
                i = X[1];//updating position of rows and columns when it moves
                j = Y[1];
            }
            else if ((X[1] == X[0]) && (Y[1] + 1 == Y[0]))//checks if snake's head position is adj with food position
            {
                for (k = l + 1; k > 1; k--)
                {
                    X[k] = X[k - 1];//moves each segment one step forward, with each segment taking the position of the segment in front of it.
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] + 1;//effectively moving the head to the position of the food.
                i = X[1];//updating position of rows and columns when it acquires food
                j = Y[1];
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1)
                {
                    X[0] = rand() % 23 + 2; // ensures that food position is in playing area
                    Y[0] = rand() % 73 + 2;
                }   // selects position of food randomly
                l = l + 1; // length increment
                s = s + 1; // score increment
            }
            else
                break;
        }
        else if (d == 2) // direction of movement is up
        {
            if (X[1] == 1)
                X[1] = 26;              // checking if snake hits top wall and then wrapping it around to bottom boundary
            if (G[X[1] - 1][Y[1]] == 0) // checking if cell above snake is empty, if empty snake can move up
            {
                for (k = l; k > 1; k--)
                {
                    X[k] = X[k - 1];// movement of row upwards
                    Y[k] = Y[k - 1]; //column same
                }
                X[1] = X[1] - 1; // updating snake's head position
                i = X[1];
                j = Y[1]; // i,j are also updated
            }
            else if ((X[1] - 1 == X[0]) && (Y[1] == Y[0])) // if snake's head reaches food
            {
                for (k = l + 1; k > 1; k--) // move snake's body upwards
                {
                    X[k] = X[k - 1]; // move row coordinates up keeping columns same
                    Y[k] = Y[k - 1]; // maintain same column coordinate
                }
                X[1] = X[1] - 1; // moves snake left
                i = X[1];
                j = Y[1]; // update i and j to hold snake's head
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1)
                {
                    X[0] = rand() % 23 + 2; // updating posistion of food to any random position
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1; // length increment
                s = s + 1; // score increment
            }
            else
                break;
        }
        else if (d == 3)//left movement
        {
            if (Y[1] == 1)
                Y[1] = 76;
            if (G[X[1]][Y[1] - 1] == 0)
            {
                for (k = l; k > 1; k--)
                {
                    X[k] = X[k - 1];//move row coordinate left
                    Y[k] = Y[k - 1];//keep columns same
                }
                Y[1] = Y[1] - 1;//moves snake down
                i = X[1];//updating values of i and j
                j = Y[1];
            }
            else if ((X[1] == X[0]) && (Y[1] - 1 == Y[0]))//food consumption check
            {
                for (k = l + 1; k > 1; k--)
                {
                    X[k] = X[k - 1];//moves each segment one step forward, with each segment taking the position of the segment in front of it.
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] - 1;
                i = X[1];
                j = Y[1];
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1)
                {
                    X[0] = rand() % 23 + 2;//choose new position for food
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1;//length increment
                s = s + 1;//score increment
            }
            else
                break;
        }
        else if (d == 4) // check if head of snake is at bottom boundary
        {
            if (X[1] == 25)             // check if head of snake is at bottom boundary
                X[1] = 0;               // move to top boundary
            if (G[X[1] + 1][Y[1]] == 0) // check if cell below snake's head is empty
            {
                for (k = l; k > 1; k--)
                {
                    X[k] = X[k - 1]; // move row down
                    Y[k] = Y[k - 1]; // keep same column
                }                    // move snake down
                X[1] = X[1] + 1;    
                 // updating variables holding snake's head position
                i = X[1];
                j = Y[1];
            }
           
            else if ((X[1] + 1 == X[0]) && (Y[1] == Y[0])) // if snake encounters food
            {
                // move snake downwards
                for (k = l + 1; k > 1; k--)
                {
                    X[k] = X[k - 1];//moves each segment one step forward, with each segment taking the position of the segment in front of it.
                    Y[k] = Y[k - 1];
                }
                X[1] = X[1] + 1;
                i = X[1];
                j = Y[1]; // update variables holding head position
                x = X[0];
                y = Y[0];
                // save position of food
                f = l;

                while (G[X[0]][Y[0]] >= 1)
                {
                    X[0] = rand() % 23 + 2; // choose new position for food
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1; // length increment
                s = s + 1; // score increment
            }
            else
                break;
        }
        if ((GetAsyncKeyState(VK_RIGHT)) && (d != 3))
            d = 1;
        // GetAsyncKeyState: This function checks whether a specific key is currently pressed. It takes the virtual key code of the key you want to check.
        // VK_RIGHT, VK_UP, VK_LEFT, VK_DOWN: These are virtual key codes representing the arrow keys on the keyboard. They indicate right, up, left, and down arrow keys, respectively.
        // d!=3 states if direction of snake is left, it will move 90 deg not 180
        else if ((GetAsyncKeyState(VK_UP)) && (d != 4))
            d = 2;
        // GetAsyncKeyState: This function checks whether a specific key is currently pressed. It takes the virtual key code of the key you want to check.
        // VK_RIGHT, VK_UP, VK_LEFT, VK_DOWN: These are virtual key codes representing the arrow keys on the keyboard. They indicate right, up, left, and down arrow keys, respectively.
        // d!=4 states if direction of snake is down, it won't move up

        else if ((GetAsyncKeyState(VK_LEFT)) && (d != 1))
            d = 3;
        // GetAsyncKeyState: This function checks whether a specific key is currently pressed. It takes the virtual key code of the key you want to check.
        // VK_RIGHT, VK_UP, VK_LEFT, VK_DOWN: These are virtual key codes representing the arrow keys on the keyboard. They indicate right, up, left, and down arrow keys, respectively.
        // d!=1 states if direction of snake is right, it will move 90 deg not 180
        else if ((GetAsyncKeyState(VK_DOWN)) && (d != 2))
            d = 4;
        // GetAsyncKeyState: This function checks whether a specific key is currently pressed. It takes the virtual key code of the key you want to check.
        // VK_RIGHT, VK_UP, VK_LEFT, VK_DOWN: These are virtual key codes representing the arrow keys on the keyboard. They indicate right, up, left, and down arrow keys, respectively.
        // d!=2 states if direction of snake is up, it will move down without colliding
        Sleep(20);     // pause execution for 20 ms.Control the speed of the game by adding a short delay between each frame update.
        stable(0,0);
        //stable(0, 0); the cursor position is reset to the top-left corner of the console window, which is a common practice to ensure that subsequent output starts from the beginning of the window, making the display consistent and avoiding overlapping or misplaced text or graphics
    }
      printf("\n");
    printf(GORED"  GGGGG   AAAAA   M     M  EEEEE   \n");
    printf(GORED" G     G  A     A  MM   MM  E       \n");
    printf(GORED"G         AAAAAAA  M M M M  EEEEE   \n");
    printf(GORED"G   GGG  A     A  M  M  M  E       \n");
    printf(GORED" G     G A     A  M     M  EEEEE   \n\n");
    printf(RESET""); 
    printf(GORED"    OOO   V     V  EEEEE  RRRRR\n");
    printf(GORED"  O     O  V   V   E      R    R\n");
    printf(GORED" O       O  V V    EEEEE  RRRRR\n");
    printf(GORED"  O     O   V V    E      R   R\n");
    printf(GORED"    OOO      V     EEEEE  R    R\n");
    getchar(); // called to wait for the user to press any key before exiting the program

    return 0;
}

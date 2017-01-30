/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// position blank cell
int b_row, b_col;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(100000);
        }

        // sleep thread for animation's sake
        usleep(100000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(1000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // initialize the highest number in the board
    int number = d * d - 1;

    // initialize the blank cell position
    b_row = b_col = (d - 1);

    // loop through each tile and add correct number to them
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            board[row][col] = number;

            // swap the last two tiles in case of even d board
            if (d % 2 == 0)
            {
                if (number == 2)
                {
                    board[row][col] = 1;
                }
                else if (number == 1)
                {
                    board[row][col] = 2;
                }
            }

            number--;
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // loop through each tile and print the value to the console
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            if (board[row][col])
                printf("%3i", board[row][col]);
            else
                printf("  _");
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // check tile above the blank one
    if (b_row > 0 && board[b_row - 1][b_col] == tile)
    {
        // swap tiles
        board[b_row][b_col] = board[b_row - 1][b_col];
        board[b_row - 1][b_col] = 0;

        // update blank tile position and return
        b_row--;
        return true;
    }
    // check tile below the blank one
    else if (b_row < d - 1 && board[b_row + 1][b_col] == tile)
    {
        // swap tiles
        board[b_row][b_col] = board[b_row + 1][b_col];
        board[b_row + 1][b_col] = 0;

        // update blank tile position and return
        b_row++;
        return true;
    }
    // check tile to the left
    else if (b_col > 0 && board[b_row][b_col - 1] == tile)
    {
        // swap tiles
        board[b_row][b_col] = board[b_row][b_col - 1];
        board[b_row][b_col - 1] = 0;

        // update blank tile position and return
        b_col--;
        return true;
    }
    // check tile to the right
    else if (b_col < d - 1 && board[b_row][b_col + 1] == tile)
    {
        // swap tiles
        board[b_row][b_col] = board[b_row][b_col + 1];
        board[b_row][b_col + 1] = 0;

        // update blank tile position and return
        b_col++;
        return true;
    }

    // invalid move
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // track the tile number
    int number = 1;

    // loop through each tile and check that the order is correct
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            if (board[row][col] != number && number < (d * d))
                return false;

            number++;
        }
    }

    // won!
    return true;
}

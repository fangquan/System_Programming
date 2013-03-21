/* CS033 Lab 01 - Life
   Written June 2012 by the CS033 Dev Team

   Executes Conway's Game of Life on the game board set in main,
   printing the results to stdout. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define ROWS 9
#define COLS 7
#define ROWS1 5
#define COLS1 4
/* Execute the Life algorithm for a number of 
   steps given the initial generation array */
void do_life(int rows, int cols, int array[rows][cols], int steps);

/* Performs a single iteration of the Life algorithm, given the old game board in old_array,
   and stores the result in new_array */
void update(int rows, int cols, int old_array[rows][cols], int new_array[rows][cols]);

/* Determines the next state for the cell at a particular row and column based on the previous iteration's board */
int get_next_state(int rows, int cols, int array[rows][cols], int row, int col);


/* Determines whether or not the cell at a particular row and column is on the game board. */
int is_in_range(int rows, int cols, int row, int col);


/* Determines the number of live neighbors of the cell at a particular row and column. */
int count_alive_neighbors(int rows, int cols, int array[rows][cols], int row, int col);


/* Determines whether or not the cell at a particular row and column is alive on the board array. */
int is_alive(int rows, int cols, int array[rows][cols], int row, int col);


/* Sets the cell at a particular row and column to be alive on the board array. */
void set_alive(int rows, int cols, int array[rows][cols], int row, int col);


/* Sets the cell at a particular row and column to be dead on the board array. */
void set_dead(int rows, int cols, int array[rows][cols], int row, int col);


/* Prints the array array to stdout. */
void print_array(int rows, int cols, int array[rows][cols]);


/* Function main

   This function is where the program begins.  Initializes the game board
   and calls do_life to execute the algorithm.

   Input: int    argc - The number of program arguments, including the executable name
          char** argv - An array of strings containing the program arguments.
 	
   Output: 0 upon completion of the program
 */
int main(int argc, char** argv) {
    /* If argc is at least 2, parse the second element of argv as the number of
       iterations to run.  Otherwise, set the number of iterations to some default
       value.  To do this, use the function
           int atoi(char *nptr)
       which is like Java's Integer.parseInt(). */
	int iteration;
	if ( argc != 2)
	{ printf ("Usage: ./life iteration# \n"); return 0;}
	else 
	{
	iteration = atoi(argv[1]);	// Convert string to int
	}
    /* Create the game board, a 2D int array. For this lab, you'll want to hard code the array
       dimensions using preprocessor #define directives as seen in class. Then choose an arbitrary initial
       configuration for the board (fill each entry with either 0 (a dead cell) or 1 (a live cell)). */
	int board[ROWS][COLS] = {
	{1, 1, 0, 1, 0, 1, 0},
	{1, 1, 0, 1, 0, 1, 0},
	{0, 0, 0, 1, 0, 1, 0},
	{1, 1, 1, 1, 0, 1, 0},
	{0, 0, 0, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 0, 1, 1}};

	/*
	int board1[ROWS1][COLS1] = {
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 0, 0}};

	int board2[ROWS1][COLS1] = {
	{0, 0, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 0}};
	*/

    /* Call the function do_life, passing in the board dimensions, the board itself,
       and the number of iterations to run the Life algorithm. */
	
	do_life(ROWS,COLS,board,iteration);

    /* Return 0 to show that the program has completed successfully. */

}

	/*Function do_life

   Executes Conway's Game of Life on board array for steps iterations,
   printing the board at each iteration.
   Input: int     rows  - the number of rows of the game board
          int     cols  - the number of columns of the game board
          int[][] array - the initial game board, a 2D array of zeros and ones
          int     steps - the number of iterations for which to run the life algorithm
   Output: None
 	*/
void do_life(int rows, int cols, int array[rows][cols], int steps) {
	/* Create an array to store the next state of the board at each step */
	int other_array[rows][cols];
	
	/* Create a pointer to each array, need to specify all the dimensions, except the first */
	int (*old_ptr)[cols] = array;
	int (*new_ptr)[cols] = other_array;
	// declares a rows x cols array, and creates a pointer "new_ptr" to it
	// An array variable can be assigned to a pointer whose "pointee" type is the array element type.


	/* 
	Run the Life algorithm steps times.  At each iteration, you should do the following:
	1. Print the current generation of the game board by calling print_array.
	2. Get the next generation of the game board by calling update, passing in the old state and the spare array to hold the new state.
	3. Switch the pointers to the old and new states.
	4. Print a new line to separate the generations.
	*/	
	int s;
	int (*temp_ptr)[cols];
	print_array(rows, cols, old_ptr);
	update(rows, cols, old_ptr, new_ptr);
	//print_array(rows, cols, new_ptr);
	temp_ptr = old_ptr;		
	old_ptr  = new_ptr;
	new_ptr = temp_ptr;
	for ( s = 0; s<steps; s++)
	{	printf ("\n");
		print_array(rows, cols, old_ptr);	
		update(rows, cols, old_ptr, new_ptr);
		//print_array(rows, cols, new_ptr);
		temp_ptr = old_ptr;		
		old_ptr  = new_ptr;
		new_ptr = temp_ptr;
	}
	// ***************************************
	// C arrays are always passed as pointers 
	// ***************************************

    /*  Once this is complete, print the final generation of the game board by calling print_array. */
}


/* Function update

   Given the previous generation of the game board in old_array, performs a single iteration of Conway's
   Game of Life, storing the new generation of the game board in new_array.

   Input: int     rows      - the number of rows    of the game board
          int     cols      - the number of columns of the game board
          int[][] old_array - the previous generation of the game board, a 2D array of zeros and ones
          int[][] new_array - a 2D array where the next generation of the game board will be stored
	
   Output: None
*/

void update(int rows, int cols, int old_array[rows][cols], int new_array[rows][cols]) {
	// in the function header, create an array old_array[rows][cols] , while passing arrays is by pointers.     	
	/* For each cell in old_array, you should:
         1. Determine whether that cell will be alive or dead in the next generation
            by calling get_next_state on old_array.
         2. If the cell's next state is 1 (alive), set that cell to alive in new_array
            by calling set_alive.  Otherwise, set that cell to dead in new_array by calling
            set_dead. 
	*/
	int i,j;
	for ( i = 0; i < rows; i++)
	{	
		for ( j = 0; j < cols; j++)
		{	
			new_array[i][j] = get_next_state(rows, cols, old_array, i, j);
		}
		// old_array is passed by pointers
	}
}

/* Function get_next_state
   Given the previous generation of the game board, determines the next state of the cell at a particular
   row and column (row, col).  If the cell is not on the game board, prints an error message and terminates the program.
   Input: int     rows  - the number of rows of the game board
          int     cols  - the number of columns of the game board
          int[][] array - the previous generation of the game board, a 2D array of zeros and ones
          int     row   - the row of the cell whose next state is being determined
          int     col   - the column of the cell whose next state is being determined
   Output: The next state of the cell at (row, col); 0 if the cell will be dead and 1 if it will be alive.
*/

int get_next_state(int rows, int cols, int array[rows][cols], int row, int col) {
    /* First, use an assert statement and call is_in_range to confirm the specified cell is on the game board. */

	assert(is_in_range(rows, cols, row, col));
    /* Then, assuming the assert succeeds:
         1. Determine how many live neighbors the cell had in the previous generation by calling count_alive_neighbors.
         2. Determine if the cell was alive in the previous generation by calling is_alive.
         3. Return 1 (alive) if the cell was alive and had 2 or 3 live neighbors, or if the cell was dead and had 3 live neighbors.
         4. Return 0 (dead) otherwise. */
	int alive_neighbors;
	alive_neighbors = count_alive_neighbors( rows, cols, array, row, col);
	if ( is_alive(rows, cols, array, row, col) && ( alive_neighbors == 2 || alive_neighbors == 3 ) )
	{
		return 1;
	} 
	else if ( is_alive(rows, cols, array, row, col)  == 0 && alive_neighbors == 3)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



/* Function is_in_range

   Given a row and column (row, col), determines if the cell at that position is on a zero-indexed game board
   with a given number of rows and columns.


   Input: int rows - the number of rows of the game board
          int cols - the number of columns of the game board
          int row  - the row of the cell in question
          int col  - the column of the cell in question

   Output: 1 (true) if the cell is on the game board and 0 (false) otherwise
 */
int is_in_range(int rows, int cols, int row, int col) {
    /* Return 1 if row is between 0 and rows-1, inclusive and col is between 0 and cols-1, inclusive; otherwise return 0 */
	if ( row >= 0 && row <= rows - 1 && col >= 0 && col <= cols -1 )
		{return 1;}
	else
		{return 0;}
}


/* Function count_alive_neighbors

   Given a game board, array, and a row and column (row, col), determines the number of surrounding cells that are alive.
   If the cell is not on the game board, prints an error message and terminates the program.


   Input: int     rows  - the number of rows of the game board
          int     cols  - the number of columns of the game board
          int[][] array - the previous generation of the game board, a 2D array of zeros and ones
          int     row   - the row of the cell whose neighbors are being counted
          int     col   - the column of the cell whose neighbors are being counted

   Output: The number of surrounding cells that are alive
 */
int count_alive_neighbors(int rows, int cols, int array[rows][cols], int row, int col) {
    /* First, use an assert statement and call is_in_range to confirm the specified cell is on the game board. */
	assert(is_in_range(rows, cols, row, col));

    /* Then, assuming the assert succeeds:
         Compute and return the number of live neighbors by adding together the results of is_alive for each of
         the 8 surrounding cells.  Since is_alive checks to see if a cell is on the board, you do not need to do so here. */
	int neighbor;
	neighbor = is_alive(rows,cols,array,row-1,col-1) 
	  + is_alive(rows,cols,array,row-1,col) 
	  + is_alive(rows,cols,array,row-1,col+1) 
	  + is_alive(rows,cols,array,row,col-1) 
	  + is_alive(rows,cols,array,row,col+1) 
	  + is_alive(rows,cols,array,row+1,col-1) 
	  + is_alive(rows,cols,array,row+1,col) 
	  + is_alive(rows,cols,array,row+1,col+1);
	//printf ("%d ",neighbor);
	return neighbor; 
}


/* Function is_alive

   Given a game board, array, and a row and column (row, col), determines if the cell is alive or not.  If the cell
   is not on the game board, returns 0.

   Input: int     rows  - the number of rows of the game board
          int     cols  - the number of columns of the game board
          int[][] array - the game board, a 2D array of zeros and ones
          int     row   - the row of the cell in question
          int     col   - the column of the cell in question

   Output: 1 if the cell is alive (is 1), 0 if it is dead (is 0) or out of range.
 */
int is_alive(int rows, int cols, int array[rows][cols], int row, int col) {
    /* First, determine if the cell is on the game board by calling is_in_range.
       If the result is 1 (true), then return the value of the cell
       Otherwise, return 0.  Unlike with other functions, this should not cause the program to terminate. */
	if ( is_in_range(rows, cols, row, col) )
		{ return array[row][col];}
	else
		return 0;
}


/* Function set_alive

   Given a game board, array, and a row and column (row, col), sets the cell to be alive.  If the cell is not on
   the game board, prints an error message and terminates the program.

   Input: int     rows  - the number of rows of the game board
          int     cols  - the number of columns of the game board
          int[][] array - the game board, a 2D array of zeros and ones
          int     row   - the row of the cell in question
          int     col   - the column of the cell in question

   Output: None
 */
void set_alive(int rows, int cols, int array[rows][cols], int row, int col) {
    /* First, use an assert statement and call is_in_range to confirm the specified cell is on the game board. */
	assert(is_in_range(rows, cols, row, col));
    /* Then, assuming the assert succeeds, set that cell's value to 1 in array.*/
	array[row][col] = 1;
}

/* Function set_dead

   Given a game board, array, and a row and column (row, col), sets the cell to be dead.  If the cell is not on
   the game board, prints an error message and terminates the program.

   Input: int     rows  - the number of rows of the game board
          int     cols  - the number of columns of the game board
          int[][] array - the game board, a 2D array of zeros and ones
          int     row   - the row of the cell in question
          int     col   - the column of the cell in question

   Output: None
 */
void set_dead(int rows, int cols, int array[rows][cols], int row, int col) {
    /*  First, use an assert statement and call is_in_range to confirm the specified cell is on the game board. */
	assert(is_in_range(rows, cols, row, col));
    /* Then, assuming the assert succeeds, set that cell's value to 0 in array. */
	array[row][col] = 0;
}


/* Function print_array

   Given a game board, array, prints the board to stdout using printf.

   Input: int     rows  - the number of rows of the game board
          int     cols  - the number of columns of the game board
          int[][] array - the game board, a 2D array of zeros and ones

   Output: None
 */
void print_array(int rows, int cols, int array[rows][cols]) {
    /* For each cell on the game board, use printf to print the result of is_alive for that cell.
       After each row has been printed, be sure to print a new line.*/
    int i,j;
    for ( i = 0; i < rows; i++){	
	for ( j = 0; j < cols; j++)
		{printf ("%d ", array[i][j]);}
	printf ("\n");
    }
}



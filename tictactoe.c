/*********************************************************
 Compiling the program
*********************************************************
The program should be compiled using the following flags:
-std=c99
-Wall
compiling: gcc tictactoe.c -std=c99 -Wall -o tictactoe
*********************************************************
Running the Program
*********************************************************
running: ./tictactoe
The user is prompted to enter inputs for a row and column to
fill with their symbol until either the user or computer
wins the game.
*********************************************************/
//Mihajlo Milisic
//01/2019

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid(int entered, int minimum, int maximum);
int isBoardFull(char board[N][N]);
void createInitialBoard(char board[N][N]);
void readUserMove(int * userRow, int * userCol);
void printCurrentBoard(char board[N][N]);
int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol);
int gameWon(char board[N][N], char symbol);
int computerPlaysToWin(char board[N][N], int * cRow, int * cCol);
void computerPlaysRandom(int * cRow, int * cCol, int uRow, int uCol);
void sumAllDimensions(char board[N][N], int sumR[N], int sumC[N], int * sumLD, int * sumRD);
int memberOf(int aNum, int someArray[N]);
//bonus function
int computerPlaysToBlock (char board[N][N], int * cRow , int * cCol);


int main(){

   int userRow, userCol, computerRow, computerCol;
   int taken;
   char board[N][N];
   char winner = 'N';
   
   srand(time(NULL));
    
   printf("This tic-tac-toe board is of size %d by %d\n", N, N);
   
   printf("Player symbol: X \nComputer symbol: O\n\n");

   printf("Here is the board - spaces are indicated by a ?\n");

   createInitialBoard(board);     // create a 3 X 3 board with '?' in each cell
   
   while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
   {
     taken = 0;
     
    while (!(taken))                  // loop used to accept valid row and col values from the user
    {
      readUserMove(&userRow, &userCol);                  //get user's move
      printf("You chose row %d and column %d \n", userRow, userCol);
      
      while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))     // validate user's move
      {
        printf("That's is an invalid row or column number - try again\n");
        readUserMove(&userRow, &userCol);
        printf("You chose row %d and column %d \n", userRow, userCol);
      }
           
      if (board[userRow-1][userCol-1] == '?')           // if cell is unoccupied
      {
        board[userRow-1][userCol-1] = 'X';      // store an X there
        taken = 1;
      }
      else
      {
        taken = 0;                  // otherwise inform the user to enter values again
        printf("That spot is taken - please try another one\n");
      }
      
    } //end of while (!taken)
  
     if (gameWon(board, 'X'))   // check if the user wins - game will end if the user does win
     {
       printf("Congrats - you won against the computer :)\n");
       winner = 'Y';
     }
     
     else  if (!(isBoardFull(board)))            //check if the board is already full
     {
       taken = 0;
       
       while (!(taken))
       {
        getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1); // get computer's row and col
       
        if (board[computerRow][computerCol] == '?')         // check if the cell is unoccupied
        {
          board[computerRow][computerCol] = 'O';
          taken = 1;
  
        }
        else
        {
          taken = 0;    //That spot is taken - computer - try another one
        }
       }
       
       printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);
       
       if (gameWon(board, 'O'))               // check if the computer wins - game must end if it does
       {
         printf("Oh the computer won this time :(( think hard next time\n");
         winner = 'Y';
       }
     }
   
  printCurrentBoard(board);
  
  printf("\nPress enter to continue \n");
  getchar();
       
   } //end of while
   
   if (winner != 'Y')
      printf("Game was a tie - no winner!\n\n");
    
   return 0;
}

//FUNCTION DEFINITIONS

/*
isInputValid: checks if the inputs are valid (between 1 and 3 inclusive)
In: int entered, int minimum, int maximum
Out: int - 1 if valid input, 0 if not valid
*/
int isInputValid(int entered, int minimum, int maximum){
  int result;
  if (entered >= minimum && entered <= maximum)
    result = 1;
  else
    result = 0;

  return result;
}

/*
isBoardFull: checks if the board is full by searching for any remaining '?'
In: char board[N][N]
Out: int - 0 if there is at least one empty cell, 1 if no empty cell
*/
int isBoardFull(char board[N][N]){
  int i, j;
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      if (board[i][j] == '?') //if an empty cell is found the function will return 0
        return 0;

  return 1;  //if no empty cells (? filled) than the function will reach this line and return 1
}

/*
createInitialBoard: populates the array such that each element is '?' and prints the starting board
In: char board[N][N]
Out: none
*/
void createInitialBoard(char board[N][N]){
  int i, j;
  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {             //populating each element of the array to ? for start
      board[i][j] = '?';
    }
  }

  printf("\n");
  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      printf(" %c ", board[i][j]);
      if (j != 2)
        printf("|");                      //printing line to seperate columns 1,2 and 2,3
    }
    if (i != (N - 1))                  //printing line to seperate rows 1,2 and 2,3
      printf("\n____________\n");
  }
  printf("\n");

  return;
}


/*
readUserMove: gets the user's choice of next move
In: int * userRow, int * userCol
Out: none
*/
void readUserMove(int * userRow, int * userCol){
  printf("\nYour move - enter numbers between 1 and 3\n\n");
  printf("Enter row: ");
  scanf("%d", userRow);
  printf("Enter column: ");
  scanf("%d", userCol);
  printf("\n");
  return;
}


/*
printCurrentBoard: prints the board with the position of the sybmols the have been placed up to that point
In: char board[N][N]
Out: none
*/
void printCurrentBoard(char board[N][N]){
  int i, j;

  printf("\nCurrent Board now is: \n\n");

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      printf(" %c ", board[i][j]);
      if (j != 2)
        printf("|");                  //printing line to seperate columns 1,2 and 2,3
    }
    if (i != (N - 1))               //printing line to seperate rows 1,2 and 2,3
      printf("\n____________\n");
  }
  printf("\n");
  return;
}


/*
Function was given to the class
getComputerMove: *refer to given description starting below function definition*
In: char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol
Out: Int
*/
int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
/*
  This function determines computer's move in terms of row (computerRow) and column (computerCol)
  and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
  find one, then it calls function computerPlaysRandom in its attempt to place its symbol in
  the same row or column as the user (userRow, userCol)
*/

   int winningSpot = 0;
   int blocked = 1;
   
   winningSpot = computerPlaysToWin(board, computerRow, computerCol);
   
   if (!winningSpot)            // if computer does find a winning spot, then it plays to block the user
   {
     computerPlaysRandom(computerRow, computerCol, userRow, userCol);
     
     
     blocked = computerPlaysToBlock(board, computerRow, computerCol);
     if (blocked == 0)
       computerPlaysRandom(computerRow, computerCol, userRow, userCol);
     
   }
 
   return winningSpot;
}

/*
gameWon: Checks if either the computer or player have 3 of their respective symbols in any direction
In: char board[N][N], char symbol
Out: int - 1 if there is a winner, 0 if there is no winner so far
*/
int gameWon(char board[N][N], char symbol){
  int i, sumR[N], sumC[N], sumLD, sumRD;

  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);

  for (i = 0; i < N; ++i){
    if (sumR[i] == 12 || sumC[i] == 12 || sumLD == 12 || sumRD == 12)
      return 1;
    else if (sumR[i] == 3 || sumC[i] == 3 || sumLD == 3 || sumRD == 3)
      return 1;
  }

return 0;
}

/*
computerPlaysToWin: if the computer has 2 'O' in any direction and the 3rd spot is empty, the computer
                    will fill that spot
In: char board[N][N], int * cRow, int * cCol
Out: int - 1 if winning move available, 0 if no winning move
*/
int computerPlaysToWin(char board[N][N], int * cRow, int * cCol){
  int i,j;
  int sumR[N], sumC[N], sumLD, sumRD;

  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);

  //for if the winning move is based on row sum

  for (i = 0; i < N; ++i){
    if (sumR[i] == 8)
      for (j = 0; j < N; ++j)
        if (board[i][j] == '?'){
          *cRow = i;
          *cCol = j;
          return 1;
        }
  }
  //for if the winning move is based on column sum
  for (i = 0; i < N; ++i){
    if (sumC[i] == 8)
      for (j = 0; j < N; ++j)
        if (board[j][i] == '?'){
          *cRow = j;
          *cCol = i;
          return 1;
        }
  }
  //for if the winning move is based on the left diagonal sum
  j = 0;
  if (sumLD == 8)
    for (i = 0; i < N; ++i){
      if (board[i][j] == '?'){
        *cRow = i;
        *cCol = j;
        return 1;
      }
      j += 1;
    }

  //for if the winning move is based on the right diagonal sum
  j = 2;
  if (sumRD == 8)
    for (i = 0; i <= N; ++i){
      if (board[i][j] == '?'){
        *cRow = i;
        *cCol = j;
        return 1;
      }
      j -= 1;
    }



  return 0; //returns if computer does not win in this step
}


/*
computerPlaysRandom: Computer plays a move based on the users previous move
                     by randomly choice the type of placement in relation to the
                    user's move
In: int * cRow, int * cCol, int uRow, int uCol
Out: none
*/
void computerPlaysRandom(int * cRow, int * cCol, int uRow, int uCol){
  int typeOfMove, choice;
  typeOfMove = (rand() % 3);     //randomly picks a number between 0 and 2 for whether to match...
                                 //...the user's row, column, or diagonal

  if (typeOfMove == 0){  //same row
    *cRow = uRow;
    do{
      *cCol = rand() % 3;
    } while (*cCol == uCol);
  }
  else if (typeOfMove == 1){ //same column
    *cCol = uCol;
    do{
      *cRow = rand() % 3;
    } while(*cRow == uRow);
  }
  else if (typeOfMove == 2){ //diagonal
    //if the user's cell is one the corner ones
    if ((uRow == 0 && uCol != 1) || (uRow == 2 && uCol != 1)){
      choice = rand() % 2;
      //place in the middle cell
      if (choice == 1){
        *cRow = 1;
        *cCol = 1;
      }
      else {
      //place in the opposite corner
        *cRow = abs(uRow - 2);
        *cCol = abs(uCol - 2);
      }
    }
    else if (uCol == 1 && uRow == 1){
      //if the user's cell is the middle one, place in one of the corners
      do{
       *cCol = rand() % 3;
       *cRow = rand() % 3;
      } while (*cCol == 1 || *cRow == 1);
    }
  }

  return;
}


/*
sumAllDimensions: determines the sum of each row, column, and diagonal grouping
                   'X' increments by 1, 'O' increments by 4
In: char board[N][N], int sumR[N], int sumC[N], int * sumLD, int * sumRD
Out: none
*/
void sumAllDimensions(char board[N][N], int sumR[N], int sumC[N], int * sumLD, int * sumRD){
  int i, j;

  for (i = 0; i < N; ++i) {           //summing the rows
    sumR[i] = 0;
    for (j = 0; j < N; ++j) {
      if(board[i][j] == 'O')
        sumR[i] += 4;
      else if (board[i][j] == 'X')
        sumR[i] += 1;       //Assigning a value to 'X' to differentiate it from '?'
    }
  }
  for (i = 0; i < N; ++i) {           //summing the columns
    sumC[i] = 0;
    for (j = 0; j < N; ++j) {
      if(board[j][i] == 'O')
        sumC[i] += 4;
      else if (board[j][i] == 'X')
        sumC[i] += 1;       //Assigning a value to 'X' to differentiate it from '?'
    }
  }
 
  *sumLD = 0;       //Summing the diagonals
  *sumRD = 0;
  //top left corner
  if (board[0][0] == 'O')
    *sumLD += 4;
  else if (board[0][0] == 'X')
    *sumLD += 1;
  //bottom right corner
  if (board[2][2] == 'O')
    *sumLD += 4;
  else if (board[2][2] == 'X')
    *sumLD += 1;
  //middle cell - applies to both the LD and RD
  if (board[1][1] == 'O'){
    *sumRD += 4;
    *sumLD += 4;
  }
  else if (board[1][1] == 'X'){
    *sumLD += 1;
    *sumRD += 1;
  }
  //bottom left corner
  if (board[2][0] == 'O')
    *sumRD += 4;
  else if (board[2][0] == 'X')
    *sumRD += 1;
  //top right corner
  if (board[0][2] == 'O')
    *sumRD += 4;
  else if (board[0][2] == 'X')
    *sumRD += 1;

  return;
}

/*
I am not using this function but I was told to show that I know how to make it work
User can enter values for an array and a number to check if it is one of the elements
____________________________________________
memberOf: determines if a number is an element of an array
In: int aNum, int someArray[N]
Out: int - 1 if found in array, 0 if not
*/
int memberOf(int aNum, int someArray[N]){
  int i;

  printf("Enter a number to check if it is a member of the array: ");
  scanf("%d", &aNum);  //getting the number to check with

  for (i = 0; i < N; ++i) {  //user assigns values to the array elements
    printf("Enter element %d: ", i);
    scanf("%d", &someArray[i]);
  }

  //checking if the entered number is in the entered array
  for (i = 0; i < N; ++i)
    if (someArray[i] == aNum)
      return 1; //if aNum is a member than the function will end and return 1

  return 0;   //returns 0 if aNum is not a member of the array
}




//bonus function
/*
computerPlaysToBlock: computer plays a move which will prevent the user from winning
In: char board[N][N], int * cRow , int * cCol
Out: int - 1 if blocking, 0 if not blocking
*/
int computerPlaysToBlock (char board[N][N], int * cRow , int * cCol){
  int i,j;
  int sumR[N], sumC[N], sumLD, sumRD;

  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD); //calling function to calculate all sums

  //for if the blocking move is based on row sum

  for (i = 0; i < N; ++i){
    if (sumR[i] == 2)
      for (j = 0; j < N; ++j)
        if (board[i][j] == '?'){
          *cRow = i;
          *cCol = j;
          return 1;
        }
  }
  //for if the blocking move is based on column sum
  for (i = 0; i < N; ++i){
    if (sumC[i] == 2)
      for (j = 0; j < N; ++j)
        if (board[j][i] == '?'){
          *cRow = j;
          *cCol = i;
          return 1;
        }
  }
  //for if the blocking move is based on the left diagonal sum
  j = 0;
  if (sumLD == 2)
    for (i = 0; i < N; ++i){
      if (board[i][j] == '?'){
        *cRow = i;
        *cCol = j;
        return 1;
      }
      j += 1;
    }

  //for if the blocking move is based on the right diagonal sum
  j = 2;
  if (sumRD == 2)
    for (i = 0; i < N; ++i){
      if (board[i][j] == '?'){
        *cRow = i;
        *cCol = j;
        return 1;
      }
      j -= 1;
    }

  return 0; //returns if no blocking move
}

/*
Author: xhanwt
*/

//This program simulates the classic Knight's Tour problem

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <random>
using namespace std;

// Variables
const int SIZE = 8;
const int ROWS = 8;
const int COLS = 8;
const int LENGTH = 65;
const int tours = 200000;

// Array for Chess board representing the move number
int board[ROWS][COLS];
// Array for recording number of tours with move totals
int moveTotals[LENGTH];

// Arrays for eight possible moves
static int horizontal[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
static int vertical[] = { -1, -2, -2, -1, 1, 2, 2, 1 };

// Function prototypes
bool validMove(int, int, int[][SIZE]);
void clearBoard(int[][SIZE]);
void printBoard(int[][SIZE]);
void saveResults(int[LENGTH]);


int main() {

  
  // Simulates 200,000 times
  for (int i = 0; i < tours; i++) {
  // Clear the board
  clearBoard(board);
  //Initialize moveNumber to 0
  int moveNumber = 0;

  // Begin at random square
  // Random number engine
  random_device myEngine;

  //currentRow = random value between 0 and 7
  // Distribution object
  uniform_int_distribution<int> randomROWInt(0, 7);
  int currentRow = randomROWInt(myEngine);

  // currentColumn = random value between 0 and 7
  // Distribution object
  uniform_int_distribution<int> randomCOLInt(0, 7);
  int currentColumn = randomCOLInt(myEngine);


  // Increment moveNumber
  moveNumber += 1;
  // Set board[currentRow][currentColumn] to moveNumber;
  board[currentRow][currentColumn] = moveNumber;

  // initialize done to false
  bool done = false;

  while (!done){
    
    bool goodMove = false;
    
    // Distribution object
    uniform_int_distribution<int> randomMoveType(0, 7);
    // moveType = random value between 0 and 8
    int moveType = randomMoveType(myEngine);

    // Try popssible moves
    for (int count = 0; count < 8 && !goodMove; count +=1)
    {
    // Move the knight as a test
    int testRow = currentRow + vertical[moveType];
    int testColumn = currentColumn + horizontal[moveType];
      
    // Check if it is a good move
    goodMove = validMove(testRow,  testColumn, board);


    if (goodMove){
     // Assign current square
     currentRow = testRow;
     currentColumn = testColumn;
     moveNumber +=1;

     // Record to board
     board[currentRow][currentColumn] = moveNumber;
    }
      
    // Change to another move
    moveType = (moveType + 1) % 8;
    }
  

    if (!goodMove || moveNumber == 64){
      done = true;
      if (moveNumber ==  64) {
        printBoard(board);
     }
    }
  }
  // Record total moves
  moveTotals[moveNumber] += 1;
    
  }
  // Save results
  saveResults(moveTotals);

  // End program
  return 0;
}

/*
Clear board function 
Simply set all values of board to int 0    
*/
void clearBoard(int board[][SIZE]){
  // Each row
  for(int r = 0; r < ROWS; r++){
    // Each column
    for(int c = 0; c < COLS; c++){
      board[r][c] = 0;
    }
  }
} 

/*
Move validation function 
*/
bool validMove(int row, int column, int board[][SIZE]){
  if(row >= 0 && column >= 0 && row <= 7 && column <= 7 && board[row][column] == 0){
    return true;
  }
  return false;
} 

/*
Printing the board for successful solution(completes a full tour) function
*/
void printBoard(int board[][SIZE]){
  // Print column number lables of the board
  cout << setw(3) << "*";
  int x = 0;
  while(x < 8){
    cout << setw(3) << x;
    x++;
  }
  cout << endl; // Next line
  
  // Print board contents
  // Each row
  for(int r = 0; r < 8; r++){
    // Print row number lable
    cout << setw(3) << r;
    // Each column
    for(int c = 0; c < 8; c++){
      cout << setw(3) << board[r][c];
    }
    cout << endl; // Next line
  }
  
  cout << "\n\n"; // Separate boards
}

/*
Save results function
in form of a horizontal histogram
*/
void saveResults(int moveTotals[LENGTH]){
 
  // Validate the file 
  ofstream results;
  results.open("Results.txt");
  if(!results){
    cout << "ERROR: Couldn't save the results in the text file - no access to the file.";
      exit(0); // Halt the program
  }
  // Write in the file
  cout << "SAVING THE RESULTS..." << endl;
  // Value per asterisks
  int valuePerAst = 50;
  // Print each line
  for(int i = 1; i < LENGTH;i++){
    
    results << i << "  ";
    
    // Move totals in move number 'i'
    int mTotals = moveTotals[i];

    // Calculate percentage
    double percent = (mTotals / (double)tours) * 100.00;

    // Print asterisks
    int numOfAst = mTotals / valuePerAst;
    for(int x = 0; x < numOfAst; x++){
      results << "*";
    }
    
    if(numOfAst > 0)
    results << fixed << showpoint << setprecision(2) << "  " << percent << "%";

    // Separate line
    results << endl;
    }
  // Success
  cout << "SUCCESSFULLY WROTE THE FILE!" << endl;
  
  // Close the file
  results.close();
  
}
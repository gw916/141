/**------------------------------------------
    Program 2: Great 13

    Course: CS 141, Fall 2022.
    System: Linux x86_64 and G++
    Author: Gerard W. Wilbert
 ---------------------------------------------**/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <string>

/* Everything below this comment is starter code, and you are not
allowed to modify */

using namespace std;

// Function that displays the instructions to the user

void display_instructions()
{
    cout << "Class: CS 141" << endl
         << "Program 2: Great 13" << endl << endl
         << "Make a series of jumps until there is a single piece left" << endl
         << "anywhere on board. On each move you must jump an adjacent" << endl
         << "piece   into   an  empty  square,  jumping  horizontally," << endl
         << "vertically, or diagonally." << endl << endl
         << "Input of 'R' resets the board back to the beginning, and " << endl
         << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

// Function that returns the element at a given position
char get_element(char position)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to get element at position " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    return board[position - 'A'];
}
// function that sets an element at a given position
void set_element(char position, char value)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to set element at postion " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board()
{
    cout << endl;
    cout << setw(7) << "Board" << setw(12) << "Position" << endl;
    cout << setw(5) << board[0] << setw(11) << 'A' << endl
         << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3]
         << setw(11) << "B C D" << endl
         << board[4] << ' ' << board[5] << ' ' << board[6] << ' '
         << board[7] << ' ' << board[8] << ' '
         << " E F G H I" << endl
         << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
         << setw(11) << "J K L" << endl
         << setw(5) << board[12] << setw(11) << 'M' << endl;
    cout << endl;
}

/* This is the end of the starter code, and below is where you can
add your own code. Feel free to add helper functions or variables.
*/

/* forward declarations for the functions you will write later. This
is so the order of the function definitions, in this file,  does not
matter. */

// function creates the starting elements of the board.
void initialize_board()
{
  for(char i = 'A'; i <= 'M'; ++i) {
    if (i == 'G') {
      set_element(i, '.');
    }
    else {
      set_element(i, '#');
    }
  }
}

// Function that makes a move after the move is determined as valid.
void make_move()
{
  // Array that has all moves that can be made.
   string validMoves[32] = {"ABE", "ADI", "ACG", "BCD", "BFJ", "BGL", "CGK", "DHL", "DGJ", "EFG", "IHG", "DCB", "FGH", "GHI", "JKL", "EJM", "ILM", "GFE", "LKJ", "HGF", "IDA", "EBA", "GCA", "GKM", "MKG", "JFB", "KGC", "LHD", "MLI", "MJE", "LGB", "JGD"};

  string move;
  int i;

  cout << "Enter positions from, jump, and to (e.g. EFG): ";
  cin >> move;
  // the first check for a valid move is if it its length is 3 or its a x or r.
 if (move.size() == 3) {
   for(i = 0; i < 3; i++) {
     move.at(i) = toupper(move.at(i));
   }
 }
 else if (move == "X" || move == "x") {
   cout << "Exiting." << endl;
   exit(0);
   
 }
 else if (move == "R" || move == "r") {
   cout << "Restarting game" << endl;
   initialize_board();
   return;
 }
 else {
   cout << "*** Invalid sequence. Please retry." << endl;
   return;
 }
  // The second check is for the move to have all positions on the board which is from A to M.
  for (i = 0; i < move.size(); ++i) {
    if ((move.at(i) < 'A') || (move.at(i) > 'M')) {
      cout << "*** Given move has positions not on the board! Please retry." << endl;

      return;
    }
  }
  // The third check is to see if there is a piece at the middle part of the move 
  if (get_element(move.at(1)) == '.') {
    cout << "*** Must jump a piece. Please retry." << endl;

    return;
    }
  
// The fourth check is to see if there is a piece at the first position
  if (get_element(move.at(0)) == '.') {
    cout  << "*** Source needs a piece. Please retry." << endl;

    return;
  }

// The fifth check is to see if there is no piece at the last position
  if (get_element(move.at(2)) == '#') {
    cout << "*** Destination must be empty. Please retry." << endl;

    return;
  }
// The last check is to make sure the move is not a curve
  int count = 0;
  for(i = 0; i < 32; ++i) {
    if (validMoves[i] == move) {
      count += 1;
      break;
    }
  }

  if (count == 1) {
      set_element(move.at(0),'.');
      set_element(move.at(1),'.');
      set_element(move.at(2),'#');

  }

  else {
    cout << "*** Move is invalid. Please retry." << endl;
  }
 
  
    
}
// returns true only if there is one piece left.
bool game_over(){
  int peg_amount = 0;
  for(char i = 'A'; i <= 'M'; ++i) {
    if (get_element(i) == '.') {
      peg_amount += 1;
    }
  }
  if (peg_amount == 12) {
      return true;
    }
    else {
      return false;
    }
}





int main()
{
    display_instructions();
    initialize_board();
    do {
        display_board();
        make_move();
    } while (!game_over() && !cin.eof());
    cout << "Congrats you win!" << endl;
    return 0;
}






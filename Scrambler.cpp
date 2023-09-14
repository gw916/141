#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

class Scrambler {
  public:
    Scrambler(const string& path, const int size);
    string str();
    void try_move(const string& cmd);
    string display_solution();
    bool is_over();
    void shift_up(vector<string>& data, int columnNum);
    void shift_down(vector<string>& data, int columnNum);
    void shift_right(vector<string>& data, int rowNum);
    void shift_left(vector<string>& data, int rowNum);
    vector<string> get_words();
    void jumble_board(vector<string> &board, int size);
    void setSize(int sizes) {
      size = sizes;    
    }
vector <string>getSolutionMoves() {
      return solutionMoves;
    }
  private:
    vector<string> board;
    int size;
// Put into Scrambler instead of making b1
// The board of the words themselves with needed spaces.
    vector<string> wordUsed;
    vector<string> moves;
    vector<string> initial_board;
    vector<string> solutionMoves;
};

int random_words(vector<string> file) {
  int idx;
  idx = rand() % file.size();
  return idx;
}

void
Scrambler::shift_up(vector<string>& data, int columnNum) {
 
   // your code here
   char beginning = data[0][columnNum];
   for(int i = 1; i < size; i++) {
     data[i - 1][columnNum] = data[i][columnNum];
   }
   data[size - 1][columnNum] = beginning;
}
void 
Scrambler::shift_down(vector<string>& data, int columnNum) {
   // your code here
   char end =  data[size - 1][columnNum];
   for (int i = size - 1; i > 0; i--) {
      data[i][columnNum] = data[i-1][columnNum];
   }
   data[0][columnNum] = end;

}
void
Scrambler::shift_right(vector<string>& data, int rowNum)
{
  
   // your code here
   char end = data[rowNum][size - 1];
   for (int i = size - 1; i > 0; i--) {
      data[rowNum][i] = data[rowNum][i-1];
   }
   data[rowNum][0] = end;
}

void
Scrambler::shift_left(vector<string>& data, int rowNum)
{
   // your code here
   char beginning = data[rowNum][0];
   for(int i = 1; i < size; i++) {
     data[rowNum][i - 1] = data[rowNum][i];
   }
   data[rowNum][size - 1] = beginning;
}

string turntolowercase(string name) {
     string lowername = "";
     for(int i = 0; i < name.size(); i++) {
       char currchar = name[i];
       currchar = tolower(currchar);
       lowername += currchar;
     }
     return lowername;
   }

void Scrambler::jumble_board(vector<string>& board, int size) {
  int x;
  int numMoves;
  int d;
  int i;
  int idx;
  char rowColumn;
  char dir;
  string move;
  x = rand() % 8;
  numMoves = x + 3;
  for(i = 1; i <= numMoves; i++) {
    idx = rand() % size;
     if (i % 2 == 0) {
       rowColumn = 'c';
       d = rand() % 2;
         if(d == 0) {
         //  cout<<"here" << endl;
            dir = 'u';
           shift_up(board, idx);
         }
          else {
         //  cout<<"here" << endl;

            dir = 'd';
            shift_down(board, idx);
          }
        move = rowColumn + to_string(idx + 1) + dir;
        moves.push_back(move);
     }
     else {
     // cout<<"here" << endl;
       rowColumn = 'r';
       d = rand() % 2;
       if(d == 0) {
            dir = 'r';
            shift_right(board, idx);
         }
          else {
           // cout<<"here" << endl;
            dir = 'l';
            shift_left(board, idx);
          }
       move = rowColumn + to_string(idx + 1) + dir;
       moves.push_back(move);
     }
  }
}
/* For this function you initialize the board. 
No need for rows and colomns in my opinion.
Start with a for loop like you did initialitally.
set your spaces to the size.
for the first change of my code do while( room >= 3) 
Then call the function you create for random word.
Call it string wordRand or something it returns the word.
After that do what is said in my remainingRoom comment
That all can give so there is no strike. 
Last tip keep the function simple
*/
Scrambler::Scrambler(const string& path, const int size) {
  int room; // the space in a given row. It get initialized to size in the outer most loop. 
  int remainingRoom = size; // After each word it get subtracted. Can't be place in loop.
  int idx; // If you make a function that returns the random word then this isn't needed.
  string word; // The random word.
  string boardword = ""; // This could be a vector of characters that you loop through.
  string dictword;
  ifstream file{path};
  vector<string> dictionary;
  while(!file.eof()) {
    file >> dictword;
    dictionary.push_back(dictword);
  }
  setSize(size);
  for(int r = 0; r < size; r++) {
    room = size;
    while(room > 2) {
      idx = random_words(dictionary);
      word = dictionary[idx];
    
      remainingRoom = room - word.size();

      if(word.size() <= room && remainingRoom != 3) {
        wordUsed.push_back(word);
        boardword += word;
        room -= word.size();

        if (room > 3) {
          boardword += " ";
          room -= 1;
        }
        
      }
     
    }
     while(boardword.size() != size) {
      boardword += " ";
      
    }
    board.push_back(boardword);
    boardword = "";
    remainingRoom = 0;
    }
 jumble_board(board, size);
 initial_board = board;
}

string Scrambler::display_solution() {
  string result = str();
  int moveNum = 1;
  char dir;
  for(int i = 0; i < moves.size(); i++) {
     solutionMoves.push_back(moves[i]);
  }
  for(int r = 0; r < solutionMoves.size(); r++) {
    if(solutionMoves[r][0] == 'c') {
      solutionMoves[r][2] = (solutionMoves[r][2] == 'u') ? 'd' : 'u';
    }
    else{
      solutionMoves[r][2] = (solutionMoves[r][2] == 'l') ? 'r' : 'l';
    }
  }
  for(int d = solutionMoves.size() - 1; d >= 0; d--) {
    try_move(solutionMoves[d]);
    result += "\n";
    result +=  "*** Move " + to_string(moveNum) + " (" + solutionMoves[d][0] + "," + solutionMoves[d][1] + "," + solutionMoves[d][2] + ")" + "\n";
    result += str();
    moveNum += 1;
  }
  return result;
}

bool Scrambler::is_over() {
  vector<string> completewords;
  vector<string> toCheck;
  string temp = "";

  for(int i = 0; i < board.size(); i++) {
    for(int j = 0; j < board[i].size(); j++) {
      if(board[i][j] != ' ') {
      temp += board[i][j];
      }else{
      completewords.push_back(temp);
      temp = "";
        }
    }

      completewords.push_back(temp);
      temp = "";
    }

    for(int a = 0; a < completewords.size(); a++) {
      for(int b = 0; b < wordUsed.size(); b++) {
        if(completewords[a] == wordUsed[b]) {
          toCheck.push_back(completewords[a]);
        }
      }
    }
  
    sort(toCheck.begin(), toCheck.end());
    sort(wordUsed.begin(), wordUsed.end());
    if(toCheck == wordUsed){
      return true;
    }
      return false;
  
  
}

void Scrambler::try_move(const string& cmd) {
if(cmd == "r" || cmd == "R") {
  board = initial_board;
}
 char rowColumn = cmd[0];
 int idx = (cmd[1] - '0') - 1;
 char dir = cmd[2];
 rowColumn = tolower(rowColumn);
 dir = tolower(dir);
 if(rowColumn == 'c') {
  if(dir == 'u') {
    shift_up(board, idx);
  } 
  else if(dir == 'd') {
    shift_down(board, idx);
  }
 }
 else if(rowColumn == 'r'){
   if(dir == 'r') {
     shift_right(board, idx);
   }
   else if (dir == 'l') {
     shift_left(board, idx);
   }
 }
}

vector<string> Scrambler::get_words() {
  vector<string> words;
  for(int i = 0; i < wordUsed.size(); i++) {
    words.push_back(wordUsed[i]);
  }
  return words;
}

string Scrambler::str() {
string result;
string word;
string sOfBoard;
string charOfword;
sOfBoard = "";
sOfBoard += "    ";
for(int b = 1; b <= size; b++) {
   if(b == size) {
      sOfBoard += to_string(b);
  }else {
      sOfBoard += to_string(b) + "   ";
  }
}
  result += sOfBoard + "\n";
  sOfBoard ="";
  sOfBoard += "   ";
  for(int r = 0; r < 4 * size; r++) {
      sOfBoard += "-";
    }
  result += sOfBoard + "\n";
  
  for(int i = 0; i < board.size(); i++) {
    word = board[i];
    sOfBoard = "";
    sOfBoard += to_string(i + 1) + " |";
    for(int j = 0; j < word.size(); j++) {
      charOfword = word[j];
      sOfBoard += " " + charOfword + " |";
    }
    result += sOfBoard + "\n";
    sOfBoard = "";
    sOfBoard += "   ";
    for(int r = 0; r < 4 * size; r++) {
      sOfBoard += "-";
    }
    if(i != board.size() -1)
{      result += sOfBoard + "\n";
} else{ result += sOfBoard;
  
}
  }
  
return result;

}
int main() {
  string result;
  string solution;
  bool gameStatus;
  vector<string> solutionMoves;
  int sizes;
  string move;
  // Must be 3-9
  cin >> sizes;
  Scrambler S("dictionary.txt", sizes);
  result = S.str();
  cout << result << endl; 
  solution = S.display_solution();
  solutionMoves = S.getSolutionMoves();
  cout << S.str() << endl;
  gameStatus = S.is_over();
  cout << gameStatus << endl;
  return 0;
}

   
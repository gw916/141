#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

const int NMISP = 5;
const int RNG_RANGE = 100;

void
display_header(const int ndict, const int nmiss)
// Prints out the header
{
  cout << "*** Typing Tutor" << endl;
  cout << "There are " << ndict << " words in the dictionary." << endl;
  cout << "There are " << nmiss << " commonly misspelled words." << endl;
    
    
}

void
display_menu_options()
{
    /* This function prints out all the menu options, it is
    given to you as part of the starter code. If you change
    it,  you run the  risk of failing  an early test of the
    autograder.*/

    cout << endl << "*** Select a menu option:" << endl
         << "1. Spell commonly misspelled words" << endl
         << "2. Type random words from the full dictionary" << endl
         << "3. Display some words from one of the lists" << endl
         << "4. Use binary search to lookup a word in the dictionary" << endl
         << "5. Exit the program." << endl
         << "Your choice: ";
}

vector<int>
randn(const int n, const int max)
{
/* This function creates and return a vector that has n random numbers drawn from between 0 and the value of the parameter max which is the size of the file used - 1. 
*/
  int i;
  int randnum;
  vector<int> numbers;
  for (i =0; i < n; ++i) {
    randnum = rand() % (max + 1);
    numbers.push_back(randnum);
  }
  return numbers;
}

ifstream
open(const string& src_file)
{
    ifstream src{src_file};
    if (!src.is_open()) {
        cout << "Could not find file " << src_file << "." << endl;
        exit(1);
    }
    return src;
}

void
extract_dict(vector<string>& dst, const string& src_file)
/*  Reads the data from the dictionary file,
    and store dictionary word in the empty vector dst.
*/
{
   string dictWord;
   fstream dictfile;
   dictfile.open(src_file);
   while (getline(dictfile, dictWord)) {
      dst.push_back(dictWord);
   }
}

void
extract_misspelled(vector<string>& misspelled, vector<string>& correct,
                    const string& src_file)
{
  /* Reads and Extracts the word pairs (misspelled, correct) from the misspelled file and stores them in their respective vectors.
*/
  string missWord;
  string correctWord;
  fstream missfile;
  missfile.open(src_file);
  while(!missfile.eof()) {
     missfile >> missWord;
     misspelled.push_back(missWord);
     missfile >> correctWord;
     correct.push_back(correctWord);
    }
  }

void
display_elems(const vector<string>& src, const vector<int>& positions)
{
  /* Using the vector that is created in the randn function. this  prints out the elements in the vector src only at those indices, with a space between each of the elements.
*/
  int i;
  int positnum;
  string word;
  for(i = 0; i < positions.size(); ++i) {
    positnum = positions[i];
    word = src[positnum];
    if(i != positions.size() - 1) {
       cout << word << ' ';
    }
    else {
      cout << word;
    }
  }
  cout << endl;
}

void
extract_spelling_answers(vector<string>& dst, const vector<string>& correct,
                            const vector<int> positions)
{
  /*  Copies the elements at the indices, in the positions vector, from the correct vector, into the vector dst.
*/
  int i;
  int positnum;
  string word;
  for(i = 0; i < positions.size(); ++i) {
    positnum = positions[i];
    word = correct[positnum];
    dst.push_back(word);
  }
}

void
extract_spelling_mistakes(vector<string>& dst, const string& to_grade,
                const vector<string>& correct)
{
  /*  Populates the vector dst everytime the user has a word mistake in to grade.
*/
vector<string> wordstoCheck;
int i;
int j;
string correction;
char element;
string wordtoCheck;
string grade1;
grade1 =  to_grade + " ";
for(i = 0; i < grade1.size(); ++i) {
  element = grade1.at(i);
       if(element != ' ') {
         wordtoCheck += element;
       }
       else {
         wordstoCheck.push_back(wordtoCheck);
          wordtoCheck = "";
        }
}
for(j = 0; j < wordstoCheck.size(); ++j) {
  if(wordstoCheck[j] != correct[j]) {
    correction = wordstoCheck[j] + " -> " + correct[j];
    dst.push_back(correction);
  }
}
}

void
report_misspell_mistakes(const vector<string>& mistakes,
                            const int num_words)
{
  /*  Prints out all the spelling mistakes in mistakes to the user. If mistakes is empty then No misspelled words! is printed.
  */
  int i;
  int correctScore, incorrectScore, totalScore, correctWords, incorrectWords;

  correctWords = num_words;
  incorrectWords = 0;
  
  if (mistakes.size() == 0) {
    cout << "No misspelled words!" << endl;
    
  }

  else {
    cout << "Misspelled words: " << endl;
    for(i = 0; i < mistakes.size(); ++i) {
      cout << "    " << mistakes[i] << endl;
      correctWords -= 1;
      incorrectWords += 1;
      }
  }

  correctScore = correctWords * 3;
  incorrectScore = incorrectWords * 6;

  cout << correctScore << " points: " << correctWords << " spelled correctly x 3 points for each." << endl;
  cout << incorrectScore << " point penalty: " << incorrectWords << " spelled incorrectly x -6 points for each." << endl;
  totalScore = correctScore - incorrectScore;
  cout << "Score: " << totalScore << endl;
  
}

void
evaluate_user_misspells(const vector<string>& src, const vector<int>& positions)
{
   /* Reads the userinput for the typing test, and reports
    back their performance. Which is done by calling the functions extract_spelling_answers, extract_spelling mistakes, and report_mispell_mistakes
   */
  string userInput;
  getline(cin, userInput);
  vector<string> mistakes;
  vector<string> answers;
  extract_spelling_answers(answers, src, positions);
  extract_spelling_mistakes(mistakes, userInput, answers);
  report_misspell_mistakes(mistakes, answers.size());
}

void
misspelled(const vector<string>& mspelled, const vector<string>& correct)
{
   /*  Does everything for option 1. First, it prints out the starting message for it. Then, it gets 5 random indexs for words in the mspelled vector and displays them. Lastly,it evaluates the users input.
*/
  vector<int> numbers;
  int positnum, i;
  string word;
  numbers = randn(NMISP, mspelled.size() - 1);
  cout << endl;
  cout << "*** Using commonly misspelled words." << endl;
  display_elems(mspelled , numbers);
  cout << "Type the words above with the correct spelling:" << endl;
  evaluate_user_misspells(correct , numbers);
   
}

void
full_dict(const vector<string>& dict)
{
    /*  Does everything for option 2. First, it prints out the starting message for it. Then, it gets 5 random indexs for words in the dict vector and displays them. Lastly,it evaluates the users input.
*/
  vector<int> numbers;
  int positnum, i;
  string word;
  numbers = randn(NMISP, dict.size() - 1);
  cout << endl;
  cout << "*** Using full dictionary." << endl;
  display_elems(dict , numbers);
  cout << "Correctly type the words above:" << endl;
  evaluate_user_misspells(dict , numbers);   
}

void
display_words_prompt()
{
    // This displays the data set choices for menu option 3
    cout << endl << "*** Displaying word list entries." << endl
         << "Which words do you want to display?" << endl
         << "A. Dictionary of all words" << endl
         << "B. Commonly misspelled words (wrongly spelled)" << endl
         << "C. Commonly misspelled words (correctly spelled)" << endl
         << "Your choice: ";
}

void
print_range(const vector<string>& data)
{
  /*  Reads the users chosen range, verify that the indices are in range, then print out the  words in the index range. 
 
Parameters:
        data -> a vector (string),  passed by reference, that cannot be
                modified (const), which holds the all the data (and the
                user will print some of it in a range)
*/
  int startRange;
  int endRange;
  cout << "*** Enter the start and end indices between 0 and " << data.size() - 1 << ": ";
  cin >> startRange;
  cin >> endRange;
  if ((startRange > endRange) || (startRange > (data.size() - 1)) || (endRange > (data.size() - 1))) {
    cout << "The end index must come after the start, and the indices must be in range." << endl;
  }

  else {
    for (int i = startRange; i <= endRange; ++i) {
      cout << i << ". " << data[i] << endl;
    }
  }
}

void
display_in_range(const vector<string>& dict, const vector<string>& mspelled,
                const vector<string>& correct)
{
   /*  Displays the initial messages for menu option 3, reads in
    the user's choice of dataset, and displays the data in range.
   
    Parameters:
        dict -> a vector (string),  passed by reference, that cannot be
                modified (const), which holds the all the data from the
                full dictionary

        mspelled -> a vector (string), passed by reference, that cannot
                    be modified (const),  which holds the all the miss-
                    pelled words

        correct -> a vector (string), passed by reference, that cannot
                   be modified (const),  which holds the all the words
                   with correct spelling
   */
  char choice;
  cout << endl;
  display_words_prompt();
  cin >> choice;
  if (choice == 'A' || choice == 'a') {
    print_range(dict);
  }
  else if (choice == 'B' || choice == 'b') {
    print_range(mspelled);
  }

  else if (choice == 'C' || choice == 'c') {
    print_range(correct);
  }
}

void
bsearch(const vector<string>& data)
{
  /* Reads in the word to search for, from the user, and runs the Binary Search Algorithm to search for the word. At every step of the algorithm, it prints out the current word,  that is being compared with the target.

    Parameters:
        data -> a vector (string),  passed by reference, that cannot be
                modified (const), which holds the all the data from the
                full dictionary
*/
  string wordtoSearch, currentWord;
  cout << "*** Enter word to search: ";
  cin >> wordtoSearch;
  int start = 0;
  int mid, count, size;
  count = 0;
  size = data.size();
    do {
        mid = (start + size) / 2;
        currentWord = data[mid];
        if (currentWord < wordtoSearch) {
          count += 1;
          start = mid + 1;
         if (count >= 10) {
          cout << "   " << count << ". Comparing to: " << currentWord  << endl;
          }
        else {
          cout << "    " << count << ". Comparing to: " << currentWord  << endl;
          }
          
        }
          else if (currentWord > wordtoSearch) {
            size = mid;
            count += 1;
          if (count >= 10) {
          cout << "   " << count << ". Comparing to: " << currentWord  << endl;
          }
        else {
          cout << "    " << count << ". Comparing to: " << currentWord  << endl;
          }
            size = mid;
          }
        else {
          count += 1;
        if (count >= 10) {
          cout << "   " << count << ". Comparing to: " << currentWord  << endl;
          }
        else {
          cout << "    " << count << ". Comparing to: " << currentWord  << endl;
          }
          cout << wordtoSearch << " was found." << endl;
          return;
      }
    } while (start < size);
  cout << wordtoSearch << " was NOT found." << endl;
          return;
}

void
extract_all_data(vector<string>& dict, vector<string>& mspelled,
                    vector<string>& correct)
{
    extract_dict(dict, "dictionary.txt");
    extract_misspelled(mspelled, correct, "misspelled.txt");
}

int
main()
{
    srand(1);
    vector<string> dict, mspelled, correct;
    extract_all_data(dict, mspelled, correct);
    display_header(dict.size(), correct.size());
    unsigned int choice;
    do {
        display_menu_options();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            misspelled(mspelled, correct);
            break;
        case 2:
            full_dict(dict);
            break;
        case 3:
            display_in_range(dict, mspelled, correct);
            break;
        case 4:
            bsearch(dict);
            break;
        case 5:
            cout << "Exiting." << endl;
            break;
        default:
            cout << "No menu option " << choice << ". "
                 << "Please try again." << endl;
        }
    } while ((choice != 5) && !cin.eof());

    return 0;
  
}
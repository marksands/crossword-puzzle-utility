#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "src/SearchableADT.hpp"
#include "src/Hash.hpp"

#include "src/Timer.hpp"

using namespace std;

enum MenuOptions {LOAD = 1, CHECK_ENTRY = 2, CHECK_SHRINK = 3, CLEAR = 4, QUIT = 5 };

int Menu();

void ReadFile( SearchableADT<string>*& dictionary );
void Clear( SearchableADT<string>*& dictionary );
void CheckEntry( SearchableADT<string>*& dictionary );
void CheckShrink( SearchableADT<string>*& dictionary );
void QuitProgram( SearchableADT<string>*& dictionary );

void SearchForWord( SearchableADT<string>*& dictionary, string word, int pos );
size_t CalculateShrinkability( SearchableADT<string>*& dictionary, string word, size_t length );


int main( int argc, char** argv )
{
  int choice = 0;
  SearchableADT<string>* dictionary = new Hash<string>;

  void (*menuTable[6])( SearchableADT<string>*& ) = { NULL, &ReadFile, &CheckEntry, &CheckShrink, &Clear, &QuitProgram };

  do {
    menuTable[ choice = Menu() ]( dictionary );
  } while( choice != 5 );

  return 0;
}

int Menu()
{
  int choice;

  cout << endl
     << setw(3) << LOAD << ". Load file"
     << endl
     << setw(3) << CHECK_ENTRY << ". Check spelling"
     << endl
     << setw(3) << CHECK_SHRINK << ". Check shrinkability"
     << endl
     << setw(3) << CLEAR << ". Clear data"
     << endl
     << setw(3) << QUIT << ". Quit"
     << endl
     << endl
     << setw(3) << " " << "Enter choice: ";
  cin >> choice;
  cout << endl;

  return (choice);
}

void ReadFile( SearchableADT<string>*& dictionary )
{
  Timer t;

  string filename;
  cout << setw(3) <<  " " << "Enter filename: ";
  cin >> filename;

  if ( !dictionary->LoadFromFile(filename) )
    cerr << setw(3) << " " << "File failed to load!" << endl;
}

void Clear( SearchableADT<string>*& dictionary )
{
  Timer t;
  
  dictionary->clear();
  cout << setw(3) << " " << "Dictionary cleared." << endl;
}

void CheckEntry( SearchableADT<string>*& dictionary )
{
  Timer t;

  string pattern;
  cout << setw(3) << " " << "Enter a word or pattern. Use '?' for wilcard: ";
  cin >> pattern;

  cout << endl
     << setw(3)  << " "
     << "Words found:" << endl;

  SearchForWord( dictionary, pattern, 0 );

  cout << endl;
}

void CheckShrink( SearchableADT<string>*& dictionary )
{
  Timer t;

  string word;
  cout << setw(3) << " " << "Enter a word to check its shrinkability index: ";
  cin >> word;

  cout << endl;
  cout << endl
      << setw(3) << " "
      << "Shrinkability index: "
      << CalculateShrinkability( dictionary, word, word.length() - 1 )
      << endl;

  cout << endl;
}

void QuitProgram( SearchableADT<string>*& dictionary )
{
  delete dictionary;
}

void SearchForWord( SearchableADT<string>*& dictionary, string word, int pos )
{
  string temp = word;
  int qpos = -1;

  for ( size_t i = pos; i < temp.size(); i++ )
  {
    if ( temp[i] == '?' )
    {
      qpos = i;
      for ( int i = 0; i < 26; i++ )
      {
        temp[qpos] = i + 97;
        SearchForWord( dictionary, temp, qpos );

        if ( dictionary->isThere( temp ) ) {
          cout << setw(5) << " " << temp << endl;
        }
      }
    }
  }
}

size_t CalculateShrinkability( SearchableADT<string>*& dictionary, string word, size_t length )
{
  try {
    string temp = word.substr( 0, length );
    if ( dictionary->isThere( temp ) ) {
      cout << setw(3) << " " << "\"" << word << "\"" << " => \"" << temp << "\"" << endl;
      return CalculateShrinkability( dictionary, temp, temp.length() - 1 );
    }
  } catch( std::out_of_range &e ) {
    return word.length();
  }

  try {
    string temp = word.substr( 1, length );
    if ( dictionary->isThere( temp ) ) {
      cout << setw(3) << " " << "\"" << word << "\"" << " => \"" << temp << "\"" << endl;
      return CalculateShrinkability( dictionary, temp, temp.length() - 1 );
    }
  } catch( std::out_of_range &e ) {
    return word.length();
  }

  cout << setw(3) << " " << "\"" << word << "\"" << endl;
  return word.length();
}
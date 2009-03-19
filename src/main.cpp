//   File: main.cpp
//   Name: Mark Sands
//   Date: 3/02/08
// Course: CS 340 - Data Structures and Algorithms
//   Desc: a SearchableADT class that creats a dictionary object inheriting either
//			a BST or an AVL tree which loads in dictionary files. Then the user is
//			able to search the tree for a partial word using '?' as a wildcard letter
//
//  Other files required: BST.h, AVL.h, SearchableADT.h 
//
//	* citations: Justin Camerer for the amazing Timer class idea
//------------------------------------------------------------------------------------------

#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>

#include "SearchableADT.h"
#include "BST.h"
#include "AVL.h"
#include "Timer.h"


using namespace std;

enum MenuOptions {LOAD = 1, CLEAR = 2, CHECK_ENTRY = 3, CHECK_FROM_FILE = 4, STATS = 5, QUIT = 6};
enum InitMenuOptions { BST_TREE = 1, AVL_TREE =  2};

int InitMenu();
int Menu();

void GetDS( SearchableADT<string>*& dictionary );

void ReadFile( SearchableADT<string>*& dictionary );
void Clear( SearchableADT<string>*& dictionary );
void CheckEntry( SearchableADT<string>*& dictionary );
void CheckEntryFromFile( SearchableADT<string>*& dictionary );
void ShowStats( SearchableADT<string>*& dictionary );
void QuitProgram( SearchableADT<string>*& dictionary );

void SearchForWord( SearchableADT<string>*& dictionary, string word );
void SearchForWord( SearchableADT<string>*& dictionary, string word, int pos  );


int main( int argc, char* argv[] )
{
	int choice = 0;
	
	SearchableADT<string>* dictionary;
	GetDS( dictionary );
	
		
	// LUT of function pointers
	void (*menuTable[7])( SearchableADT<string>*& ) = { 
			NULL, &ReadFile, &Clear, &CheckEntry, &CheckEntryFromFile, &ShowStats, &QuitProgram };
	
	do {
		menuTable[ choice = Menu() ]( dictionary );
	} while ( choice != 6 );
	
	return 0;
}



int InitMenu()
{
	int choice;

	cout << endl
		 << setw(3) << BST_TREE << ". Use a BST"
		 << endl
		 << setw(3) << AVL_TREE << ". Use an AVL"
		 << endl
		 << endl
		 << setw(3) << " " << "Enter choice: ";
	cin >> choice;

	return (choice);
}


int Menu()
{
	int choice;

	cout << endl
		 << setw(3) << LOAD << ". Load dictionary file into tree"
		 << endl
		 << setw(3) << CLEAR << ". Clear tree"
		 << endl
		 << setw(3) << CHECK_ENTRY << ". Check for entry"
		 << endl
		 << setw(3) << CHECK_FROM_FILE << ". Check for entry from file"
		 << endl
		 << setw(3) << STATS << ". Report tree statistics"
		 << endl
		 << setw(3) << QUIT << ". Quit"
		 << endl
		 << endl
		 << setw(3) << " " << "Enter choice: ";
	cin >> choice;
	cout << endl;
	
	return (choice);
}

void GetDS( SearchableADT<string>*& dictionary  )
{
	int choice = 0;
	
	do {
		switch ( choice = InitMenu() ) {
			case BST_TREE:
				dictionary = new BST<string>;
				break;
			case AVL_TREE:
				dictionary = new AVL<string>;
				break;
			default:
			dictionary = new AVL<string>;
		}
	} while( choice == 0);	
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
	cout << setw(3) << " " << "Tree cleared." << endl;
}

void CheckEntry( SearchableADT<string>*& dictionary )
{
	Timer t;

	string pattern;
	cout << setw(3) << " " << "Enter a word or pattern. Use '?' for wilcard: ";
	cin >> pattern;

	cout << endl
		 << setw(3)  << " "
		 << "Words:" << endl;

	//SearchForWord( dictionary, pattern );
	SearchForWord( dictionary, pattern, 0 );

	cout << endl;
}

void CheckEntryFromFile( SearchableADT<string>*& dictionary )
{
	Timer t;

	string filename, word;
	cout << setw(3) << " " << "Enter filename: ";
	cin >> filename;

	ifstream fin( filename.c_str() );
	if ( fin.fail() ) {
		cerr << "File failed to load!" << endl;
		return;
	}
	else {
		while ( !fin.eof() ) {
			fin >> word;
			SearchForWord( dictionary, word );
		}
	}
}

void ShowStats( SearchableADT<string>*& dictionary )
{
	Timer t;
		
	cout << setw(3) << " " << "Number of entries: "
		 << dictionary->numEntries() << endl;
	
	cout << setw(3) << " " << "Tree height: "
		 << dictionary->treeHeight() << endl;
}

void QuitProgram( SearchableADT<string>*& dictionary )
{
	delete dictionary;
}

void SearchForWord( SearchableADT<string>*& dictionary, string word )
{
	int pos = -1;
	string temp = word;
	// find the position of the wildcard
	for ( size_t j = 0; j < temp.size(); j++ ) {
		if ( temp[j] == '?' ) pos = j;
	}

	// check every value for the pattern
	if ( pos > -1 ) {
		for ( int i = 0; i < 26; i++ ) {
			temp[pos] = i + 97;
			if ( dictionary->isThere( temp ) ) {
				cout << setw(5) << " " << temp << endl;
			}
		}
	}
	else if ( dictionary->isThere( temp ) ) {
		cout << setw(5) << " "
			 << "Word: " << temp << " was found in the file. "
			 << endl;
	}
	else {
		cout << setw(3) << " "
			 << "Word appears to be mispelled."
			 << endl;
	}
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


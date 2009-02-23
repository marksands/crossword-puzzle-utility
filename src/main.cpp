//   File: main.cpp
//   Name: Mark Sands
//   Date: 3/02/08
// Course: CS 340 - Data Structures and Algorithms
//   Desc: 
//
//         Other files required: BST.h, AVL.h, SearchableADT.h 
//------------------------------------------------------------------------------------------

#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>

#include "BST.h"
#include "AVL.h"
#include "SearchableADT.h"


using namespace bst;
using namespace avl;
using namespace std;

enum MenuOptions {LOAD = 1, CLEAR = 2, CHECK_ENTRY = 3, CHECK_FROM_FILE = 4, STATS = 5, QUIT = 6};
enum InitMenuOptions { BST_TREE = 1, AVL_TREE =  2};

void Display(const string& item);

int InitMenu();
int Menu();

void ReadFile( SearchableADT<string>*& dictionary );
void Clear( SearchableADT<string>*& dictionary );
void CheckEntry( SearchableADT<string>*& dictionary );
void CheckEntryFromFile( SearchableADT<string>*& dictionary );
void ShowStats( SearchableADT<string>*& dictionary );


int main( int argc, char* argv[] )
{
	clock_t start, finish;
	start = clock();
	
	
	int choice = 0;
	SearchableADT<string>* dictionary;

	// determine BST or AVL
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
	
	
	// present menu of choices
	do {
		switch ( choice = Menu() ) {
			case LOAD:
				ReadFile(  dictionary );
				break;

			case CLEAR:
				Clear( dictionary );
				break;

			case CHECK_ENTRY:
				CheckEntry(  dictionary );
				break;

			case CHECK_FROM_FILE:
				CheckEntryFromFile( dictionary );
				break;

			case STATS:
				ShowStats(  dictionary );
				cout << endl << endl;
				break;
		}
	} while(choice != QUIT);
	
	
	delete dictionary;	
	
	
	
	finish = clock();
	
	cout << "time: "
		 << ((double)(finish - start)/CLOCKS_PER_SEC)
		 << endl;
}



void Display(const string& item)
{
	cout << item << endl;
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


void ReadFile( SearchableADT<string>*& dictionary )
{
	clock_t finish, start = clock();
	
	string filename;
	cout << setw(3) <<  " " << "Enter filename: ";
	cin >> filename;
	
	if ( !dictionary->LoadFromFile(filename) )
		cerr << setw(3) << " " << "File failed to load!" << endl;
		
	finish = clock();
	cout << setw(5) << " " << "Total time: "
		 << ( (double) (finish - start)/CLOCKS_PER_SEC )
		 << endl;
}
	

void Clear( SearchableADT<string>*& dictionary )
{
	clock_t finish, start = clock();
	
	dictionary->clear();
	cout << setw(3) << " " << "Tree cleared." << endl;
	
	finish = clock();
	cout << setw(5) << " " << "Total time: "
		 << ( (double) (finish - start)/CLOCKS_PER_SEC )
		 << endl;
}

void CheckEntry( SearchableADT<string>*& dictionary )
{
	clock_t finish, start = clock();
	
	string pattern;
	cout << setw(3) << " " << "Enter a word or pattern. Use '?' for wilcard: ";
	cin >> pattern;

	cout << endl
		 << setw(3)  << " "
		 << "Words:" << endl;

	int pos = 0;
	string temp = pattern;
	// find the position of the wildcard
	for ( size_t j = 0; j < temp.size(); j++ ) {
		if ( temp[j] == '?' ) pos = j;
	}

	// check every value for the pattern
	for ( int i = 0; i < 26; i++ ) {
		temp[pos] = i + 97;
		if ( dictionary->isThere( temp ) ) {
			cout << setw(5) << " " << temp << endl;
		}
	}

	cout << endl;

	finish = clock();
	cout << setw(5) << " " << "Total time: "
		 << ( (double) (finish - start)/CLOCKS_PER_SEC )
		 << endl;
}

void CheckEntryFromFile( SearchableADT<string>*& dictionary )
{
	clock_t finish, start = clock();
	
	string filename;
	cout << setw(3) << " " << "Enter filename: ";
	cin >> filename;
	
	// search file
	finish = clock();
	cout << setw(5) << " " << "Total time: "
		 << ( (double) (finish - start)/CLOCKS_PER_SEC )
		 << endl;
}

void ShowStats( SearchableADT<string>*& dictionary )
{
	clock_t finish, start = clock();
		
	cout << setw(3) << " " << "Number of entries: "
		 << dictionary->numEntries() << endl;
		
	finish = clock();
	cout << setw(5) << " " << "Total time: "
		 << ( (double) (finish - start)/CLOCKS_PER_SEC )
		 << endl;
}

#ifndef SEARCHABLE_ADT_H
#define SEARCHABLE_ADT_H

#include <iostream>
#include <string>

using namespace std;

template <class T>
class SearchableADT {
  public:
	virtual ~SearchableADT() { }
	
	virtual int LoadFromFile(string filename) = 0;
	virtual void clear(void) = 0;
	virtual void insertEntry(T value) = 0;
	virtual void deleteEntry(T value) = 0;
	virtual bool isThere(T value) = 0;
	virtual int numEntries(void) = 0; 
};


#endif

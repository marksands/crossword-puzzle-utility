#ifndef HASH_H
#define HASH_H

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

  //---------------------------------------------------------------------------------------------------
  // Class: Hash
  //---------------------------------------------------------------------------------------------------
  template<class T>
  class Hash : public SearchableADT<T>
  {
  private:  
        
    int size;
      // holds curent size;
    int numberOfItems;
      //holds mumber of items
      
    enum EntryType { ACTIVE, EMPTY, DELETED };
    
      // struct HashNode stores the item and lazy deletion information
    struct HashNode {
      T element;
      EntryType info;
      
      HashNode( const T& e = T(), EntryType i = EMPTY ) : element(e), info(i)
      { }
    };  
      
      // vector array of HashNode
    vector<HashNode> array; 
            
    virtual int hash(T value) const;
      // finds the hashvalue of the item : 1st hash
    virtual int hash2(T value) const;
      // finds the hashvalue of the item : 2nd hash
    virtual bool IsActive(int pos) const; 
      // returns true if the position is occupied 
        
    virtual void rehash();
      // rehashes the hash table to double its size
      
    void Empty();
      // erases the hash table
    bool Insert( const T& value );
      // inserts value into the hash table
    bool Remove( const T& value );
      // removes a value from the hash table

  public:
    Hash( int size = 101 );
      // Sets the root to NULL;
    virtual ~Hash();
      // Calls DestroyTree() to destroy the current tree.

    virtual int LoadFromFile(string filename);
      // loads from file
    virtual void clear(void);
      // clears tree
    virtual void insertEntry(T value);
      // inserts entry 'value'
    virtual void deleteEntry(T value);
      // deletes entry 'value'
    virtual bool isThere(T value);
      // boolean is there?
    virtual int numEntries(void); 
      // number of entries
      
    virtual int treeHeight(void);
      // returns the height of the tree; Doesn't apply to this.
  };

#pragma mark -
#pragma mark Private

      //***********************************
      //  
      //    Private Methods
      //
      //***********************************


      // erases the hash table
    template <class T>  
    void Hash<T>::Empty()
    {
      for ( int i = 0; i < array.size(); i++ )
        array[i].info = EMPTY;

      numberOfItems = 0;
    }

#pragma mark -
#pragma mark Hash Algorithms

      // finds the hashvalue of the item : 1st hash
    template <class T>
    int Hash<T>::hash( T value ) const
    {
      unsigned int hash = 5381;
      
      for(int i = 0; i < value.length(); i++)
        hash = ((hash << 5) + hash) + value[i];

      return hash;
    }


      // finds the hashvalue of the item  : 2nd hash  
    template <class T>
    int Hash<T>::hash2( T value ) const
    {
      unsigned int hash = 773;

      for( int i = 0; i < value.length(); i++)
        hash = ((hash << 3) + hash) + 1 + value[i];

      return hash;
    }


      // rehashes the hash table to double its size
    template <class T>
    void Hash<T>::rehash()
    {
      vector<HashNode> oldArray = array;
      
      array.resize( 2 * oldArray.size() + 1 );
      for ( int i = 0; i < array.size(); i++ ) {
        array[i].info = EMPTY;
      }
      
      size = ( size * 2 ) + 1;
      
      for ( int i = 0; i < oldArray.size(); i++ ) {
        if ( oldArray[i].info == ACTIVE ) {
          Insert( oldArray[i].element );
        }
      }
      
    }

#pragma mark -
#pragma mark Standard

      // returns true if the position is occupied
    template <class T>
    bool Hash<T>::IsActive(int pos) const
    {
      return ( array[pos].info == ACTIVE );
    }


      // inserts value into the hash table
    template <class T>
    bool Hash<T>::Insert( const T& value )
    {
      if ( numberOfItems != 0 ) 
        if ( (double)numberOfItems/(double)size > 0.6 )
          rehash();

      HashNode newNode(value, ACTIVE);
        
      bool flag = false;
      bool endfor = true;

      int h1 = hash(value);
      int h2 = hash2(value);  
        
      for ( int i = 1; endfor; i++)
      {
        int pos = abs((h1 + i*h2) % size);

        if ( !IsActive( pos ) )
        {
          array[ pos ] = newNode;
          numberOfItems++;
          endfor = false;
          flag = true;
        } else if ( array[ pos ].element == newNode.element ) {
          endfor = false;
          flag = true;
        }
      }
            
      return ( flag );
    }

      // removes a value from the hash table
    template <class T>
    bool Hash<T>::Remove( const T& value )
    {
      bool flag = true;
      int pos = hash( value );

      if ( IsActive(pos) )
      {
        array[pos].info = DELETED;
        numberOfItems--;
      }
      else {
        flag = false;
      }

      return ( flag );
    }

#pragma mark -
#pragma mark Public


      //***********************************
      //  
      //    Public Methods
      //
      //***********************************


  template <class T>
  Hash<T>::Hash( int size ) : size(size)
  {
    array.resize(size);
    Empty();
  }

  template <class T>
  Hash<T>::~Hash()
  {
    Empty();
  }


#pragma mark -
#pragma mark Inherited

      //***********************************
      //
      //    Inherited Methods
      //
      //***********************************


    // loads from file
  template <class T>
  int Hash<T>::LoadFromFile(string filename)
  {
    int RET = 1;
    ifstream fin( filename.c_str() );
    T item;

    if ( fin.fail() ) {
      RET = 0;
    }
    else {
      while ( !fin.eof() ) {
        fin >> item;
        insertEntry( item );
      }

      fin.clear();
      fin.close();
    }

    return RET; 
  }

    // clears tree  
  template <class T>
  void Hash<T>::clear(void)
  {
    Empty();
  }

    // inserts entry 'value'
  template <class T>
  void Hash<T>::insertEntry(T value)
  {
    if ( Insert( value ) );
  }

    // deletes entry 'value'
  template <class T>
  void Hash<T>::deleteEntry(T value)
  {
    if ( Remove( value ) );
  }

    // boolean is there?
  template <class T>
  bool Hash<T>::isThere(T value)
  {
    int h1 = hash(value);
    int h2 = hash2(value);

    if ( numberOfItems == 0 ) return false;

    for ( int i = 1; ; i++) {
      int pos = abs( (h1 + (i*h2)) % size );

      if ( !IsActive( pos ) )
        return false;
      else if ( array[ pos ].element == value && array[ pos ].info == ACTIVE )
        return true;
    }
  }

    // number of entries
  template <class T>
  int Hash<T>::numEntries(void)
  {
    return ( numberOfItems );
  }

    // returns 0, since this isn't a tree..
  template <class T>
  int Hash<T>::treeHeight(void)
  {
    return -1;
  }

#endif
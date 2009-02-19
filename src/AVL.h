#ifndef AVL_H
#define AVL_H

#include <string>
#include <iostream>
#include <fstream>
#include "BST.h"

using namespace std;

namespace avl
{	
	template<class T> class AVL;
	
	//---------------------------------------------------------------------------------------------------
	// Class: TreeNode
	//---------------------------------------------------------------------------------------------------
	template<class T>
	class TreeNode
	{
	private:
		friend class AVL<T>;

		T item;
		int balance;
		TreeNode<T>* left;
		TreeNode<T>* right;

	public:
		TreeNode<T>(const T& item, TreeNode<T>* left, TreeNode<T>* right);
			// Sets the fields to the supplied parameters.
	};

	//---------------------------------------------------------------------------------------------------
	// Class: AVL
	//---------------------------------------------------------------------------------------------------
	template<class T>
  class AVL : public ::bst::BST<T>
	{
	private:
		TreeNode<T>* root;
			// THE root node
		int nodeCount;
			// keeps a running count of the number of nodes

		TreeNode<T>* InsertNode(TreeNode<T>*& pTree, const T& item);
			// Inserts the item into the tree.
		void RemoveNode(TreeNode<T>*& pTree);
			// Removes the actual node from the tree.
		void Remove(TreeNode<T>*& pTree, const T item);
			// Finds the node containing the item or gives error message if value not found.
			// Once found calls RemoveNode to remove it.
		void ProcessLeftMost(TreeNode<T>*& pTree, T& replacementItem);
			// Finds the left most node on the right subtree to replace the node to be removed.
		void DestroyTree(TreeNode<T>*& pTree);
			// Destroys the AVL tree.
		void CopyTree(TreeNode<T>* pFromTree, TreeNode<T>*& pToTree);
			// Performs a preorder copy of the current tree to create a new one.
		bool isThere(TreeNode<T>* pTree, const T& item);
			// returns true if the item is found in the tree, false otherwise
			
		TreeNode<T>* SingleRightRotation( TreeNode<T>* pTree );
			// performs a single right rotation on the tree
		TreeNode<T>* SingleLeftRotation( TreeNode<T>* pTree );
			// performs a single left rotation on the tree
		TreeNode<T>* DoubleRightLeftRotation( TreeNode<T>* pTree );
			// performs a double right left rotation on the tree
		TreeNode<T>* DoubleLeftRightRotation( TreeNode<T>* pTree );
			// performs a double left right rotatoin on the tree
			
		int Height( TreeNode<T>* pTree );
			// returns the balance of the tree, if NULL returns -1
            

	public:
		AVL();
			// Sets the root to NULL;
		AVL(const AVL& tree);
			// Calls CopyTree() to make a copy of the current tree.
		~AVL();
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
	};

}

#include "AVL.cpp"

#endif

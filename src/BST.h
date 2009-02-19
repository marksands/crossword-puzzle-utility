#ifndef BST_H
#define BST_H

#include <string>
#include <iostream>
#include <fstream>
#include "SearchableADT.h"

using namespace std;

namespace bst
{	
	template<class T> class BST;
	
	//---------------------------------------------------------------------------------------------------
	// Class: TreeNode
	//---------------------------------------------------------------------------------------------------
	template<class T>
	class TreeNode
	{
	private:
		friend class BST<T>;

		T item;
		TreeNode<T>* left;
		TreeNode<T>* right;

	public:
		TreeNode<T>(const T& item, TreeNode<T>* left, TreeNode<T>* right);
			// Sets the fields to the supplied parameters.
	};

	//---------------------------------------------------------------------------------------------------
	// Class: BST
	//---------------------------------------------------------------------------------------------------
	template<class T>
	class BST : public ::SearchableADT<T>
	{
	private:
		TreeNode<T>* root;
			// THE root node
		int nodeCount;
			// keeps a running count of the number of nodes

	protected:
		virtual void InsertNode(TreeNode<T>*& pTree, const T& item);
			// Inserts the item into the tree.
		virtual void RemoveNode(TreeNode<T>*& pTree);
			// Removes the actual node from the tree.
		virtual void Remove(TreeNode<T>*& pTree, const T item);
			// Finds the node containing the item or gives error message if value not found.
			// Once found calls RemoveNode to remove it.
		void ProcessLeftMost(TreeNode<T>*& pTree, T& replacementItem);
			// Finds the left most node on the right subtree to replace the node to be removed.
		void Preorder(TreeNode<T>* pTree, void(*visit)(const T& item));
			// Performs a preorder traversal and executes the function visit upon root visitation.
		void Inorder(TreeNode<T>* pTree, void(*visit)(const T& item));
			// Performs an inorder traversal and executes the function visit upon root visitation.
		void Postorder(TreeNode<T>* pTree, void(*visit)(const T& item));
			// Performs a postorder traversal and executes the function visit upon root visitation.
		void DestroyTree(TreeNode<T>*& pTree);
			// Destroys the bst tree.
		void CopyTree(TreeNode<T>* pFromTree, TreeNode<T>*& pToTree);
			// Performs a preorder copy of the current tree to create a new one.
		bool isThere(TreeNode<T>* pTree, const T& item);
			// returns true if the item is found in the tree, false otherwise

	public:
		BST();
			// Sets the root to NULL;
		BST(const BST& tree);
			// Calls CopyTree() to make a copy of the current tree.
		virtual ~BST();
			// Calls DestroyTree() to destroy the current tree.
		void PreorderTraversal(  void (*visit)(const T& item) );
			// Calls Preorder() to perform a preorder traversal of the tree.
		void InorderTraversal(   void (*visit)(const T& item) );
			// Calls Inorder() to perform an inorder traversal of the tree.
		void PostorderTraversal( void (*visit)(const T& item) );
			// Calls Postorder() to perform a postorder traversal of the tree.
				
		int LoadFromFile(string filename);
			// loads from file
		void clear(void);
			// clears tree
		virtual void insertEntry(T value);
			// inserts entry 'value'
		void deleteEntry(T value);
			// deletes entry 'value'
		bool isThere(T value);
			// boolean is there?
		int numEntries(void);	
			// number of entries
	};
	
}

#include "BST.cpp"

#endif

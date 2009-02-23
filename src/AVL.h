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

	protected:
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
			
				
		TreeNode<T>* SingleRightRotation( TreeNode<T>*& pTree );
			// performs a single right rotation on the tree
		TreeNode<T>* SingleLeftRotation( TreeNode<T>*& pTree );
			// performs a single left rotation on the tree
		TreeNode<T>* DoubleRightLeftRotation( TreeNode<T>*& pTree );
			// performs a double right left rotation on the tree
		TreeNode<T>* DoubleLeftRightRotation( TreeNode<T>*& pTree );
			// performs a double left right rotation on the tree
			
		int Height( TreeNode<T>*& pTree );
			// returns the balance of the tree, if NULL returns -1
            

	public:
		AVL();
			// Sets the root to NULL;
		AVL(const AVL& tree);
			// Calls CopyTree() to make a copy of the current tree.
		~AVL();
			// Calls DestroyTree() to destroy the current tree.
			
		//virtual int LoadFromFile(string filename);
			// loads from file
		//virtual void clear(void);
			// clears tree
		virtual void insertEntry(T value);
			// inserts entry 'value'
		//virtual void deleteEntry(T value);
			// deletes entry 'value'
		//virtual bool isThere(T value);
			// boolean is there?
		//virtual int numEntries(void);	
			// number of entries
	};
	
	
		//---------------------------------------------------------------------------------------------------
		// Class: TreeNode
		//---------------------------------------------------------------------------------------------------

			template <class T>
			TreeNode<T>::TreeNode(const T& item, TreeNode<T>* left, TreeNode<T>* right)
				: item(item), left(left), right(right), balance(0)
			{ }

		//---------------------------------------------------------------------------------------------------
		// Class: AVL
		//---------------------------------------------------------------------------------------------------

			template <class T>
			TreeNode<T>* AVL<T>::InsertNode(TreeNode<T>*& pTree, const T& item)
			{
				if ( item < pTree->item ) {

						pTree->left = InsertNode( pTree->left , item );

		        int balance = Height( pTree->left ) - Height( pTree->right );

		        if ( balance == 2 ) {
							if ( item < pTree->left->item )
								pTree = SingleRightRotation( pTree );
							else
								pTree = DoubleLeftRightRotation( pTree );
		        }
		    }
				else if ( item >= pTree->item ) {

		                pTree->right = InsertNode( pTree->right, item );

		                int balance = Height( pTree->right ) - Height( pTree->left );

		                if ( balance == 2 ) {
							if ( item >= pTree->right->item )
								pTree = SingleLeftRotation( pTree );
							else
								pTree = DoubleRightLeftRotation( pTree );
		                }
		        }
				else {

						pTree = new TreeNode<T>( item, NULL, NULL );
						nodeCount++;
				}


		    int height = Height( pTree->left ) >= Height( pTree->right ) ?
											Height( pTree->left ) : Height( pTree->right );
		    pTree->balance = height + 1;

				return pTree;

			}




			template <class T>
			void AVL<T>::Remove(TreeNode<T>*& pTree, const T item)
			{
				if ( pTree != NULL )
				{
					if ( item == pTree->item )
						RemoveNode(pTree);
					else if ( item < pTree->item )
						Remove(pTree->left, item);
					else if ( item >= pTree->item )
						Remove(pTree->right, item);
				}
				else {
					cerr << "Error: " << item << " not found." << endl;
				}
			}	



			template <class T>
			void AVL<T>::RemoveNode(TreeNode<T>*& pTree)
			{
				if ( pTree->right == NULL && pTree->left == NULL )
				{
					delete pTree;
					pTree = NULL;

					nodeCount--;
				}
				else if ( pTree->right == NULL || pTree->left == NULL )
				{
					TreeNode<T>* delPtr = pTree;
					if ( pTree->right == NULL )
						pTree = pTree->left;
					else
						pTree = pTree->right;
					delete delPtr;
					nodeCount--;
				}
				else {
					T replacementItem = pTree->item;
					ProcessLeftMost(pTree->left, replacementItem);
					pTree->item = replacementItem;
				}
			}
			

			template <class T>
			void AVL<T>::ProcessLeftMost(TreeNode<T>*& pTree, T& replacementItem)
			{
				TreeNode<T>* delPtr;

				if ( pTree->left == NULL )
				{
					replacementItem = pTree->item;
					delPtr = pTree;
					pTree = pTree->right;
					delete delPtr;
					nodeCount--;
				}	
				else {
					ProcessLeftMost(pTree->left, replacementItem);
				}

			}


			template <class T>
			void AVL<T>::DestroyTree(TreeNode<T>*& pTree)
			{
				while ( pTree != NULL )
					RemoveNode(pTree);
			}


			template <class T>
			TreeNode<T>* AVL<T>::SingleRightRotation( TreeNode<T>*& pTree)
			{
				TreeNode<T>* temp = NULL;

				if (pTree != NULL)
			    {
			        temp = pTree->left;
			        pTree->left = temp->right;
			        pTree->right = pTree;

			        int balance =  Height( pTree->left ) >= Height( pTree->right ) ?
									Height( pTree->left ) : Height( pTree->right);
			        pTree->balance = balance + 1;

					balance = Height( temp->left ) >= Height( pTree ) ?
							   Height( temp->left ) : Height( pTree );
			        temp->balance = balance + 1;
				}

				return temp;
			}

			template <class T>		
	        TreeNode<T>* AVL<T>::SingleLeftRotation( TreeNode<T>*& pTree)
			{
				TreeNode<T>* temp = NULL;

				if ( pTree != NULL )
				{
							temp = pTree->right;
			        pTree->right = temp->left;
			        pTree->left = temp;

			        int balance = Height( pTree->left ) >= Height( pTree->right ) ?
									Height( pTree->left ) : Height( pTree->right );
			        pTree->balance = balance + 1;

			        balance = Height( temp->right ) >= Height( pTree ) ?
								Height( temp->right ) : Height( pTree );
			        temp->balance = balance + 1;

				}

				return temp;
			}

			template <class T>
	        TreeNode<T>* AVL<T>::DoubleRightLeftRotation( TreeNode<T>*& pTree)
			{
				TreeNode<T>* temp = NULL;
				if ( pTree == NULL )
				{
			        pTree->right = SingleRightRotation( pTree->right );
					temp = SingleLeftRotation( pTree );
				 }

				return temp;   
			}

			template <class T>
	        TreeNode<T>* AVL<T>::DoubleLeftRightRotation( TreeNode<T>*& pTree)
			{
				TreeNode<T>* temp = NULL;
				if ( pTree == NULL )
				{
			        pTree->left = SingleLeftRotation( pTree->left );
					temp = SingleRightRotation( pTree );
				 }

				return temp;	
			}


			template <class T>
			int AVL<T>::Height( TreeNode<T>*& pTree )
			{
				int height = -1;

				if ( pTree != NULL ) {
					height = pTree->balance;
				}

				return ( height );
			}


	// *******************************
	//
	//		 PUBLIC
	//
	// *******************************


			template <class T>
			AVL<T>::AVL() : root(NULL)
			{ }



			template <class T>
			AVL<T>::AVL(const AVL<T>& tree)
			{
				CopyTree(tree.root, root);
			}


			template <class T>
			AVL<T>::~AVL()
			{
				DestroyTree(root);
			}




		//***********************************
		//	
		// 		Inherited Methods
		//
		//***********************************


			template <class T>
			void AVL<T>::insertEntry(T value)
			{
				root = InsertNode(root, value);
			}

}

//#include "AVL.cpp"

#endif

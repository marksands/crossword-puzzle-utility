#ifndef AVL_H
#define AVL_H

#include <string>
#include <iostream>
#include <fstream>
#include "BST.h"

using namespace std;

	//---------------------------------------------------------------------------------------------------
	// Class: AVL
	//---------------------------------------------------------------------------------------------------
	template<class T>
	class AVL : public BST<T>
	{
	private:
		TreeNode<T>* root;
			// THE root node
		int nodeCount;
			// keeps a running count of the number of nodes

	protected:
		void InsertNode(TreeNode<T>*& pTree, const T& item);
			// Inserts the item into the tree.
		void RemoveNode(TreeNode<T>*& pTree);
			// Removes the actual node from the tree.
		void Remove(TreeNode<T>*& pTree, const T item);
			// Finds the node containing the item or gives error message if value not found.
			// Once found calls RemoveNode to remove it.
		void ProcessLeftMost(TreeNode<T>*& pTree, T& replacementItem);
			// Finds the left most node on the right subtree to replace the node to be removed.

		void SingleRightRotation( TreeNode<T>*& pTree );
			// performs a single right rotation on the tree
		void SingleLeftRotation( TreeNode<T>*& pTree );
			// performs a single left rotation on the tree
		void DoubleRightLeftRotation( TreeNode<T>*& pTree );
			// performs a double right left rotation on the tree
		void DoubleLeftRightRotation( TreeNode<T>*& pTree );
			// performs a double left right rotation on the tree
			
		int Height( TreeNode<T>*& pTree );
			// returns the balance of the tree, if NULL returns -1
		int numEntries(void);	
			// number of entries
            
	public:
		AVL();
			// Sets the root to NULL;
		AVL(const AVL& tree);
			// Calls CopyTree() to make a copy of the current tree.
		~AVL();
			// Calls DestroyTree() to destroy the current tree.
	};

		//---------------------------------------------------------------------------------------------------
		// Class: AVL
		//---------------------------------------------------------------------------------------------------

			template <class T>
			void AVL<T>::InsertNode(TreeNode<T>*& pTree, const T& item)
			{
				if ( pTree == NULL )
				{
					pTree = new TreeNode<T>( item, NULL, NULL );
					nodeCount++;
				}
				else if ( item < pTree->item ) {

					InsertNode( pTree->left , item );

					int balance = Height( pTree->left ) - Height( pTree->right );
					if ( balance == 2 ) {
						if ( item < pTree->left->item )
							SingleRightRotation( pTree );
						else
							DoubleRightLeftRotation( pTree );
					}
				}
				else if ( item > pTree->item ) {
					
					InsertNode( pTree->right, item );

					int balance = Height( pTree->right ) - Height( pTree->left );
					if ( balance == 2 ) {
						if ( item > pTree->right->item )
							SingleLeftRotation( pTree );
						else
							DoubleLeftRightRotation( pTree );
					}
		        }


				int height = Height( pTree->left ) >= Height( pTree->right ) ?
											Height( pTree->left ) : Height( pTree->right );

				pTree->height = height + 1;
			}



			template <class T>
			void AVL<T>::SingleRightRotation( TreeNode<T>*& pTree)
			{
				TreeNode<T>* temp = NULL;

				if (pTree != NULL)
			    {
			        temp = pTree->left;
			        pTree->left = temp->right;
					temp->right = pTree;

			        int height =  Height( pTree->left ) >= Height( pTree->right ) ?
									Height( pTree->left ) : Height( pTree->right);
			        pTree->height = height + 1;

					height = Height( temp->left ) >= Height( pTree ) ?
							   Height( temp->left ) : Height( pTree );
			        temp->height = height + 1;

					pTree = temp;
				}
			}

			template <class T>		
	        void AVL<T>::SingleLeftRotation( TreeNode<T>*& pTree)
			{
				TreeNode<T>* temp = NULL;

				if ( pTree != NULL )
				{
					temp = pTree->right;
			        pTree->right = temp->left;
					temp->left = pTree;

			        int height = Height( pTree->left ) >= Height( pTree->right ) ?
									Height( pTree->left ) : Height( pTree->right );
			        pTree->height = height + 1;

			        height = Height( temp->right ) >= Height( pTree ) ?
								Height( temp->right ) : Height( pTree );
			        temp->height = height + 1;
					
					pTree = temp;
				}
			}

			template <class T>
	        void AVL<T>::DoubleRightLeftRotation( TreeNode<T>*& pTree)
			{
				if ( pTree != NULL )
				{
			        SingleLeftRotation( pTree->left );
					SingleRightRotation( pTree );
				} 
			}

			template <class T>
	        void AVL<T>::DoubleLeftRightRotation( TreeNode<T>*& pTree)
			{
				if ( pTree != NULL )
				{
			        SingleRightRotation( pTree->right );
					SingleLeftRotation( pTree );
				}
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
			int AVL<T>::Height( TreeNode<T>*& pTree )
			{
				return ( pTree == NULL ? -1 : pTree->height );
			}
			
			template <class T>
			int AVL<T>::numEntries(void)
			{
				return ( nodeCount );
			}


	// *******************************
	//
	//		 PUBLIC
	//
	// *******************************


			template <class T>
			AVL<T>::AVL() : root(NULL), nodeCount(0)
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

//#include "AVL.cpp"

#endif

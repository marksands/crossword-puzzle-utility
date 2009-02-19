#include <iostream>
#include <fstream>
#include <string>

#include "AVL.h"

using namespace std;

namespace avl
{	
	
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
		void Remove(TreeNode<T>*& pTree, const T item)
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
		TreeNode<T>* AVL<T>::SingleRightRotation( TreeNode<T>* pTree)
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
        TreeNode<T>* AVL<T>::SingleLeftRotation( TreeNode<T>* pTree)
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
        TreeNode<T>* AVL<T>::DoubleRightLeftRotation( TreeNode<T>* pTree)
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
        TreeNode<T>* AVL<T>::DoubleLeftRightRotation( TreeNode<T>* pTree)
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
		int Height( TreeNode<T>* pTree )
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
		void AVL<T>::insertEntry(const T value)
		{
			root = InsertNode(root, value);
		}

}

#include <iostream>
#include <fstream>
#include <string>

#include "BST.h"

using namespace std;

namespace bst {


		//---------------------------------------------------------------------------------------------------
		// Class: TreeNode
		//---------------------------------------------------------------------------------------------------

			template <class T>
			TreeNode<T>::TreeNode(const T& item, TreeNode<T>* left, TreeNode<T>* right)
				: item(item), left(left), right(right)
			{ }

		//---------------------------------------------------------------------------------------------------
		// Class: BST
		//---------------------------------------------------------------------------------------------------

			template <class T>
			void BST<T>::InsertNode(TreeNode<T>*& pTree, const T& item)
			{
				if ( pTree == NULL ) {
					pTree = new TreeNode<T>(item, NULL, NULL);
					nodeCount++;
				} else if ( item < pTree->item ) {
					InsertNode(pTree->left, item);
				} else if ( item >= pTree->item ) {
					InsertNode(pTree->right, item);
				}
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
			void BST<T>::RemoveNode(TreeNode<T>*& pTree)
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
			void BST<T>::ProcessLeftMost(TreeNode<T>*& pTree, T& replacementItem)
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
			void BST<T>::Preorder(TreeNode<T>* pTree, void(*visit)(const T& item))
			{
				visit(pTree->item);

				if ( pTree->left != NULL )
					Preorder(pTree->left, visit);

				if ( pTree->right != NULL )
					Preorder(pTree->right, visit);
			}

			template <class T>
			void BST<T>::Inorder(TreeNode<T>* pTree, void(*visit)(const T& item))
			{
				if ( pTree->left != NULL )
					Inorder(pTree->left, visit);

				visit(pTree->item);

				if ( pTree->right != NULL )
					Inorder(pTree->right, visit);
			}


			template <class T>
			void BST<T>::Postorder(TreeNode<T>* pTree, void(*visit)(const T& item))
			{
				if ( pTree->left != NULL )
					Postorder(pTree->left, visit);

				if ( pTree->right != NULL )
					Postorder(pTree->right, visit);

				visit(pTree->item);
			}


			template <class T>
			void BST<T>::DestroyTree(TreeNode<T>*& pTree)
			{
				while ( pTree != NULL )
					RemoveNode(pTree);
			}



			template <class T>
			void BST<T>::CopyTree(TreeNode<T>* pFromTree, TreeNode<T>*& pToTree)
			{
				if ( pFromTree != NULL)
				{
					pToTree = new TreeNode<T>(pFromTree->item, NULL, NULL);

					if ( pFromTree->left != NULL )
						CopyTree(pFromTree->left, pToTree->left);

					if ( pFromTree->right != NULL )
						CopyTree(pFromTree->right, pToTree->right);
				}
			}



			template <class T>
			bool BST<T>::isThere(TreeNode<T>* pTree, const T& item)
			{
				if ( pTree == NULL )
					return false;
				else
				{					
					if ( item == pTree->item )
						return true;
					else if ( item < pTree->item )
						return isThere( pTree->left, item );
					else 
						return isThere( pTree->right, item );		
				}
			}



	// *******************************
	//
	//		 PUBLIC
	//
	// *******************************


			template <class T>
			BST<T>::BST() : root(NULL), nodeCount(0)
			{ }



			template <class T>
			BST<T>::BST(const BST<T>& tree)
			{
				CopyTree(tree.root, root);
			}


			template <class T>
			BST<T>::~BST()
			{
				DestroyTree(root);
			}


			template <class T>
			void BST<T>::PreorderTraversal(void(*visit)(const T& item))
			{
				Preorder(root, visit);
			}

			template <class T>
			void BST<T>::InorderTraversal( void (*visit)(const T& item) )
			{
				Inorder(root, visit);
			}

			template <class T>
			void BST<T>::PostorderTraversal( void (*visit)(const T& item) )
			{
				Postorder(root, visit);
			}


		//***********************************
		//	
		// 		Inherited Methods
		//
		//***********************************


			template <class T>
			int BST<T>::LoadFromFile(string filename)
			{
				ifstream fin;
				fin.open( filename.c_str() );

				if ( fin.fail() ) {
					return 0;
				}

				T item;

				while ( !fin.eof() ) {
					fin >> item;
					insertEntry( item );
				}


				fin.clear();
				fin.close();	

				return 1;
			}

			template <class T>
			void BST<T>::clear(void) 
			{
				DestroyTree(root);
			}

			template <class T>
			void BST<T>::insertEntry(const T value)
			{
	 			InsertNode(root, value);
			}

			template <class T>
			void BST<T>::deleteEntry(const T value)
			{
				//Remove(root, value);			
			}

			template <class T>
			bool BST<T>::isThere(const T value)
			{
				return ( isThere(root, value) );
			}

			template <class T>
			int BST<T>::numEntries(void)
			{
				return ( nodeCount );
			}
}

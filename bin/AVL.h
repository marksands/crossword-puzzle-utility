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
  class AVL : public BST<T>
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
			void AVL<T>::Preorder(TreeNode<T>* pTree, void(*visit)(const T& item))
			{
				visit(pTree->item);

				if ( pTree->left != NULL )
					Preorder(pTree->left, visit);

				if ( pTree->right != NULL )
					Preorder(pTree->right, visit);
			}

			template <class T>
			void AVL<T>::Inorder(TreeNode<T>* pTree, void(*visit)(const T& item))
			{
				if ( pTree->left != NULL )
					Inorder(pTree->left, visit);

				visit(pTree->item);

				if ( pTree->right != NULL )
					Inorder(pTree->right, visit);
			}


			template <class T>
			void AVL<T>::Postorder(TreeNode<T>* pTree, void(*visit)(const T& item))
			{
				if ( pTree->left != NULL )
					Postorder(pTree->left, visit);

				if ( pTree->right != NULL )
					Postorder(pTree->right, visit);

				visit(pTree->item);
			}


			template <class T>
			void AVL<T>::DestroyTree(TreeNode<T>*& pTree)
			{
				while ( pTree != NULL )
					RemoveNode(pTree);
			}



			template <class T>
			void AVL<T>::CopyTree(TreeNode<T>* pFromTree, TreeNode<T>*& pToTree)
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
			bool AVL<T>::isThere(TreeNode<T>* pTree, const T& item)
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


			template <class T>
			void AVL<T>::PreorderTraversal(void(*visit)(const T& item))
			{
				Preorder(root, visit);
			}

			template <class T>
			void AVL<T>::InorderTraversal( void (*visit)(const T& item) )
			{
				Inorder(root, visit);
			}

			template <class T>
			void AVL<T>::PostorderTraversal( void (*visit)(const T& item) )
			{
				Postorder(root, visit);
			}


		//***********************************
		//	
		// 		Inherited Methods
		//
		//***********************************


			template <class T>
			int AVL<T>::LoadFromFile(string filename)
			{
				ifstream fin( filename.c_str(), ios::in );

				if ( !fin.is_open() )
					return -1;

				T item;

				while ( !fin.eof() ) {
					fin >> item;
					insertEntry( item );
				}

				fin.clear();
				fin.close();	

				return 0;
			}

			template <class T>
			void AVL<T>::clear(void) 
			{
				DestroyTree(root);
			}

			template <class T>
			void AVL<T>::insertEntry(const T value)
			{
				root = InsertNode(root, value);
			}

			template <class T>
			void AVL<T>::deleteEntry(const T value)
			{
				//Remove(root, value);			
			}

			template <class T>
			bool AVL<T>::isThere(const T value)
			{
				return ( isThere(root, value) );
			}

			template <class T>
			int AVL<T>::numEntries(void)
			{
				return ( nodeCount );
			}


	
}

//#include "AVL.cpp"

#endif

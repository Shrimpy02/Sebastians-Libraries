#pragma once
#include <iostream>
#include <vector>

using namespace std;
class BinaryTree
{
public:
	//--------------------- Class initialization ---------------------
	/**
	 * \brief Binary Tree constructor, inits the first node of the tree. 
	 */
	BinaryTree()
	{
		// Initialize root node with no parent and rootData = -1
		Tree.push_back(CreateNode(rootData, nullptr));
	};

	struct Node
	{
		int data;
		Node* LeftChild;
		Node* RightChild;
		Node* Parent;
	};

	//---------------------  Variables  ---------------------

	/**
	* \brief Vector containing a dynamic amount of trees.
	*/
	vector<Node*> Tree;

	/**
	 * \brief Common Data for all root nodes.
	 */
	const int rootData = -1;

	//---------------------  Test Functions  ---------------------
		/**
		 * \brief Creates a test tree using the constructed root
		 */
	void CreateTestTree()
	{
		/*		The tree to create
		*   lvl0:      -1
		*			  /  \
		*	lvl1:    1	  2
		*		    / \     \
		*	lvl2:  3   4     5
		*
		 */

		// Lvl 0 - root
		// constructed

		// Lvl 1
		Tree[0]->LeftChild = CreateNode(1, Tree[0]);
		Tree[0]->RightChild = CreateNode(2, Tree[0]);

		// Lvl 2
		Tree[0]->LeftChild->LeftChild = CreateNode(3, Tree[0]->LeftChild);
		Tree[0]->LeftChild->RightChild = CreateNode(4, Tree[0]->LeftChild);
		Tree[0]->RightChild->RightChild = CreateNode(5, Tree[0]->RightChild);
	}

	//---------------------  Member Functions  ---------------------

	/**
	 * \brief Function to init a new root for a new tree.
	 */
	void InitNewTree()
	{
		Tree.push_back(CreateNode(rootData, nullptr));
	}

	/**
	 * \brief Create's a new node.
	 * \param data Data the new Node is to hold.
	 * \return returns the new node created.
	 */
	Node* CreateNode(const int data, Node* inputparent)
	{
		Node* NewNode = new Node();
		NewNode->data = data;
		NewNode->Parent = inputparent;
		return NewNode;
	}

	/**
	 * \brief Deletes the given node from memory and from Tree,
	 * also deletes all children nodes.
	 * \param root the node to delete.
	 */
	void DeleteNode(Node* root)
	{
		if (root == nullptr) return;

		// delete parents left child, if this root is the left child
		if(root->Parent->LeftChild && root->Parent->LeftChild->data == root->data)
			root->Parent->LeftChild = nullptr;
		
		// delete parents right child, if this root is the right child
		if(root->Parent->LeftChild && root->Parent->LeftChild->data == root->data)
			root->Parent->RightChild = nullptr;

		// Calls delete children to remove the current node and its children from memory
		DeleteChildren(root);
	}

private:
	/**
	 * \brief A recursive function used to delete the children and itself from memory.
	 * function is private since the parents reference must be deleted as well and that
	 * is handled internally.
	 * \param root the node to delete.
	 */
	void DeleteChildren(Node* root)
	{
		// Check left child
		if (root->LeftChild)
			DeleteChildren(root->LeftChild);

		// Check right child
		if (root->RightChild)
			DeleteChildren(root->RightChild);

		// delete the input node
		delete root;
	}
public:
	/**
	 * \brief Traverses the tree from the given node in a depth first manor.
	 * \param root The node it starts traversing from.
	 */
	void DepthFirstPrintTree(Node* root, bool isLast = true)
	{
		if (root == nullptr) return;
		std::cout << root->data << " ";
		// Recursively calls print after printing, this makes it print down each node and its children first.

		// Check left child
		if (root->LeftChild)
			DepthFirstPrintTree(root->LeftChild);
		
		// Check right child
		if (root->RightChild)
			DepthFirstPrintTree(root->RightChild);
		
	
	}

	/**
	 * \brief Traverses the tree from the given node in a breadth first manor.
	 * \param root The node it starts traversing from.
	 */
	void BredthFirstPrintTree(Node* root)
	{
		if (root == nullptr) return;

		// Create a vector of temp children to remember whom to print
		std::vector<Node*> TempChildren;
		TempChildren.push_back(root);

		// works while there are temp children 
		while (!TempChildren.empty())
		{
			size_t n = TempChildren.size();

			while (n > 0)
			{
				Node* p = TempChildren[0];
				// deletes the first element of the vector
				TempChildren.erase(TempChildren.begin());
				std::cout << p->data << " ";

				// push back on the vector per iteration.
				if (p->LeftChild)
					TempChildren.push_back(p->LeftChild);
				if (p->RightChild)
					TempChildren.push_back(p->RightChild);

				n--;
			}
			std::cout << std::endl;
		}
	}

	/**
	 * \brief Modifies the input node to contain the new input data.
	 * \param root The node to update data.
	 * \param newData The new data the node is updated with.
	 */
	void ModifyNode(Node* root, int newData)
	{
		root->data = newData;
	}

	// ---------------------  Getters  ---------------------

	/**
	 * \brief Gets the root of the tree from any node.
	 * \param node Any node of a tree.
	 * \return Returns the root node.
	 */
	Node* GetRoot(Node* node) {
		if (node == nullptr) {
			return nullptr;
		}

		// Traverse up the tree to find the root node.
		while (node->Parent != nullptr) {
			node = node->Parent;
		}

		return node;
	}

	/**
	 * \brief Gets the parent of the input node.
	 * \param root The node you want the parent of.
	 * \return Returns the parent node.
	 */
	Node* GetParent(Node* root) {
		if (root == NULL) return nullptr;

		return root->Parent;
	}

	/**
	 * \brief Gets the vector of children from the input node.
	 * \param root The node you want the children from.
	 * \return Returns the vector of children the node has.
	 */
	Node* GetLeftChild(Node* root)
	{
		return root->LeftChild;
	}

	Node* GetRightChild(Node* root)
	{
		return root->RightChild;
	}

	/**
	 * \brief Gets the overall size of all nodes bellow the input root.
	 * \param root The node you wish to get the size from.
	 * \return Returns the size as int.
	 */
	int GetSize(Node* root)
	{
		if (root == nullptr) return 0;

		int size = 1;

		// Traverse the left child
		size += GetSize(root->LeftChild);

		// Traverse the right child
		size += GetSize(root->RightChild);

		return size;
	}

	/**
	 * \brief Gets the depth of the tree from the input node.
	 * \param root The root to get the height from.
	 * \return Returns the depth as an int.
	 */
	int GetDepth(Node* root)
	{
		if (root == nullptr) return 0;

		// Recursively calculate the depth of the left and right subtrees
		int leftDepth = GetDepth(root->LeftChild);
		int rightDepth = GetDepth(root->RightChild);

		// Return the maximum depth of the left and right subtrees plus 1
		return std::max(leftDepth, rightDepth) + 1;
	}

	/**
	 * \brief Gets the data of the input node.
	 * \param root The node you want the data from.
	 * \return Returns the data as int.
	 */
	int GetNodeData(Node* root)
	{
		if (root == nullptr) return 0;
		return root->data;
	}

	// ---------------------  Checkers  ---------------------

	/**
	 * \brief Checks if the Tree index is empty, IE no trees.
	 * \return Returns true if it is empty.
	 */
	bool IsEmpty()
	{
		if (Tree.size() == 0) return true;

		return false;
	}

	/**
	 * \brief Checks if the input node is the root node or not
	 * by testing if it has a parent node.
	 * \param root The node to check.
	 * \return Returns true if the Node is the root.
	 */
	bool IsRoot(Node* root)
	{
		if (root != nullptr && root->Parent == nullptr) return true;

		return false;
	}

	/**
	 * \brief Checks if the input node is a leaf node or not
	 * by testing if it has children nodes.
	 * \param root The node to check.
	 * \return Returns true if the input node is a leaf.
	 */
	bool Isleaf(Node* root)
	{
		if (root->LeftChild == nullptr || root->RightChild == nullptr) return true;

		return false;
	}

};
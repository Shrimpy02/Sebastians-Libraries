#pragma once
#include <iostream>
#include <vector>

class GenericTree
{
public:
	//--------------------- Class initialization ---------------------
	/**
	 * \brief Constructor creates the root for the first of the tree Arrays.
	 */
	GenericTree()
	{
		// Initialize root node with no parent and rootData = -1
		Tree.push_back(CreateNode(rootData, nullptr));
	}

	/**
	 * \brief Node Struct.
	 */
	struct Node
	{
		int data;
		std::vector<Node*> child;
		Node* Parent;
	};

	//---------------------  Variables  ---------------------

	/**
	 * \brief Vector containing a dynamic amount of trees.
	 */
	std::vector<Node*> Tree;

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
		*              -1
		*         /  /    \     \
		*        1  2      3      4
		*       / \        |   /  | \
		*      5   6       7   8  9  10
		*/

		// Lvl 0 - root
		// constructed

		// Lvl 1
		Tree[0]->child.push_back(CreateNode(1, Tree[0]));
		Tree[0]->child.push_back(CreateNode(2, Tree[0]));
		Tree[0]->child.push_back(CreateNode(3, Tree[0]));
		Tree[0]->child.push_back(CreateNode(4, Tree[0]));

		// Lvl 2
		Tree[0]->child[0]->child.push_back(CreateNode(5, Tree[0]->child[0]));
		Tree[0]->child[0]->child.push_back(CreateNode(6, Tree[0]->child[0]));
		Tree[0]->child[2]->child.push_back(CreateNode(7, Tree[0]->child[2]));
		Tree[0]->child[3]->child.push_back(CreateNode(8, Tree[0]->child[3]));
		Tree[0]->child[3]->child.push_back(CreateNode(9, Tree[0]->child[3]));
		Tree[0]->child[3]->child.push_back(CreateNode(10, Tree[0]->child[3]));

	}

	/**
	 * \brief tests the GetChildren function and prints all children data to the console.
	 * \param TempGetChildren the vector of children to test on.
	 */
	void testGetChildren(std::vector<Node*> TempGetChildren)
	{
		// gets and outputs to the console all the children of the given vector.
		for (int i = 0; i > TempGetChildren.size(); i++) {
			std::cout << TempGetChildren[i]->data << ", ";
		}
	}

	/**
	 * \brief Tests the GetParent function and prints to the console.
	 * \param root Node to test on.
	 */
	void testGetParent(Node* root)
	{
		// gets and outputs the data of the given parent
		std::cout << "The parents data of node with data '11': ";
		std::cout << GetParent(root)->data;
	}

	/**
	 * \brief Tests the GetRoot function and prints to the console.
	 * \param root Node to test on.
	 */
	void testGetRoot(Node* root)
	{
		// gets and outputs the data of the root of a tree.
		std::cout << "The Trees Root data: ";
		std::cout << GetRoot(root)->data;
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
	 * \brief A function to generate a random general tree.
	* \param root the root from witch to generate a new tree.
	* \param maxDepth The max depth of the tree generated.
	* \param currentDepth The current depth of the generated tree for recursion.
	*/
	void GenerateRandomTree(Node* root, int maxDepth, int currentDepth)
	{
		// Stop recursion when the maximum depth is reached.
		if (currentDepth >= maxDepth) {
			return;
		}

		int numChildren = std::rand() % 4; // Generate a random number of children (0 to 3 in this example).

		for (int i = 0; i < numChildren; ++i) {

			// Create a new child node and add it to the current root.
			Node* child = CreateRandomNode(root);
			root->child.push_back(child);

			// Recursively generate the subtree for the child.
			GenerateRandomTree(child, maxDepth, currentDepth + 1);
		}
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
	* \brief Create's a new node with random data.
	* \return returns the new node created.
	*/
	Node* CreateRandomNode(Node* inputparent)
	{
		Node* NewNode = new Node();
		// Generate a random data value (0 to 99).
		NewNode->data = std::rand() % 100;
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

		// deletes the parents reference to the node
		for (auto it = root->Parent->child.begin(); it != root->Parent->child.end();) {

			if (*it == root) {
				it = root->Parent->child.erase(it); // Erase the element and get the next iterator.
			}
			else {
				++it; // Move to the next element if it's not the one we want to delete.
			}
		}

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
		// calls delete children recursively for each child in the input node. 
		for (auto it = root->child.begin(); it != root->child.end(); ++it) {
			DeleteChildren(*it);
		}

		// Clear the child vector
		root->child.clear();

		// delete the input node
		delete root;
	}

public:

	/**
	 * \brief Traverses the tree from the given node in a depth first manor.
	 * \param root The node it starts traversing from.
	 */
	void DepthFirstPrintTree(Node* root, const std::string& prefix = "", bool isLast = true)
	{
		if (root == nullptr) return;
		std::cout << root->data << " ";
		// Recursively calls print after printing, this makes it print down each node and its children first.
		for (auto it = root->child.begin(); it != root->child.end(); ++it) {
			DepthFirstPrintTree(*it);
		}
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
				for (auto it = p->child.begin(); it != p->child.end(); ++it) {
					TempChildren.push_back(*it);
				}
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
	std::vector<Node*> GetChildren(Node* root)
	{
		return root->child;
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

		for (auto it = root->child.begin(); it != root->child.end(); ++it) {
			size += GetSize(*it);
		}
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

		int maxdepth = 0;

		for (auto it = root->child.begin(); it != root->child.end(); ++it) {
			maxdepth = std::max(maxdepth, GetDepth(*it));
		}

		return maxdepth + 1;
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
		if (root != nullptr && root->child.size() == 0) return true;

		return false;
	}
};

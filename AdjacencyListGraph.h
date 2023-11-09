#pragma once
#include <memory>
#include <vector>


class AdjacencyListGraph
{
public:

	//--------------------- Class initialization ---------------------

	/**
	 * \brief Graph Constructor.
	 */
	 AdjacencyListGraph()
	{
		vertexes.resize(AmountOfVertexes);
	}

	/**
	 * \brief Node Struct with constructor.
	 */
	struct Node
	{
		int id;
		int data;
		Node(int _id, int _data) : id(_id), data(_data) {}
	};

	//---------------------  Variables  ---------------------

private:

	/**
	 * \brief Linked List of Graph vertexes. Uses a pairs containing the Node struct and edge weight
	 */
	std::vector<std::vector<std::pair<std::shared_ptr<Node>, int>>> vertexes;

	/**
	 * \brief Smart pointer vector to contain all node references. 
	 */
	std::vector<std::shared_ptr<Node>> nodes;

	/**
	 * \brief Amount of vertexes in Graph.
	 */
	int AmountOfVertexes = 0;

public:

	//---------------------  Test Functions  ---------------------

	/**
	 * \brief Prints the entire graph with its edges. 
	 */
	void printGraph()
	{
		for (int u = 0; u < vertexes.size(); u++)
		{
			std::cout << "Node " << u << " makes an edge with:\n";
			for (const auto& pair : vertexes[u])
			{
				const std::shared_ptr<Node>& v = pair.first;
				int w = pair.second;
				std::cout << "\tNode " << v->id << " with edge weight = " << w << "\n";
			}
			std::cout << std::endl;
		}
	}

	/**
	 * \brief Prints the data of each Node from input.
	 * \param adjacentNodes The vector of Nodes to print. 
	 */
	void printData(std::vector<std::shared_ptr<Node>> adjacentNodes)
	{
		// Iterates through the size of adjacent nodes vector and prints each id in the vector
		for(int i = 0 ; i < adjacentNodes.size(); i++)
		{
			if(adjacentNodes[i] != nullptr)
				std::cout << adjacentNodes[i]->id << ", ";
		}
	}

	/**
	 * \brief Prints all Int's in the input vector as edge weights.
	 * \param adjacentEdgeWeights The adjacent edge weights to print. 
	 */
	void printEdge(std::vector<int> adjacentEdgeWeights)
	{
		// Iterates through the size of adjacent edge weights and prints each weight in the vector
		for (int i = 0; i < adjacentEdgeWeights.size(); i++)
		{
			std::cout << adjacentEdgeWeights[i] << ", ";
		}
	}

	/**
	 * \brief Prints both the Node data and the edge weight of the input vector.
	 * \param adjacentNodeEdges The vector adjacent Node edges to print from. 
	 */
	void printAdjacentNodeEdges(std::vector<std::pair<std::shared_ptr<Node>, int>> adjacentNodeEdges)
	{
		// Iterates through the input vector and prints both pairs, IE node data and edge weight
		for (const auto& edge : adjacentNodeEdges)
		{
			const std::shared_ptr<Node>& v = edge.first;
			int w = edge.second;
			std::cout << "\tNode " << v->id << " with edge weight = " << w << "\n";
		}
		std::cout << std::endl;
	}

	/**
	 * \brief Prints the complete graph based on the input.
	 * \param graph The graph to completely print.
	 */
	void printCompleteGraph(std::vector<std::vector<std::pair<std::shared_ptr<Node>, int>>> graph)
	{
		// Iterates through entire graph and prints the node, its adjacent nodes and their coresponding weights. 
		std::cout << std::endl;
		for (int u = 0; u < graph.size(); u++)
		{
			std::cout << "Node " << u << " makes an edge with:\n";
			for (const auto& pair : graph[u])
			{
				const std::shared_ptr<Node>& v = pair.first;
				int w = pair.second;
				std::cout << "\tNode " << v->id << " with edge weight = " << w << "\n";
			}
			std::cout << std::endl;
		}
	}

	//---------------------  Member Functions  ---------------------
private:
	/**
	 * \brief Internal function to resize graph list with the amount of vertexes given.
	 */
	void resizeGraph()
	{
		vertexes.resize(AmountOfVertexes);
	}

public:

	/**
	 * \brief Creates a random graph with random data and random edges with random weights.
	 * \param numNodes the amount of nodes to create a graph with. 
	 * \param maxEdgeWeight Max Edge weight of the edges created. 
	 */
	void GenerateRandomGraph(int numNodes, int maxEdgeWeight) {
		// Seed the random number generator
		std::srand(static_cast<unsigned>(std::time(nullptr)));

		// Generate random nodes
		for (int i = 0; i < numNodes; ++i) {
			CreateRandomNode(i);
		}

		// Connect nodes with random edges
		for (int i = 0; i < numNodes; ++i) {
			for (int j = i + 1; j < numNodes; ++j) {
				// Random edge weight (1 to maxEdgeWeight)
				int edgeWeight = 1 + std::rand() % maxEdgeWeight;
				AddEdge(GetGraphVertices()[i], GetGraphVertices()[j], edgeWeight);
			}
		}
	}

	/**
	 * \brief Creates a new smart pointer to a Node.
	 * \param nodeID The node index, should be consecutive to the last. 
	 * \param nodeData The Node data is the information the node contains. 
	 * \return It returns a smart pointer to the new node created.
	 */
	std::shared_ptr<Node> CreateNode(int nodeID, int nodeData)
	{
		std::shared_ptr<Node> newNode = std::make_shared<Node>(nodeID, nodeData);
		// Pushes new node reference into a smart pointer vector to keep track of them. 
		nodes.push_back(newNode);
		// Calls resize graph as the graph size now increases. 
		AmountOfVertexes++;
		resizeGraph();
		return newNode;
	}

	/**
	* \brief Creates a new smart pointer to a Node with random data.
	* \param nodeID The node index, should be consecutive to the last.
	* \return It returns a smart pointer to the new node created.
	*/
	std::shared_ptr<Node> CreateRandomNode(int nodeID)
	{
		// Generate a random data value (0 to 99).
		int nodeData = std::rand() % 100;
		std::shared_ptr<Node> newNode = std::make_shared<Node>(nodeID, nodeData);
		// Pushes new node reference into a smart pointer vector to keep track of them. 
		nodes.push_back(newNode);
		// Calls resize graph as the graph size now increases. 
		AmountOfVertexes++;
		resizeGraph();
		return newNode;
	}

	/**
	 * \brief Creates a new edge from a node to a different node. The new edges has a weight assigned to it.
	 * \param from The from node is the start of the edge.
	 * \param to The to node is where the edge connects too. 
	 * \param weight The weight of the edge connecting the two nodes.  
	 */
	void AddEdge(const std::shared_ptr<Node>& from, const std::shared_ptr<Node>& to, int weight) {
		// Pushes both edges to the linked list. 
		vertexes[from->id].push_back(std::make_pair(to, weight));
		vertexes[to->id].push_back(std::make_pair(from, weight));
	}

	/**
	 * \brief Deletes a Node, it's reference and it's edges between other nodes. 
	 * \param NodeToDelete The Node to delete. 
	 */
	void DeleteNode(const std::shared_ptr<Node>& NodeToDelete)
	{
		if (NodeToDelete == nullptr) return;
		int NodeID = NodeToDelete->id;

		if(NodeID >= 0 && NodeID < AmountOfVertexes)
		{
			// Delete all edges connected to the node
			std::vector<std::pair<std::shared_ptr<Node>, int>> AdjacentEdges = GetAdjacentNodeEdges(NodeToDelete);
			for (auto edge : AdjacentEdges)
			{
				DeleteEdge(NodeToDelete, edge.first);
			}

			// Delete the node itself
			nodes[NodeID].reset();

			// Clear connected edges
			vertexes[NodeID].clear();

			// Update the adjacency list of other nodes to remove references to deleted node
			// Creates an adjacentList based on vertexes
			for (auto adjacentList : vertexes)
			{
				// Iterates through the adjacentList and if the id of the adjacent node matches 
				// the deleted node, the element gets deleted removing the edge reference.
				for (auto it = adjacentList.begin(); it != adjacentList.end(); )
				{
					if(it->first->id == NodeID)
					{
						it = adjacentList.erase(it);
					} else
					{
						++it;
					}
				}
			}
			// Resizes the amount of vertexes after one has been deleted. 
			AmountOfVertexes--;
			resizeGraph();
		}
	}

	/**
	 * \brief Deletes the edge between two nodes. 
	 * \param from A node that has an edge to the second node. 
	 * \param to The second node.
	 */
	void DeleteEdge(const std::shared_ptr<Node>& from, const std::shared_ptr<Node>& to)
	{
		if (from == nullptr || to == nullptr) return;

		// Remove Edge from the "from" nodes index.

		// Accesses the adjacency list from the "from" node where from->id is the index used
		// it then calls erase with standard library remove_if function, that removes elements from the range vertexes[from].begin to vertexes[from].end
		vertexes[from->id].erase(std::remove_if(vertexes[from->id].begin(), vertexes[from->id].end(),
			
			// the third argument [&to] is a lambda function that defines the condition for removing elements from the range.
			// A lambda function is small function called within other functions to encapsulate a few lines of code and return an immediate value.
			// the lambda function takes an argument "edge" witch is an element in the adjacency list.
			// [&to] is captured by reference so that it can be used inside the lambda function
			[&to](const std::pair<std::shared_ptr<Node>, int>& edge) {

				// condition used by lambda function that checks if the first member of the edge (shared_ptr<Node>) is equal to the "to" smart pointer
				// in other words it compares if the edge connects from the "from" node to the "to" node. 
				return edge.first == to;

				// the lambda function returns the first iteration in the range that should be removed. And passes it to the erase function.
				// the erase function can then delete all iterations that connect "from" too "to" with in the range of vertexes[from].end
		}), vertexes[from->id].end());

		// Then remove Edge from the "to" nodes index.
		vertexes[to->id].erase(std::remove_if(vertexes[to->id].begin(), vertexes[to->id].end(),
			[&from](const std::pair<std::shared_ptr<Node>, int>& edge) {
				return edge.first == from;
			}), vertexes[to->id].end());
	}

	/**
	 * \brief Graph depth first traversal algorithm, it visits all visitable nodes from the input node by depth.  
	 * \param startNode The node to start traversing from.
	 * \param visited An input vector that keeps track of if a node has been visited or not,
	 * must be initialized to the same size as the graph and must contain only false values.
	 */
	void DepthTraversal(const std::shared_ptr<Node>& startNode, std::vector<bool>& visited)
	{
		// base case; returns if the start node is null or node has been visited already. 
		if (!startNode || visited[startNode->id]) return;

		// sets the visited array of the index of the node currently being visited too true and prints. 
		visited[startNode->id] = true;
		std::cout << "Visited Node " << startNode->id << std::endl;

		// Iterates through the linked list and recursively calls depth first traversal for each neighbor
		for (const auto& edge : vertexes[startNode->id])
		{
			const std::shared_ptr<Node>& neighbor = edge.first;
			DepthTraversal(neighbor, visited);
		}
	}

	/**
	 * \brief Graph Breadth first traversal algorithm, it visits all visitable nodes from the input node level by level. 
	 * \param startNode The node to start traversing from.
	 */
	void BreadthTraversal(const std::shared_ptr<Node>& startNode)
	{
		// Base case; returns if the start node is null.
		if (!startNode) return;

		// Initiates a visited vector to check if nodes have been visited.
		// Also initiates a temp vector to store the nodes to visit in the right order.
		std::vector<bool> visited(AmountOfVertexes,false);
		std::vector<std::shared_ptr<Node>> TempNodes;

		// Sets the visited to true and pushes this node to the temp nodes.
		TempNodes.push_back(startNode);
		visited[startNode->id] = true;

		// While there are nodes to visit the while loop runs.
		while (!TempNodes.empty())
		{
			// Deques the front node and possesses it
			const std::shared_ptr<Node> current = TempNodes.front();
			TempNodes.erase(TempNodes.begin());

			// Prints if it has visited it.
			std::cout << "Visited Node " << current->id << std::endl;

			// Checks if the node shares an edge, if it does the node connected is pushed to the queue
			for (const auto& edge : vertexes[current->id])
			{
				const std::shared_ptr<Node>& neighbor = edge.first;
				if(!visited[neighbor->id])
				{
					visited[neighbor->id] = true;
					TempNodes.push_back(neighbor);
				}
			}
		}
	}

	/**
	 * \brief A Small helper function to change the data of a node to the new input data.
	 * \param node The node to change data for. 
	 * \param newdata The new data the node should contain. 
	 */
	void ModifyData(const std::shared_ptr<Node>& node, int newdata)
	{
		node->data = newdata;
	}

	// ---------------------  Getters  ---------------------

	/**
	 * \brief Gets the input nodes data.
	 * \param node The node to get data from.
	 * \return The data as int. 
	 */
	int GetNodeData(const std::shared_ptr<Node>& node)
	{
		// returns the out data as an auto assigned type.
		auto outdata = node->data;
		return outdata;
	}

	/**
	 * \brief Gets all adjacent nodes to the input node. 
	 * \param node The node to get adjacent nodes from. 
	 * \return Returns a vector of smart pointers to the nodes that are connected to the input node. 
	 */
	std::vector<std::shared_ptr<Node>> GetAdjacentNodes(const std::shared_ptr<Node>& node)
	{
		// Creates a temp vector that holds all of the adjacent nodes.
		std::vector<std::shared_ptr<Node>> AdjacentNodes;

		// Iterates through all edges of the vertexes from the input id and pushes them back into the temp vector
		for (const auto& edge : vertexes[node->id])
		{
			AdjacentNodes.push_back(edge.first);
		}

		// returns the adjacent nodes as a vector. 
		return AdjacentNodes;
	}

	/**
	 * \brief Gets all edges connecting input node to any other node.
	 * \param node The node that has edges.
	 * \return Returns a vector of int's containing all of the edge weights. 
	 */
	std::vector<int> GetEdges(const std::shared_ptr<Node>& node)
	{
		// Creates a temp vector that holds all of the nodes edges.
		std::vector<int> Edges;

		// Iterates through all edges of the vertexes from the input node and pushes them into the temp vector
		for (const auto& edge : vertexes[node->id])
		{
			Edges.push_back(edge.second);
		}

		// returns the adjacent nodes as a vector. 
		return Edges;
	}

	/**
	 * \brief Gets all of the input nodes adjacent nodes and the edge weight between them.
	 * \param node The node to get adjacent nodes and edges from. 
	 * \return Returns a vector of pairs containing all nodes and weights of the input node.
	 */
	std::vector<std::pair<std::shared_ptr<Node>, int>> GetAdjacentNodeEdges(const std::shared_ptr<Node>& node)
	{
		// Creates a temp vector that holds all of the nodes adjacent nodes the connecting edges.
		std::vector<std::pair<std::shared_ptr<Node>, int>> AdjacentNodes;

		// Iterates through all of the vertexes from the input and pushes them back into the temp vector
		for (const auto& edge : vertexes[node->id])
		{
			AdjacentNodes.push_back(edge);
		}

		// returns the adjacent nodes as a vector of pairs. 
		return AdjacentNodes;
	}

	/**
	 * \brief Gets all the vertices/nodes in the graph. 
	 * \return Returns a vector of node references.
	 */
	std::vector<std::shared_ptr<Node>> GetGraphVertices()
	{
		// Creates a temp vector that holds all of the nodes in the graph.
		std::vector<std::shared_ptr<Node>> AllNodes;

		// Iterates through all of the Vertices from the input id and pushes them back into the temp vector
		for (int u = 0; u < nodes.size(); u++)
		{
			std::shared_ptr<Node> w = nodes[u];
			AllNodes.push_back(w);
		}

		// returns the Nodes as a vector of references. 
		return AllNodes;
	}

	/**
	 * \brief Gets all the edges in the graph.
	 * \return Returns a vector of int's containing the edge weights.
	 */
	std::vector<int> GetGraphEdges()
	{
		// Iterates through total vertex list and returns all edge values  an puts them in a temp vector.
		std::vector<int> Edges;
		
		for (int u = 0; u < vertexes.size(); u++)
		{
			for (const auto& pair : vertexes[u])
			{
				int w = pair.second;
				Edges.push_back(w);
			}
		}
		return Edges;
	}

	/**
	 * \brief Gets all vertexes (nodes and their edges) in the graph.
	 * \return linked list containing graph vertex data. 
	 */
	std::vector<std::vector<std::pair<std::shared_ptr<Node>, int>>> GetGraphVertexes()
	{
		return vertexes;
	}

	/**
	 * \brief Gets the size of the total graph. 
	 * \return Returns the amount of vertexes as the size of the graph as an int.
	 */
	int GetSize()
	{
		return AmountOfVertexes;
	}

	// ---------------------  Checkers  ---------------------

	/**
	 * \brief Checks if there are any nodes or edges in the graph.
	 * \return Returns true if empty, otherwise false.
	 */
	bool isEmpty()
	{
		if (AmountOfVertexes == 0) return true;
		return false;
	}
};

#pragma once
#include "AdjacencyListGraph.h"
#include <queue>
#include <set>
#include <iostream>

using namespace std;
class GraphBFS
{
public:
	/**
	* \brief BFS constructor, has no function.
	*/
	GraphBFS(){};

	/**
	 * \brief The BFS or breadth first search algorithim searches through and returns each node of a graph.
	 * \param Graph The graph to search through. 
	 * \param Start Wich node to search from.
	 * \return returns an unordered set of ints containing the node ids of all visited nodes.
	 */
	unordered_set<int> BFSSearch(vector<vector<pair<shared_ptr<AdjacencyListGraph::Node>, int>>>& Graph,
	                             AdjacencyListGraph::Node& Start)
	{
		// Init que to hold all nodes to visit
		queue<int> nodesToVisit;

		// Init a que to remember wich nodes the algorithim has been to already.
		unordered_set<int> visitedNodes;

		// Pushes the start node to visit que.
		nodesToVisit.push(Start.id);

		//While there are nodes to check run the pathfinder
		while (!nodesToVisit.empty())
		{
			// Gets the front node of the que.
			int currentNodeID = nodesToVisit.front();
			// Pops it from the que, since it is being prossesed.
			nodesToVisit.pop();
			// Pushes to visited nodes set so that it is not prossessed again. 
			visitedNodes.insert(currentNodeID);

			// Itterate throught the current nodes neigbours
			for (const auto& neighbor : Graph[currentNodeID])
			{
				// gets the neibours id
				int neighborID = neighbor.first->id;

				// Checks if the node has not been visited yet or thath the neigbour is traversable. if so it ends.
				if (visitedNodes.find(neighborID) != visitedNodes.end() || !neighbor.first->traversable) continue;

				// pushes the neighbour node to the nodes to visit for further prossesing. 
				nodesToVisit.push(neighborID);
			}
		}
		// calls the print function to se the nodes visited.
		printBFT(visitedNodes);
		// returns all visited nodes as unordered set of ints.
		return visitedNodes;
	}

	/**
	 * \brief Prints the result of a breadth first search
	 * \param path Unordered Set of ints that the function prints
	 */
	void printBFT(unordered_set<int> path)
	{
		cout << "Nodes visisted: " << endl;
		for (auto it = path.begin(); it != path.end(); ++it)
		{
			cout << "Node: " << *it << endl;
		}
	}

};
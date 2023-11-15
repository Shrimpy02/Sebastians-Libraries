#pragma once
#include "AdjacencyListGraph.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;
// pair typedef for easy use in search algorithim. 
typedef pair<int, int> iPair;


class AStar
{
public:
	/**
	 * \brief Astar constructor, has no function. 
	 */
	AStar() {}

	/**
	 * \brief A* Search algorithim that takes the total graph, start node and end node to find the shortest path.
	 * It traverses all relevant traversable nodes dictated by the huristic value, then returns the ids of the nodes
	 * based on the shortest path between them. 
	 * \param Graph The adjacency list of all nodes that are to be searched. 
	 * \param Start The node the search starts from. 
	 * \param End The node the search ends at. 
	 * \return Returns a vector of ints that holds the ids of the path used. 
	 */
	vector<int> AStarSearch(vector<vector<pair<shared_ptr<AdjacencyListGraph::Node>,int>>>& Graph,
	                        AdjacencyListGraph::Node& Start, AdjacencyListGraph::Node& End)
	{
		// Init open closed lists.
			// the open queue will contain the ids of the node and the f values.
			// is sorted so heigest priority is the nodes with the lowest f value.
		priority_queue<iPair, vector<iPair>, greater<iPair>> nodesToVisit;
			// Closed queue is not important what order elements are in.
			// keeps track of visited nodes by their id.
		unordered_set<int> closedSet;

		// Init gvalues and came from ids.
			// gValues remember the weight values.
		unordered_map<int, int> gValues;
			// With the cameFrom map they know the weight between nodes for re tracing the path.
		unordered_map<int, int> cameFrom;

		//push the first node into the start set with default f value of 0, and id refrence.
		nodesToVisit.push(make_pair(0,Start.id));
		//Init gValues with the default weight of 0 for the first node. 
		gValues[Start.id] = 0;

		//While there are nodes to check run the pathfinder
		while (!nodesToVisit.empty())
		{
			// gets the node with the lowest f value, then pop it from the open queue and add it to the closed set.
			int currentNode = nodesToVisit.top().second;
			nodesToVisit.pop();
			closedSet.insert(currentNode);

			// Checks if the goal has been reached if not it continues.
			if(currentNode == End.id){
				cout << "End node found" << endl;

				//If it has it retraces all nodes visited and returns the shortest path.
				vector<int> shortestPath;
				int node = End.id;

				// While the node is not at the start, since it traces from back to front
				while (node != Start.id)
				{
					// Pushes into the shortest paht based on the came from nodes.
					shortestPath.push_back(node);
					node = cameFrom[node];
				}
				//Ends with the last node, always being the start
				shortestPath.push_back(Start.id);
				//The reverse function swaps the vector back to front for logical readibility. 
				reverse(shortestPath.begin(), shortestPath.end());
				// it then uses the print path function to display the path taken. 
				printpath(shortestPath);

				// total cost variable to keep track of the movement costs. 
				int totalCost = 0;
				// loops through the shortest path and updates the total cost 
				for (size_t i = 1; i < shortestPath.size(); ++i) {
					totalCost += gValues[shortestPath[i]];
				}
				// prints the total wight. 
				printTotalWeight(totalCost);

				// returns the shortest path as a vector of ids as ints. 
				return shortestPath;
			}

			// Itterates through the current nodes neighbours, i being the current neighbour
			for (const auto& neighbor : Graph[currentNode])
			{
				// sets the current neigbor if for easy use. 
				int neighborID = neighbor.first->id;

				// Checks if the currentNodes neighbours are in in the closed sett.
				if (closedSet.find(neighborID) != closedSet.end() || !neighbor.first->traversable) continue;

				// get weight from current node to neighbour as g.
				int g = 0;
				for (int k = 0; k < Graph[currentNode].size(); k++)
				{
					// for loop is to make sure the correct weight is used from the id based on the graph index of that id
					if (Graph[currentNode][k].first->id == neighborID)
					{
						g = Graph[currentNode][k].second;
					}
				}

				// get the neighbours h value. 
				int h = neighbor.first->h;
				// calulate the f value based on the g and h.
				int f = g + h;

				// makes sure neigbours g values exits and is moer than other neibours
				if (gValues.find(neighborID) == gValues.end() || g < gValues[neighborID])
				{
					// pushses neigbour into nodesToVisit so their neigbours also are checkd
						// pushed with the calculated f value and their id. 
					nodesToVisit.push(make_pair(f, neighborID));
						// also pushs the g vale calculted
					gValues[neighborID] = g;
						// and the node the g value is assosiated with.
					cameFrom[neighborID] = currentNode;
				}
			}
		}
		// error msg if no exit is found. 
		cout << "Did not find any exit" << endl;
		return {};
	}

	/**
	 * \brief Prints the path given from the a star search. 
	 * \param path the vector of ids as ints to print.
	 */
	void printpath(vector<int> path)
	{
		cout << "Path Taken: " << endl;
		for (auto it = path.begin(); it != path.end(); ++it)
		{
			cout << "Node: " << *it << endl;
		}
	}

	/**
	 * \brief Prints the total weight/distance traversed.
	 * \param weight The input weight as an int to print.
	 */
	void printTotalWeight(int weight)
	{
		cout << "Total travel cost: " << weight << endl;
	}
};
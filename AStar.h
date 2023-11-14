#pragma once
#include "AdjacencyListGraph.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

typedef pair<int, int> iPair;

class AStar
{
public:
	AStar() {}

	void AStarSearch(vector<vector<pair<shared_ptr<AdjacencyListGraph::Node>,int>>>& Graph,
							AdjacencyListGraph::Node& Start, AdjacencyListGraph::Node& End)
	{
		//init open and closed lists
			// the open queue will contain the ids of the node and the f values.
			// is sorted so heigest priority is the nodes with the lowest f value.
		priority_queue<iPair, vector<iPair>, greater<iPair>> NodesToVisit;
			// Closed queue is not important what order elements are in.
			// keeps track of visited nodes by their id.
		unordered_set<int> ClosedSet;

		//push the first node into the start set with default f value of 0, and id refrence.
		NodesToVisit.push(make_pair(0,Start.id));

		//While there are nodes to check run the pathfinder
		while (!NodesToVisit.empty())
		{
			// gets the node with the lowest f value, then pop it from the open queue and add it to the closed queue.
			int currentNode = NodesToVisit.top().second;
			NodesToVisit.pop();
			ClosedSet.insert(currentNode);

			// Checks if the goal has been reached
			if(currentNode == End.id){
				cout << "Reached exit yo" << endl;

				printpath(ClosedSet);

				return;
			}

			// Itterates through the current nodes neighbours
			for (auto i = Graph[currentNode].begin(); i != Graph[currentNode].end(); i++)
			{
				// Checks if the currentNodes neighbours are in in the closed sett.
				bool canContinue = (ClosedSet.find((*i).first->id) == ClosedSet.end());

				// Checks if the neighbours are traversabel
				if (!(*i).first->traversable) continue;

				// if the current node is in the closed set or is not traversable it does not get prossesed further.
				if(canContinue == true)
				{
					// get weight from current node to neighbour as g.
					int g = 0;
					for(int k = 0; k < Graph[currentNode].size() ; k++)
					{
						if(Graph[currentNode][k].first->id == (*i).first->id)
						{
							g = Graph[currentNode][k].second;
						}
					}

					// get the neighbours h value. 
					int h = (*i).first->h;
					// calulate the f value based on the g and h.
					int f = g + h;
					// add the neighbour to the open list for prossessing. 
					NodesToVisit.push(make_pair(f, (*i).first->id));
				}
			}
		}
		cout << "Did not find any exit" << endl;
		return ;
	}


	void printpath(unordered_set<int> path)
	{
		cout << "Path Taken: " << endl;
		for (auto it = path.begin(); it != path.end(); ++it)
		{
			cout << "Node: " << *it << endl;
		}
	}
};
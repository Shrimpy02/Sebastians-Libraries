#pragma once
#include "AdjacencyListGraph.h"
#include <queue>
#include <list>

#define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

using namespace std;
class Dijkstras
{
public:
	/**
	 * \brief the constructur of Dijkstras search class. 
	 */
	Dijkstras() {};

	/**
	 * \brief DijkstrasSearch Algorithim. it itterates throuh the source nodes neigbours and remembers the distance it has traveled
	 * it returns a vector of all distances from the source node to the end node. 
	 * \param Graph The graph the source node is from, as a vector of a vector of a pair of a node and edge weight, in other words an adjacency list graph. 
	 * \param Source The node the search starts from. 
	 * \return Returns a vector of distances as ints.
	 */
	vector<int> DijkstrasSearch(vector<vector<pair<shared_ptr<AdjacencyListGraph::Node>, int>>>& Graph, AdjacencyListGraph::Node Source)
	{
		// Create a priority queue that holds all nodes and their distance weight. 
		priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

		// Create a vector initalized to the size of the graph with all distances = 0;
		const auto Size = Graph.size();
		vector<int> dist(Size, INF);

		// push the soruce into the prioeity queue with a distance of 0.
		pq.push(make_pair(0, Source.id));
		// update the source nodes distance to 0 in the distance vector as well.
		dist[Source.id] = 0;

		// While the queue of unvisited nodes are not empty, the prossess runs. 
		while(!pq.empty())
		{
			// extract the id of the next element in the priority queue
			int u = pq.top().second;
			// pop that element so its no longer a node that needs to be visited.
			pq.pop();

			// itterate through the current nodes neigbhours
			//list<pair<int, int>>::iterator i;
			for ( auto i = Graph[u].begin(); i != Graph[u].end(); i++)
			{
				// Gets the id of the neighbour
				int v = (*i).first->id;
				// gets the weight to that neighbour
				int weight = (*i).second;

				// checks if there is a shorter paht to neigboru through current node.
				if(dist[v] > dist[u] + weight)
				{
					// updates v if so
					dist[v] = dist[u] + weight;
					pq.push(make_pair(dist[v], v));
				}
			}
		}

		// prints the result
		printf("From source to node with distance: \n");
		for (int i = 0; i < Graph.size(); i++)
		{
			cout << "From node " << Source.id << " to Node: " << i;
			cout << "\t with distance: " << dist[i] << endl;
		}

		return dist;
	}
};
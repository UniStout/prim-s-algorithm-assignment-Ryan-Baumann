//All procedures including main

#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
//my header file
#include "prim.h"


const int big = 9999999;

int primMST(const vector<vector<pair<int, int>>>& adj, int vertex) {

	//this is the minimum edge weight that connects Vertex to the MST
	vector<int> key(vertex, big);
	//this is to see if a connection exists in the MST, -1 is for when the connection is not in the MST (yet)
	vector<int> parent(vertex, -1);
	//This tracks included vertices.
	vector<bool> inMST(vertex, false);

	//Makes a min-heap, this heap is sorted by edge weight
	//each entry looks like [weight, vertex]
	//vertex with smallest connecting edge is always included
	priority_queue<pair<int, int>, vector<pair<int, int>>,
		//flips to min-heap
		greater<pair<int, int>>> pq;

	//this is where the eveyrthing initializes
	//Starts from vertex 0
	//pq.push makes it so that vertex 0 is always included
	key[0] = 0;
	pq.push({ 0, 0 });

	//each loop adds 1 new vertex to the MST
	while (!pq.empty()) {

		//gets the vertex with the smallest edge weight so that NEXT edge is smallest possible
		int u = pq.top().second;
		pq.pop();

		//prevents duplicates (obviously bad to have duplicates) in the MST
		if (inMST[u]) continue;
		//Adds the vertex into the MST
		inMST[u] = true;

		//This loop looks at all neighbors of the vertex u
		for (auto& edge : adj[u]) {
			//This gets all of the info of one connecting vertex with u.
			int v = edge.first;
			int weight = edge.second;

			//if V is NOT in the MST and the weight is less than any existing path to v, then...
			if (!inMST[v] && weight < key[v]) {
				//sets the cheapest way to v
				key[v] = weight;
				//note that v connects to u
				parent[v] = u;
				//push the new info into the queue
				pq.push({ key[v], v });
			}
		}
	}

	//This loop calculates the total weight of edges that are in the MST created
	int totalWeight = 0;
	for (int i = 1; i < vertex; i++) {
		if (parent[i] != -1) {
			totalWeight = totalWeight + key[i];
		}
	}


	return totalWeight;
}




int main() {
	//change the contents of tree.txt to whatever you need, MAKE SURE THERE IS NO ADDITIONAL white space
	//between lines.
	ifstream inputFile("tree.txt");

	//error in case file ceases existence
	if (!inputFile) {
		cerr << "Error: Could not open file \n";
		return 1;
	}

	int vertices;
	int edges;

	//reads the first 2 lines as the number of vertices and edges respectively
	inputFile >> vertices;
	inputFile >> edge;


	//this is the adjacency list
	// adj(#) holds all connections leading to/from vertex #, weight included
	vector<vector<pair<int, int>>> adj(vertices);

	//This loop fills in the adjacency list
	for (int i = 0; i < edges; i++) {
		//u and v are the vertices, w is the weight of the edge connecting u and v
		int u, v, w;
		//reads from u, to v, to w i.e "1 2 5" for example (u = 1, v=2, w = 5)
		inputFile >> u >> v >> w;
		//graph is undirected, so we need to do this twice
		//allows movement in either direction
		adj[u].push_back({ v, w });
		adj[v].push_back({ u, w });
	}

	cout << "The total weight of the MST formed by Prim's Algorithm is: " << primMST(adj, vertices);

//here is where we call things

	return 0;
}

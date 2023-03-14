#pragma once 
#include <vector>
#include "node.h"

using namespace std;

class Node; 

class Graph {
private:
	vector<Node> nodeArray; 
	int nodeCount = 0;
public:
	// Constructor
	Graph();
	size_t insertNode(Node n);
	vector<Node*> getNodes(); 
	int getNodeCount();
	void connectNodes(Node* a, Node* b, int edgeWeight);
	void removeNode(Node* node_to_remove);
	pair<float*,float*> getCoordsForPlot();
}; 


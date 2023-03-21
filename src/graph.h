#pragma once 
#include <vector>
#include <queue>
#include "node.h"

using namespace std;

class Node;

class Graph : public ISubject {
private:
	vector<Node> nodeArray; 
	int nodeCount = 0;
public:

	enum MessageTypes { DRAWEDGE };

	// Constructor
	Graph();
	~Graph();
	size_t insertNode(Node n);
	vector<Node*> getNodes(); 
	Node* getNodeByName(string name);
	int getNodeCount();
	void connectNodes(Node* a, Node* b, int edgeWeight);
	void removeNode(Node* node_to_remove);
	pair<float*,float*> getCoordsForPlot();
	void drawEdge(Edge* e);
	//queue<Edge> runPrimsAlgorithm(Node& startingNode);
	//void visitNode(Node &node, priority_queue<Edge, vector<Edge>, greater<Edge>> &pq);
}; 


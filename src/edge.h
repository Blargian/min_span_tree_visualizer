#pragma once
#include "node.h"

class Node; 

class Edge {
private:
	Node* destinationNode;
	int edgeWeight;
public:
	//constructor
	Edge(Node* destNode, int w);

	//Setters and Getters 
	void setDestinationNode(Node* destNode);
	void setEdgeWeight(int weight);
	Node* getDestinationNode();
	int getEdgeWeight();
};
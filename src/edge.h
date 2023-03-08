#pragma once
#include "node.h"

class Node; 

class Edge {
private:
	Node* sourceNode;
	Node* destinationNode;
	int edgeWeight;
public:
	//constructor
	Edge(Node* srcNode,Node* destNode, int w);

	//Setters and Getters 
	void setSourceNode(Node* srcNode);
	void setDestinationNode(Node* destNode);
	void setEdgeWeight(int weight);
	Node* getSourceNode();
	Node* getDestinationNode();
	int getEdgeWeight();
};

bool operator==(Edge a, Edge b);
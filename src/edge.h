#pragma once
#include "node.h"
#include <iostream>
#include "iSubject.h"

class Node; 

class Edge {
private:
	Node* sourceNode;
	Node* destinationNode;
	double edgeWeight;
public:
	//constructor
	Edge(Node* srcNode,Node* destNode, double w);

	//Setters and Getters 
	void setSourceNode(Node* srcNode);
	void setDestinationNode(Node* destNode);
	void setEdgeWeight(double weight);
	Node* getSourceNode();
	Node* getDestinationNode();
	double getEdgeWeight();

	friend bool operator==(Edge a, Edge b);
	friend bool operator>(Edge a, Edge b);
	friend std::ostream& operator<<(std::ostream& stream, Edge const& e);
};



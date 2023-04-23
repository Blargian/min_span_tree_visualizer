#pragma once
#include "node.h"
#include <iostream>
#include "iSubject.h"
#include <memory>
#include "line.h"

class Node;
class Line;

using SharedMarkerPtr = std::shared_ptr<class Marker>;
using SharedLinePtr = std::shared_ptr<class Line>;

class Edge {
private:
	Node* sourceNode;
	Node* destinationNode;
	double edgeWeight = 1;
	SharedLinePtr linePtr_;
public:
	//constructor
	Edge();
	Edge(const Edge& e);
	Edge(Node* srcNode,Node* destNode, double w);
	~Edge();

	//Setters and Getters 
	void setSourceNode(Node* srcNode);
	void setDestinationNode(Node* destNode);
	void setEdgeWeight(double weight);
	void setLine(SharedLinePtr l);
	Node* getSourceNode();
	Node* getDestinationNode();
	double getEdgeWeight();
	void setLinePtr(SharedLinePtr linePtr);
	SharedLinePtr getLinePtr();

	friend bool operator==(Edge a, Edge b);
	friend bool operator>(Edge a, Edge b);
	friend std::ostream& operator<<(std::ostream& stream, Edge const& e);
};



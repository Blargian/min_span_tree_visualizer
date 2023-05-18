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
	Node* sourceNode_;
	Node* destinationNode_;
	double edgeWeight_ = 1;
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
	Node* getSourceNode() const;
	Node* getDestinationNode() const;
	double getEdgeWeight() const;
	void setLinePtr(SharedLinePtr linePtr);
	SharedLinePtr getLinePtr() const;

	friend bool operator==(Edge a, Edge b);
	friend bool operator>(Edge a, Edge b);
	friend std::ostream& operator<<(std::ostream& stream, Edge const& e);
};



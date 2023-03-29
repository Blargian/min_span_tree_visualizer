#pragma once
#include "node.h"
#include <iostream>
#include "iSubject.h"
#include "Line.h"
#include <memory>

using namespace std; 

class Node;
class Line;

class Edge {
private:
	Node* sourceNode;
	Node* destinationNode;
	double edgeWeight;
	std::shared_ptr<Line> line_; 
public:
	//constructor
	Edge();
	Edge(Node* srcNode,Node* destNode, double w);

	//Setters and Getters 
	void setSourceNode(Node* srcNode);
	void setDestinationNode(Node* destNode);
	void setEdgeWeight(double weight);
	void setLine(shared_ptr<Line> l);
	Node* getSourceNode();
	Node* getDestinationNode();
	double getEdgeWeight();

	friend bool operator==(Edge a, Edge b);
	friend bool operator>(Edge a, Edge b);
	friend std::ostream& operator<<(std::ostream& stream, Edge const& e);
};



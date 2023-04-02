#pragma once
#include "node.h"
#include <iostream>
#include "iSubject.h"
#include <memory>
#include "line.h"

class Node;
class Line;

class Edge {
private:
	Node* sourceNode;
	Node* destinationNode;
	double edgeWeight;
	std::weak_ptr<Line> associated_line_;
public:
	//constructor
	Edge();
	Edge(Node* srcNode,Node* destNode, double w);
	~Edge();

	//Setters and Getters 
	void setSourceNode(Node* srcNode);
	void setDestinationNode(Node* destNode);
	void setEdgeWeight(double weight);
	void setLine(std::shared_ptr<Line> l);
	std:: weak_ptr<Line> getLine();
	Node* getSourceNode();
	Node* getDestinationNode();
	double getEdgeWeight();

	friend bool operator==(Edge a, Edge b);
	friend bool operator>(Edge a, Edge b);
	friend std::ostream& operator<<(std::ostream& stream, Edge const& e);
};



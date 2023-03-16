#pragma once
#include "node.h"
#include <iostream>
#include "iSubject.h"

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

	friend bool operator==(Edge a, Edge b) {
		if (
			a.getSourceNode() == b.getSourceNode()
			&& a.getDestinationNode() == b.getDestinationNode()
			&& a.getEdgeWeight() == b.getEdgeWeight()
			)
		{
			return true;
		}
		else {
			return false;
		}
	};

	friend std::ostream& operator<<(std::ostream& stream, Edge const& e) {
		stream << "Source node: " << e.sourceNode << std::endl
			<< "Destination node: " << e.destinationNode << std::endl
			<< "Edge weight: " << e.edgeWeight << std::endl;

		return stream;
	};
};



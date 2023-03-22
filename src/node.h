#pragma once

#include "edge.h"
#include <string>
#include <list>
#include <utility> 
#include <iostream>

using namespace std; 

class Edge;

class Node {
private:
	list<Edge> edgeList;
	string nodeName; 
	pair <int, int> coordinates;
	bool visited = false;
public:
	Node();
	Node(string nodeName, int x, int y);
	void setNodeName(string nodeName);
	string getNodeName();
	void setXY(int x, int y);
	void insertEdge(Edge edgeToAdd);
	void removeEdge(Node* fromNode, Node* toEdge);
	void clearEdgeList();
	list<Edge> getEdgeList();
	Edge* getEdge(Node* fromNode, Node* toNode);
	pair <int, int> getXY();
	void markVisited();
	bool wasVisited();
	friend bool operator==(Node a, Node b);
	friend std::ostream& operator<<(std::ostream& stream, Node const& n);
};
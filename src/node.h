#pragma once

#include "edge.h"
#include <string>
#include <list>
#include <utility> 

using namespace std; 

class Edge;

class Node {
private:
	list<Edge> edgeList;
	string nodeName; 
	pair <int, int> coordinates;
public:
	Node();
	Node(string nodeName, int x, int y);
	void setNodeName(string nodeName);
	void setXY(int x, int y);
	void insertEdge(Edge edgeToAdd);
	void removeEdge(Node* fromNode, Node* toEdge);
	void clearEdgeList();
	list<Edge> getEdgeList();
	Edge* getEdge(Node* fromNode, Node* toNode);
	pair <int, int> getXY();

	friend bool operator==(Node a, Node b) {
		if (
			a.coordinates == b.coordinates
			&& a.edgeList == b.edgeList
			&& a.nodeName == b.nodeName
			)
		{
			return true;
		}
		else {
			return false;
		}
	};
};
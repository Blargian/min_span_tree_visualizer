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
	void removeEdge(Edge fromEdge, Edge toEdge);
	list<Edge> getEdgeList();
};
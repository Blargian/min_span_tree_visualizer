#pragma once

#include "edge.h"
#include <string>
#include <list>
#include <utility> 
#include <iostream>
#include <memory>
#include "marker.h"

class Edge;
class Marker;

class Node {
private:
	std::list<Edge> edgeList;
	std::string nodeName; 
	std::pair <int, int> coordinates;
	bool visited = false;
	std::weak_ptr<Marker> marker_;
public:
	Node();
	Node(std::string nodeName, int x, int y);
	~Node();
	void setNodeName(std::string nodeName);
	std::string getNodeName();
	void setXY(int x, int y);
	void setMarker(std::shared_ptr<Marker> marker);
	std::weak_ptr<Marker> getMarker();
	void insertEdge(Edge edgeToAdd);
	void removeEdge(Node* fromNode, Node* toEdge);
	void clearEdgeList();
	std::list<Edge> getEdgeList();
	Edge* getEdge(Node* fromNode, Node* toNode);
	std:: pair <int, int> getXY();
	void markVisited();
	bool wasVisited();
	friend bool operator==(Node a, Node b);
	friend std::ostream& operator<<(std::ostream& stream, Node const& n);
};
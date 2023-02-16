
/*
vertex.h provides the implementation for a templated
vertex object such that any data type can be stored on
a vertex eg) strings, ints etc.
*/
#pragma once
#include <list>
#include "edge.h"

class Edge;

class Vertex {

	int data;
	std::list<Edge> edgeList;

public:

	Vertex(int d) {
		data = d;
	};

	std::list<Edge> Vertex::getEdgeList();
};
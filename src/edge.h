#pragma once
#include "vertex.h"

class Vertex; 

class Edge {

Vertex* destinationVertex;
int weight;

public:

	Edge() {};

	Edge(Vertex* destVertex, int w) {
		destinationVertex = destVertex;
		weight = w;
	};
	/*Getter and Setter methods */

	void setEdge(Vertex* destVertex, int w);

	void setWeight(int w);

	Vertex* getDestination();

	int getWeight();

};

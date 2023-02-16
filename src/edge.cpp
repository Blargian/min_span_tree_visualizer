#include "edge.h"

void Edge::setEdge(Vertex* destVertex, int w) {
	destinationVertex = destVertex;
	weight = w;
};

void Edge::setWeight(int w) {
	weight = w;
};

Vertex* Edge::getDestination() {
	return destinationVertex;
};

int Edge::getWeight() {
	return weight;
};

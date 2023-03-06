#include "node.h"
#include <stdexcept>

/**
 * @brief Default Node constructor
 *
 * @param 
 */
Node::Node() {

}

/**
 * @brief Setter method for the node co-ordinates on 100x100 grid 
 *
 * @param x x-coordinate (0-100), y y-coordinate (0-100)
 */
void Node::setXY(int x, int y) {
	if ((x < 0 || x > 100) || (y < 0 || y > 100)) {
		throw std::invalid_argument("Coordinates should be between 0 and 100 inclusive");
	}
	else {
		this->coordinates.first = x;
		this->coordinates.second = y;
	}
}

/**
 * @brief inserts an edge to the edgelist
 *
 * @param edgeToAdd pointer to an Edge 
 */
void Node::insertEdge(Edge edgeToAdd) {
	this->edgeList.push_back(edgeToAdd);
}

/**
 * @brief removes an edge from the edgelist
 *
 * @param edgeToAdd pointer to an Edge
 */
void Node::removeEdge(Edge edgeToAdd) {
	
}

/**
 * @brief returns the edge list
 *
 * @param edgeToAdd pointer to an Edge
 */
list<Edge> Node::getEdgeList() {
	return edgeList; 
}


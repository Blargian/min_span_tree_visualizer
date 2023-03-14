#include <iostream>
#include "edge.h"

/**
 * @brief Edge constructor
 *
 * @param destNode pointer to the destination Node 
 * @param w weight of the edge 
 */
Edge::Edge(Node* srcNode, Node* destNode, int w)
{
	sourceNode = srcNode; 
	destinationNode = destNode;
	edgeWeight = w;
};

/**
 * @brief Destination node setter
 *
 * @param destNode pointer to the destination Node
 */
void Edge::setSourceNode(Node* srcNode)
{
	this->sourceNode = srcNode;
}

/**
 * @brief Destination node setter
 *
 * @param destNode pointer to the destination Node
 */
void Edge::setDestinationNode(Node* destNode)
{
	this->destinationNode = destNode;
}

/**
 * @brief weight setter
 *
 * @param w the weight of the edge
 */
void Edge::setEdgeWeight(int weight)
{
	this->edgeWeight = weight;
}

/**
 * @brief getter method for source node
 *
 * @param
 */
Node* Edge::getSourceNode()
{
	return this->sourceNode;
}

/**
 * @brief getter method for destination node
 *
 * @param 
 */
Node* Edge::getDestinationNode()
{
	return this->destinationNode;
}

/**
 * @brief getter method for the weight of the edge
 *
 */
int Edge::getEdgeWeight()
{
	return this->edgeWeight;
}



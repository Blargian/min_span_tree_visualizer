#include <iostream>
#include "edge.h"
#include <iomanip>
#include <memory>

using namespace std; 
/**
 * @brief Edge constructor
 *
 * @param destNode pointer to the destination Node 
 * @param w weight of the edge 
 */
Edge::Edge(Node* srcNode, Node* destNode, double w)
{
	sourceNode = srcNode; 
	destinationNode = destNode;
	edgeWeight = w;
	linePtr_ = SharedLinePtr();
};

Edge::Edge()
{
	sourceNode = nullptr;
	destinationNode = nullptr;
	edgeWeight = 0.0;
	linePtr_ = SharedLinePtr();
};


Edge::~Edge() {

}

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
};

/**
 * @brief weight setter
 *
 * @param w the weight of the edge
 */
void Edge::setEdgeWeight(double weight)
{
	edgeWeight = weight;
};


void Edge::setLinePtr(SharedLinePtr linePtr) {
	linePtr_ = linePtr; 
}

SharedLinePtr Edge::getLinePtr() {
	return linePtr_;
}

/**
 * @brief getter method for source node
 *
 * @param
 */
Node* Edge::getSourceNode()
{
	return this->sourceNode;
};

/**
 * @brief getter method for destination node
 *
 * @param 
 */
Node* Edge::getDestinationNode()
{
	return this->destinationNode;
};

/**
 * @brief getter method for the weight of the edge
 *
 */
double Edge::getEdgeWeight()
{
	return this->edgeWeight;
};


bool operator==(Edge a, Edge b) {
	if (
		a.getSourceNode() == b.getSourceNode()
		&& a.getDestinationNode() == b.getDestinationNode()
		&& a.getEdgeWeight() == b.getEdgeWeight()
		)
	{
		return true;
	}
	//because the graph is undirected
	else if (
		a.getSourceNode() == b.getDestinationNode()
		&& a.getDestinationNode() == b.getSourceNode()
		&& a.getEdgeWeight() == b.getEdgeWeight()
		) {
		return true;
	}
	else {
		return false;
	}
};

bool operator>(Edge a, Edge b) {
	if (
		a.getEdgeWeight() > b.getEdgeWeight()
		)
	{
		return true;
	}
	else {
		return false;
	}
};

std::ostream& operator<<(std::ostream& stream, Edge const& e) {
	stream << "Source node: " << e.sourceNode->getNodeName() << std::endl
		<< "Destination node: " << e.destinationNode->getNodeName() << std::endl
		<< "Edge weight: " << fixed << setprecision(2) << e.edgeWeight << std::endl;

	return stream;
};



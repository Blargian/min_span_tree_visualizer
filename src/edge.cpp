#include <iostream>
#include "edge.h"
#include <iomanip>
#include <memory>

using namespace std; 

Edge::Edge(Node* srcNode, Node* destNode, double w)
	: sourceNode_(srcNode),
	  destinationNode_(destNode),
	  edgeWeight_(w),
	  linePtr_(SharedLinePtr())
{};

Edge::Edge()
	: sourceNode_(nullptr),
	  destinationNode_(nullptr),
	  edgeWeight_(0.0),
	  linePtr_(SharedLinePtr())
{};

Edge::Edge(const Edge& e)
	: sourceNode_(e.sourceNode_),
	  destinationNode_(e.destinationNode_),
	  edgeWeight_(e.edgeWeight_),
	  linePtr_(e.linePtr_)
{};


Edge::~Edge() {};

void Edge::setSourceNode(Node* srcNode)
{
	sourceNode_ = srcNode;
}

void Edge::setDestinationNode(Node* destNode)
{
	this->destinationNode_ = destNode;
};

void Edge::setEdgeWeight(double weight)
{
	edgeWeight_ = weight;
};

void Edge::setLinePtr(SharedLinePtr linePtr) {
	linePtr_ = linePtr; 
}

SharedLinePtr Edge::getLinePtr() const {
	return linePtr_;
}

Node* Edge::getSourceNode() const
{
	return sourceNode_;
};

Node* Edge::getDestinationNode() const
{
	return destinationNode_;
};

double Edge::getEdgeWeight() const
{
	return edgeWeight_;
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
	stream << "Source node: " << e.sourceNode_->getNodeName() << std::endl
		<< "Destination node: " << e.destinationNode_->getNodeName() << std::endl
		<< "Edge weight: " << fixed << setprecision(2) << e.edgeWeight_ << std::endl;

	return stream;
};



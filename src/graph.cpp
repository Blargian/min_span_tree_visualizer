#include <iostream>
#include "graph.h"

#include <Vector>

using namespace std;

/**
 * @brief Graph default constructor
 *
 */
Graph::Graph() {

}

/**
 * @brief Inserts a node into vector<Node> nodeArray
 *
 * @param n the node to insert of type Node
 */
void Graph::insertNode(Node n) {
	this->nodeArray.push_back(n);
}

/**
 * @brief returns the vector of nodes 
 *
 */
vector<Node> Graph::getNodes() {
	return this->nodeArray;
}

/**
 * @brief connects two nodes 
 * @param a the first node
 *        b the second node
 *        edgeWeight the edge weight 
 */
void Graph::connectNodes(Node a, Node b, int edgeWeight) {

	return;
}
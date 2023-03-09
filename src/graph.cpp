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
Node* Graph::insertNode(Node n) {
	this->nodeArray.push_back(n);
	return &this->nodeArray.back();
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
void Graph::connectNodes(Node* a, Node* b, int edgeWeight) {

	//check if the nodes are connected yet or not
	//if not connected 
		//make an edge a->b and add that edge to node a edgelist
		//make an edge b->a and add that edge to node b edgelist 
	    //update the nodes

	Edge ab = Edge(a, b, edgeWeight);
	Edge ba = Edge(b, a, edgeWeight);
	a->insertEdge(ab);
	b->insertEdge(ba);
}
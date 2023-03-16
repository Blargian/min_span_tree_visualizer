#include <iostream>
#include "graph.h"
#include <string>
#include <Vector>

using namespace std;

/**
 * @brief Graph default constructor
 *
 */
Graph::Graph() {

}

Graph::~Graph() {

}

/**
 * @brief Inserts a node into vector<Node> nodeArray
 *
 * @param n the node to insert of type Node
 */
size_t  Graph::insertNode(Node n) {
	this->nodeArray.push_back(n);
	this->nodeCount++;
	return size(this->nodeArray);
}

/**
 * @brief returns the vector of nodes 
 *
 */
vector<Node*> Graph::getNodes() {
	vector<Node*> nodes;
	for (size_t i = 0; i < size(this->nodeArray); i++) {
		nodes.push_back(&(this->nodeArray[i]));
	}
	return nodes;
}

/**
 * @brief returns the number of nodes 
 *
 */
int Graph::getNodeCount() {
	return this->nodeCount;
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
	this->drawEdge(&ab);
	//this->drawEdge(&ab);
	a->insertEdge(ab);
	b->insertEdge(ba);
}

/**
 * @brief removes a node and associated edges
 * @param node_to_remove a pointer to the node to be removed
 */

void Graph::removeNode(Node* node_to_remove) {
	//visit edges in node_to_remove and remove it from those other nodes' edgelists
	list<Edge> connected_edges = node_to_remove->getEdgeList();
	for (auto it = connected_edges.begin(); it!=connected_edges.end();++it) {
		auto node_to_remove = it->getSourceNode();
		auto node_to_remove_from = it->getDestinationNode();
		node_to_remove_from->removeEdge(node_to_remove_from, node_to_remove);
	}

	//remove the edges from itself 
	node_to_remove->clearEdgeList(); 
	
	//finally, remove the node
	std::vector<Node>::iterator position = this->nodeArray.end();
	for (auto it = this->nodeArray.begin(); it != this->nodeArray.end(); ++it) {
		if (*it == *node_to_remove) {
			position = it;
		}
	}
	this->nodeArray.erase(position);
	this->nodeCount--;
}

/**
 * @brief returns formatted coordinate data of nodes for use in plotting
 */
pair<float*, float*> Graph::getCoordsForPlot() {
	int size = this->getNodeCount();
	float* node_points_x = new float[size];
	float* node_points_y = new float[size];
	for (auto it = this->nodeArray.begin(); it != this->nodeArray.end(); ++it) {
		int index = it - this->nodeArray.begin();
		auto xy = it->getXY();
		node_points_x[index] = xy.first;
		node_points_y[index] = xy.second;
	}
	return pair<float*,float*>(node_points_x,node_points_y);
}

/**
 * @brief gets formatted data for ImGui::PlotLine and notifies 
 *        App which is an observer which uses the data to plot
 *        a line with ImGui::PlotLine
 */

void Graph::drawEdge(Edge* e) {
	pair<int, int> src = e->getSourceNode()->getXY();
	pair<int, int> dest = e->getDestinationNode()->getXY();

	Line l = Line(src, dest);

	this->Notify(Graph::DRAWEDGE, l);
}
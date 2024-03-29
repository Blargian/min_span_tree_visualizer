#include <iostream>
#include "graph.h"
#include <string>
#include <Vector>
#include <queue>
#include <algorithm>
#include "implot.h"
#include "imgui.h"
#include "utility_mstv.h"

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
SharedNodePtr Graph::insertNode(SharedNodePtr n) {
	nodeCount++;
	return SharedNodePtr(nodeArray.emplace_back(n));
}

/**
 * @brief returns a vector of pointers to the nodes in nodeArray 
 *
 */
vector<SharedNodePtr>& Graph::getNodes() {
	return nodeArray;
}

/**
 * @brief returns a pointer to a node 
 * @param name String which is the nodeName member of Node
 */
SharedNodePtr Graph::getNodeByName(string name) {
	auto it = find_if(nodeArray.begin(), nodeArray.end(), [&name](auto& obj) {return obj->getNodeName() == name; });
	auto index = std::distance(nodeArray.begin(), it);
	return SharedNodePtr((nodeArray[index]));
}


/**
 * @brief returns a pointer to a node
 * @param std::pair<int,int> coordinate of the node
 */
SharedNodePtr Graph::getNodeByCoord(std::pair<int, int> coords) {

	auto node_list = getNodes();
	mstv_utility::SortNodeVector(node_list);
	auto found = mstv_utility::BinarySearch(node_list, coords);
  	return found; 
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
Edge* Graph::connectNodes(Node* a, Node* b, double edgeWeight) {

	//check if the nodes are connected yet or not
	//if not connected 
		//make an edge a->b and add that edge to node a edgelist
		//make an edge b->a and add that edge to node b edgelist 
	    //update the nodes

	Edge* ab = new Edge(a, b, edgeWeight);
	Edge* ba = new Edge(b, a, edgeWeight);
	auto aPtr = a->insertEdge(*ab);
	auto bPtr = b->insertEdge(*ba);
	return aPtr;
}

/**
 * @brief removes a node and associated edges
 * @param node_to_remove a pointer to the node to be removed
 */

void Graph::removeNode(Node* node_to_remove) {
	//visit edges in node_to_remove and remove it from those other nodes' edgelists
	list<Edge> connected_edges = node_to_remove->getEdgeList();
	
	//remove the edges from itself 
	node_to_remove->clearEdgeList(); 
	
	//finally, remove the node
	auto position = nodeArray.end();
	for (auto it = nodeArray.begin(); it != nodeArray.end(); ++it) {
		if (*(*it) == *node_to_remove) {
			position = it;
		}
	}
	nodeArray.erase(position);
	nodeCount--;
}

/**
 * @brief returns formatted coordinate data of nodes for use in plotting
 */
pair<float*, float*> Graph::getCoordsForPlot() {
	int size = this->getNodeCount();
	float* node_points_x = new float[size];
	float* node_points_y = new float[size];
	for (auto it = nodeArray.begin(); it != nodeArray.end(); ++it) {
		int index = it - nodeArray.begin();
		auto xy = (*it)->getXY();
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
	this->Notify(Graph::DRAWEDGE, Line(*e));
}

/**
 * @brief clears all of the graphs nodes, edges etc; 
 */
void Graph::clearAll() {

	//use erase-remove idiom 
	nodeArray.erase(nodeArray.begin(), nodeArray.end());
	nodeCount = nodeArray.size();
}

/**
 * @brief returns the inverse edge given an edge (i.e if given edge from 0 to 1 returns 1 to 0)
 * @parameter 
 */
Edge* getInverseEdge(Graph& g, Edge& edge) {
	auto inverse = std::make_shared<Edge>();
	auto srcNode = edge.getDestinationNode();
	auto destNode = edge.getSourceNode();
	auto& edgeList = srcNode->getEdgeList();
	for (auto& e : edgeList) {
		if (e.getDestinationNode() == destNode && e.getSourceNode() == srcNode)
			return &e;
	}
	return nullptr;
}

/**
 * @brief returns a vector of indexed edges on the graph sorted by edge weight
 * @parameter
 */

struct weightSort {
	bool operator() (Edge a, Edge b) { return (a.getEdgeWeight() > b.getEdgeWeight()); }
} sortByWeight;

std::vector<Edge> Graph::getEdges() {
	auto edges = std::vector<Edge>();
	int i = 0;
	for (auto& node : nodeArray) {
		node->setUFIID(i);
		for (auto& edge : node->getEdgeList()) {
			edges.emplace_back(edge);
		}
		i++;
	}
	std::sort(edges.begin(), edges.end(), sortByWeight);
	return edges;
}

/**
 * @brief for each node in the node list resets the node back to default as being marked 'unvisited' by some MST algorithm
 */
void Graph::resetVisitedState() {
	for (auto& node : nodeArray) {
		node->markUnvisited();
	}
}



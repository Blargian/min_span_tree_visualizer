#include "prims_algo.h"

queue<Edge> PrimsAlgorithm::findMST(Node& startingNode) {
	visitNode(startingNode, minPQ_);
	while (!minPQ_.empty()) {
		Edge edge_least_weight = minPQ_.top(); //get the edge of lowest weight
		minPQ_.pop(); //remove that edge
		Node* src = edge_least_weight.getSourceNode();
		Node* dest = edge_least_weight.getDestinationNode();
		if (src->wasVisited() && dest->wasVisited()) { //skip edges between nodes already explored
			continue;
		};
		MST_.push(edge_least_weight);
		if (!src->wasVisited()) {
			findMST(*src);
		};
		if (!dest->wasVisited()) {
			findMST(*dest);
		};
	}
	return MST_;
}
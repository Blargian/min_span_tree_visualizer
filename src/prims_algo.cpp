#include "prims_algo.h"
#include "snapshot.h"

using namespace std;

PrimsAlgorithm::PrimsAlgorithm() {
};

PrimsAlgorithm::~PrimsAlgorithm() {
};

queue<Edge> PrimsAlgorithm::findMST(Node& startingNode) {
	increaseIteration(); 
	visitNode(startingNode, minPQ_);
	Snapshot current_iteration = Snapshot();

	while (!minPQ_.empty()) {
		Edge edge_least_weight = minPQ_.top(); //get the edge of lowest weight
		current_iteration.SetEdgeLeastWeight(edge_least_weight);
		current_iteration.AddPQ(minPQ_);
		minPQ_.pop(); //remove that edge
		Node* src = edge_least_weight.getSourceNode();
		Node* dest = edge_least_weight.getDestinationNode();
		if (src->wasVisited() && dest->wasVisited()) { //skip edges between nodes already explored
			continue;
		};
		MST_.push(edge_least_weight);
		current_iteration.AddMST(MST_);
		if (!src->wasVisited()) {
			findMST(*src);
		};
		if (!dest->wasVisited()) {
			findMST(*dest);
		};
	}
	
	AddSnapshot(current_iteration);
	return MST_;
}


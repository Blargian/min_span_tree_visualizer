#include "prims_algo.h"
#include "snapshot.h"

using namespace std;

PrimsAlgorithm::PrimsAlgorithm() {
};

PrimsAlgorithm::~PrimsAlgorithm() {
};

//Lazy version of Prims algorithm, including ineligible edges in priority queue 
queue<Edge> PrimsAlgorithm::findMST(Node& startingNode) {
	increaseIteration(); 
	visitNode(startingNode, minPQ_);
	Snapshot current_iteration = Snapshot();

	while (!minPQ_.empty()) {
		Edge edge_least_weight = minPQ_.top(); //get the edge of lowest weight
		current_iteration.SetEdgeLeastWeight(edge_least_weight);
		minPQ_.pop(); //remove that edge
		current_iteration.AddPQ(minPQ_);
		Node* src = edge_least_weight.getSourceNode();
		Node* dest = edge_least_weight.getDestinationNode();
		if (src->wasVisited() && dest->wasVisited()) { //skip edges between nodes already explored
			continue;
		};
		current_iteration.AddMST(MST_);
		AddSnapshot(current_iteration);
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


#include "kruskals_algo.h"
#include "edge.h"
#include "snapshot.h"

KruskalsAlgorithm::KruskalsAlgorithm() {};

KruskalsAlgorithm::KruskalsAlgorithm(Graph& g) {
	g_ = g;
	uf_ = UnionFind(g.getNodeCount());

	auto edges = g.getEdges();
	for (auto& edge : edges) {
		minPQ_.push(edge);
	}
};

KruskalsAlgorithm::~KruskalsAlgorithm() {
};

std::queue<Edge> KruskalsAlgorithm::findMST(Node& startingNode) {
	Snapshot current_iteration = Snapshot();
	while (!minPQ_.empty() && MST_.size() < g_.getNodeCount())
	{
		auto edge = minPQ_.top();
		current_iteration.SetEdgeLeastWeight(edge);
		minPQ_.pop();
		auto a = edge.getSourceNode();
		auto b = edge.getDestinationNode();
		if (uf_.Connected(a->getUFIID(),b->getUFIID())) continue;
		uf_.Union(a->getUFIID(), b->getUFIID());
		current_iteration.AddMST(MST_);
		MST_.push(edge);
		AddSnapshot(current_iteration);
		increaseIteration();
	}
	return MST_;
}

void KruskalsAlgorithm::clearAll() {
		
	if (solving_snapshots.size() != 0)
		solving_snapshots.clear();

	//clear MST_ 
	std::queue<Edge> empty_MST;
	std::swap(MST_, empty_MST);

	std::priority_queue<Edge, std::vector<Edge>, customLess> empty_pq;
	std::swap(minPQ_, empty_pq);
}

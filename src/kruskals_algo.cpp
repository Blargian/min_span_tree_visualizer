#include "kruskals_algo.h"
#include "edge.h"


KruskalsAlgorithm::KruskalsAlgorithm(Graph& g) {
	g_ = g;
	uf_ = UnionFind(g.getNodeCount());
	mst_ = std::queue<Edge>();

	auto edges = g.getEdges();
	for (auto& edge : edges) {
		minPQ_.push(edge);
	}
};

KruskalsAlgorithm::~KruskalsAlgorithm() {
};

std::queue<Edge> KruskalsAlgorithm::findMST() {
	while (!minPQ_.empty() && mst_.size() < g_.getNodeCount())
	{
		auto edge = minPQ_.top();
		minPQ_.pop();
		auto a = edge.getSourceNode();
		auto b = edge.getDestinationNode();
		if (uf_.Connected(a->getUFIID(),b->getUFIID())) continue;
		uf_.Union(a->getUFIID(), b->getUFIID());
		mst_.push(edge);
	}
	return mst_;
}

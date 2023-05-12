#pragma once
#include "mst_algo.h"
#include "union_find.h"
#include "graph.h"
#include <queue>

struct customLess {
	bool operator()(Edge l, Edge r) const
	{
		return l.getEdgeWeight() < r.getEdgeWeight();
	};
};

class KruskalsAlgorithm : public MSTAlgorithm {
private:
	Graph g_;
	std::queue<Edge> mst_;
	std::priority_queue<Edge,std::vector<Edge>, customLess> minPQ_;
	UnionFind uf_;
	int iterationCount_ = 0;
public:
	KruskalsAlgorithm(Graph& g);
	~KruskalsAlgorithm();
	std::queue<Edge> findMST();
};
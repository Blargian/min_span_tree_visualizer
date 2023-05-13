#pragma once
#include "mst_algo.h"
#include "union_find.h"
#include "graph.h"
#include <queue>

struct customLess {
	bool operator()(Edge l, Edge r) const
	{
		return l.getEdgeWeight() > r.getEdgeWeight();
	};
};

class KruskalsAlgorithm : public MSTAlgorithm {
private:
	Graph g_;
	std::priority_queue<Edge,std::vector<Edge>, customLess> minPQ_;
	UnionFind uf_;
public:
	KruskalsAlgorithm();
	KruskalsAlgorithm(Graph& g);
	~KruskalsAlgorithm();
	std::queue<Edge> findMST();
	void clearAll();
};
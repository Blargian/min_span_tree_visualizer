#pragma once
#include "mst_algo.h"

class PrimsAlgorithm : public MSTAlgorithm {
private:
	priority_queue<Edge, vector<Edge>, greater<Edge>> minPQ_;
public:
	PrimsAlgorithm();
	~PrimsAlgorithm();
	queue<Edge> findMST(Node& startingNode) override;
};
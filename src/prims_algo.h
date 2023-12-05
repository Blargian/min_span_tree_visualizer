#pragma once
#include "mst_algo.h"

class PrimsAlgorithm : public MSTAlgorithm {
private:
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> minPQ_;
public:
	PrimsAlgorithm();
	~PrimsAlgorithm();
    std::queue<Edge> findMST(Node& startingNode) override;
	void clearAll();
};
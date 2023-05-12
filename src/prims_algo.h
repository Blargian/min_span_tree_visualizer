#pragma once
#include "mst_algo.h"

class PrimsAlgorithm : public MSTAlgorithm {
private:
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> minPQ_;
	int iterationCount_ = 0;
public:
	PrimsAlgorithm();
	~PrimsAlgorithm();
	std::queue<Edge> findMST(Node& startingNode);
	void increaseIteration() { iterationCount_++; }; 
	void resetIterationCount() { iterationCount_ = 0; };
};
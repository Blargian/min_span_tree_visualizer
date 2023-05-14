#pragma once
#include "node_generator_interface.h"

class BestCandidateGenerator : public NodeGenerator {
private:
	int candidateSize_ = 10;
public:
	BestCandidateGenerator();
	BestCandidateGenerator(int candidateSize);
	virtual ~BestCandidateGenerator() {};
	std::vector<std::pair<int, int>> generatePoints(int n, int plot_width, int plot_height);
};

float distance(std::pair<int, int> a, std::pair<int, int> b);
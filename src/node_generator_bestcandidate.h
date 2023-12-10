#pragma once
#include "node_generator_interface.h"



class BestCandidateGenerator : public NodeGenerator {
private:
	int candidateSize_ = 10;
public:
	BestCandidateGenerator();
	BestCandidateGenerator(int candidateSize);
	virtual ~BestCandidateGenerator() {};
    std::vector<std::pair<int, int>> generatePoints(int n, const double plot_width, const double plot_height) override;
};

float distance(std::pair<int, int> a, std::pair<int, int> b);
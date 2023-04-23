#pragma once
#include "node_generator_interface.h"

class BestCandidateGenerator : public NodeGenerator {
private:
	int candidateSize_ = 10;
public:
	BestCandidateGenerator(int candidateSize);
	virtual ~BestCandidateGenerator() {};
	virtual std::vector<std::pair<int, int>> generatePoints(int n, int plot_width, int plot_height);
	std::vector<Node> generateNodes(int n, int plot_width, int plot_height);
};

int randomNumber(int min, int max);
float distance(std::pair<int, int> a, std::pair<int, int> b);
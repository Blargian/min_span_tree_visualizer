#pragma once
#include "node_generator_interface.h"

class UniformGenerator : public NodeGenerator {
private:
public:
	UniformGenerator();
	virtual ~UniformGenerator() {};
	std::vector<std::pair<int, int>> generatePoints(int n, int plot_width, int plot_height);
};

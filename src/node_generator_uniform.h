#pragma once
#include "node_generator_interface.h" 

class UniformGenerator : public NodeGenerator {
private:
public:
	UniformGenerator();
	virtual ~UniformGenerator() {};
    std::vector<std::pair<int, int>> generatePoints(int n, const double plot_width, const double plot_height) override;
};

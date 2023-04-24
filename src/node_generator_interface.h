#pragma once 
#include <vector>
#include "node.h"
#include <random>

//Interface for a node generator 
class NodeGenerator {
private:
public:
	virtual ~NodeGenerator() {};
	virtual std::vector<Node> generateNodes(int n, int plot_width, int plot_height) = 0;

	//generates a random number within the confines of some range
	int randomNumber(int min, int max) {
		//float random = (float) rand() / RAND_MAX;
		//return (int)(((float)rand() / (float)RAND_MAX)*(float)( max - min ) + (float)min);
		std::random_device rd;
		std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<> dis(min, max);
		auto num = dis(gen);
		return (int)(dis(gen));
	}
};


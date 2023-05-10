#pragma once 
#include "node.h"
#include <vector>
#include <utility>
#include <string>
#include <cmath>

//Interface for a node generator 
class EdgeGenerator {
private:
public:
	virtual ~EdgeGenerator() {};

	//edge weight is given as the euclidean distance between two nodes
	std::vector<double> generateWeightsEuclidean(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& edges) {
		std::vector<double> weights;
		for (auto& edge : edges) {
			double x = edge.second.first - edge.first.first;
			double y = edge.second.second - edge.first.second;
			auto distance = sqrt(pow(x,2) + pow(y, 2));
			weights.emplace_back(distance);
		}
		return weights;
	};

	//edge weight is randomly assigned as a value between 0 and 1
	std::vector<double> generateWeightsUniformRandom(size_t numberOfEdges) {
		std::vector<double> result = { 0.0 };
		return result;
	};
};




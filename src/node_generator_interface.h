#pragma once 
#include <vector>
#include "node.h"
#include <random>

//Interface for a node generator 
class NodeGenerator {
private:
public:
	virtual ~NodeGenerator() {};
	virtual std::vector<std::pair<int, int>> generatePoints(int n, const double plot_width, const double plot_height) = 0;

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

//pairhash so that unorder_set can make use of std::pair<T,T>
struct pairhash {
public:
	template <typename T, typename U>
	std::size_t operator()(const std::pair<T, U>& x) const
	{
		return std::hash<T>()(x.first)^std::hash<U>()(x.second);
	}
};


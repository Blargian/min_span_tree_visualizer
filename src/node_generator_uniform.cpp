#include "node_generator_uniform.h"

UniformGenerator::UniformGenerator() 
{
}

std::vector<Node> UniformGenerator::generateNodes(int n, int plot_width, int plot_height) {
	return std::vector<Node>();
}

std::vector<std::pair<int, int>> UniformGenerator::generatePoints(int n, int plot_width, int plot_height) {
	std::vector<std::pair<int, int>> points; 
	for (int i = 0; i < n; i++) {
		points.push_back(std::make_pair<int,int>(randomNumber(-1 * plot_width / 2, plot_width / 2), randomNumber(-1 * plot_width / 2, plot_width / 2)));
	}
	return points;
}
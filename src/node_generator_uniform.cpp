#include "node_generator_uniform.h"
#include <unordered_set>

UniformGenerator::UniformGenerator() 
{
}

std::vector<Node> UniformGenerator::generateNodes(int n, int plot_width, int plot_height) {
	return std::vector<Node>();
}

std::vector<std::pair<int, int>> UniformGenerator::generatePoints(int n, int plot_width, int plot_height) {

	std::unordered_set<std::pair<int, int>,pairhash> unique_points; //using a set to gaurantee unique values
	
	while (unique_points.size() != n) {
		auto point = std::make_pair<int, int>(randomNumber(-1 * plot_width / 2, plot_width / 2), randomNumber(-1 * plot_width / 2, plot_width / 2));
		unique_points.insert(point);
	}

	std::vector<std::pair<int, int>> points_vector(unique_points.size());
	copy(unique_points.begin(), unique_points.end(), points_vector.begin());

	return points_vector;
}
#include "node_generator_bestcandidate.h"
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>


BestCandidateGenerator::BestCandidateGenerator() {}
BestCandidateGenerator::BestCandidateGenerator(int candidateSize) {
	candidateSize_ = candidateSize;
}


/**
 * @brief Implements Mitchell's best candidate algorithm to pseudorandomly generate points within some grid space 
 * @param n int the number of points that need to be generated 
 *        plot_width int the width of the plot
 *        plot_height int the height of the plot
 */
std::vector<std::pair<int, int>> BestCandidateGenerator::generatePoints(int n, const double plot_width, const double plot_height) {

	std::vector<std::pair<int, int>> points; 
	std::pair<int, int> best_candidate; 
	float best_distance = -1.0;
	std::pair<int, int> closestPoint;
	float closestDistance = FLT_MAX;

	auto first_candidate = std::make_pair<int, int>(randomNumber(-1 * plot_width / 2, plot_width / 2), randomNumber(-1 * plot_height / 2, plot_height / 2));
	points.emplace_back(first_candidate);
 
	while (points.size() < n) {

		// Generate some candidates uniformly
	    // Point farthest away from the closest existing sample point wins out 				
		for (int i = 0; i < candidateSize_; i++) {
			
		auto candidate = std::make_pair<int, int>(randomNumber(-1*plot_width/2, plot_width/2), randomNumber(-1*plot_height/2, plot_height/2));
		
		//find the closest sample to the candidate
		for (auto& point : points) {
			if (distance(candidate, point) < closestDistance) {
				closestPoint = point;
			};
		}

		auto distance_to_closest = distance(closestPoint, candidate);
		if (distance_to_closest > best_distance) {
			best_distance = distance_to_closest;
			best_candidate = candidate;
			points.emplace_back(best_candidate);
		};

		};
	}
	
	return points; 
}

//calculates the distance between two pairs of points 
float distance(std::pair<int, int> a, std::pair<int, int> b) { 
	return sqrt(pow((b.first - a.first), 2) + pow((b.second - a.second), 2));
}
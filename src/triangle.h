#pragma once
#include <utility>
#include <vector>
#include <iomanip>
#include <iostream>

using edge = std::pair<std::pair<int, int>, std::pair<int, int>>;

class Triangle {

public:
	//member variables
	std::pair<int, int> A, B, C;
	std::pair<float, float> circumcenter = std::make_pair<float, float>(0.0, 0.0);
	float circumradius = 0.0;
	std::vector<edge> edges = {};
	std::vector<std::pair<int, int>> vertices = {};

	//methods
	Triangle(std::pair<int, int> n1, std::pair<int, int> n2, std::pair<int, int> n3);
	Triangle(const Triangle& t);
	void computeCircumcenter();
	void computeCircumradius();
	bool ContainsEdge(edge e);
	friend bool operator!=(Triangle a, Triangle b);
	friend bool operator<(Triangle a, Triangle b);
	friend bool operator==(const Triangle a, const Triangle b);
	friend std::ostream& operator<<(std::ostream& stream, Triangle const& e);
};

bool isAntiClockwise(std::pair<int, int> A, std::pair<int, int> B, std::pair<int, int> C);
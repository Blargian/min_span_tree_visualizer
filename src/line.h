#pragma once 
#include <utility>

class Line {

	public:
		Line(std::pair<int, int> src, std::pair<int, int> dest);
		float* getPointA();
		float* getPointB();

	private:
		float point_a[2] = {};
		float point_b[2] = {};
};
#include "line.h"

Line::Line(std::pair<int, int> src, std::pair<int, int> dest)
{
	point_a[0] = src.first;
	point_a[1] = dest.first;
	point_b[0] = src.second;
	point_b[1] = dest.second;
};

float* Line::getPointA() {
	return this->point_a;
};

float* Line::getPointB() {
	return this->point_b;
};
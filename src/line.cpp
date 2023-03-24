#include "line.h"

class Edge;

Line::Line(Edge e)
{
	pair<int, int> src = e.getSourceNode()->getXY();
	pair<int, int> dest = e.getDestinationNode()->getXY();
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

float Line::lineThickness() {
	return thickness;
}

ImVec4 Line::lineColour() {
	ImVec4 line_colour; 
	switch (colour) {
	case RED : line_colour = ImVec4(214, 15, 15, 1);
	case BLACK : line_colour = ImVec4(0, 0, 0, 1);
	default: line_colour = ImVec4(207, 206, 204, 1);
	}
	return line_colour;
}
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
	colour_ = LineColours::GREY;
};


float* Line::getPointA() {
	return point_a;
};

float* Line::getPointB() {
	return point_b;
};

float Line::lineThickness() {
	return thickness_;
}

ImVec4 Line::lineColour() {
	ImVec4 line_colour; 
	switch (colour_) {
	case LineColours::RED : 
		line_colour = ImColor(250, 103, 90);
		break;
	case LineColours::BLACK :
		line_colour = ImColor(15, 15, 15);
		break;
	default: 
		line_colour = ImColor(125, 124, 124);
		break;
	}
	return line_colour;
}
#include "line.h"
#include <memory>

using namespace std;


Line::Line(Edge& e)
{
	pair<int, int> src = e.getSourceNode()->getXY();
	pair<int, int> dest = e.getDestinationNode()->getXY();
	point_a[0] = src.first;
	point_a[1] = dest.first;
	point_b[0] = src.second;
	point_b[1] = dest.second;
	colour_ = LineColours::GREY;
};

Line::Line(std::pair<int, int> a, std::pair<int, int> b) {
	point_a[0] = a.first;
	point_a[1] = b.first;
	point_b[0] = a.second;
	point_b[1] = b.second;
	colour_ = LineColours::GREY;
	edgePtr_ = nullptr; 
}

Line::~Line() {

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

void Line::setLineColour(LineColours colour) {
	colour_ = colour;
}

void Line::setLineThickness(float thickness) {
	thickness_ = thickness;
}

void Line::setEdgePtr(Edge* edgePtr) {
	edgePtr_ = edgePtr; 
}
Edge* Line::getEdgePtr() {
	return edgePtr_;
}

void Line::resetLineToDefault() {
	thickness_ = 2.0;
	colour_ = LineColours::GREY;
}

bool operator==(Line a, Line b) {
	if (
		a.point_a[0] == b.point_a[0]
		&& a.point_a[1] == b.point_a[1]
		&& a.point_b[0] == b.point_b[0]
		&& a.point_b[1] == b.point_b[1]
		&& a.thickness_ == b.thickness_
		&& a.edgePtr_ == b.edgePtr_
		&& a.colour_ == b.colour_
		)
	{
		return true;
	}
	else {
		return false;
	}
};
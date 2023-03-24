#pragma once 
#include <utility>
#include "ImGui.h"
#include "Edge.h"

class Edge;

enum Colours {RED,BLACK};

class Line {

	public:
		Line(Edge e);
		float* getPointA();
		float* getPointB();
		float lineThickness();
		ImVec4 lineColour();
	private:
		float point_a[2] = {};
		float point_b[2] = {};
		float thickness = 2.0;
		Colours colour;
};
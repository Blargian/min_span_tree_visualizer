#pragma once 
#include <utility>
#include "ImGui.h"
#include "edge.h"

class Edge;

enum class LineColours {RED,BLACK, GREY};

class Line {

	public:
		Line(Edge& e);
		~Line();
		float* getPointA();
		float* getPointB();
		float lineThickness();
		ImVec4 lineColour();
		void setLineColour(LineColours color);
	private:
		float point_a[2] = {};
		float point_b[2] = {};
		float thickness_ = 2.0;
		LineColours colour_;
};
#pragma once 
#include "ImPlot.h"
#include <utility>
#include <memory>
#include "edge.h"

class Edge;

enum class LineColours {RED,BLACK, GREY};

class Line {
	private:
		float point_a[2] = {};
		float point_b[2] = {};
		float thickness_ = 2.0;
		LineColours colour_;
		std::weak_ptr<Edge> corresponding_edge_;
	public:
		Line(Edge& e);
		~Line();
		float* getPointA();
		float* getPointB();
		float lineThickness();
		ImVec4 lineColour();
		void setLineColour(LineColours color);
};
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
		Edge* edgePtr_;
	public:
		Line(Edge& e);
		Line(std::pair<int,int> a, std::pair<int,int> b); //used for testing edge_generators
		~Line();
		float* getPointA();
		float* getPointB();
		float lineThickness();
		ImVec4 lineColour();
		void setLineColour(LineColours color);
		void setEdgePtr(Edge* edgePtr);
		void setLineThickness(float thickness);
		Edge* getEdgePtr();
		friend bool operator==(Line a, Line b);
		void resetLineToDefault();
};
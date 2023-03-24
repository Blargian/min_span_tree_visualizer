#pragma once 
#include "Line.h"
#include "Graph.h"
#include "ImPlot.h"

class Draw {
private:
	vector<Line> lines; 
	vector<Marker> markers;
public:

}

void drawNodes(Graph& g);
void drawLines(vector<Line> lines);
void drawLine()
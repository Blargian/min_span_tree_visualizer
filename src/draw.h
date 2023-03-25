#pragma once 
#include "line.h"
#include "graph.h"
#include "ImPlot.h"
#include "marker.h"
#include <optional>

class Marker; 

class Draw {
private:
	vector<Line> lines_;
	vector<Marker> markers_;
public:
	vector<Line>& lines();
	vector<Marker>& markers();
	std::optional<Marker> findMarker(ImPlotPoint p);
};

void createPlot(Draw &d, int window_width, int window_height);
void checkPlotClicked(Draw& d);
void drawNodes(vector<Marker>);
void drawLines(vector<Line>);
void drawLine(Line);
void drawMarker(Marker);
void addMarkerToDraw(Marker m, vector<Marker>& markers);
void addLineToDraw(Line m,vector<Line>& lines);
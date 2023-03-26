#pragma once 
#include "line.h"
#include "graph.h"
#include "ImPlot.h"
#include "marker.h"

class Marker; 

class Draw {
private:
	vector<Line> lines_;
	vector<Marker> markers_;
	Marker* selectedMarker_ = NULL;
public:
	vector<Line>& lines();
	vector<Marker>& markers();
	Marker* findMarker(ImPlotPoint p, bool& found);
	void setSelectedMarker(Marker& m);
	Marker* selectedMarker();
	void changeMarkerColour(Marker* m, MarkerColours c);
};

void createPlot(Draw &d, int window_width, int window_height);
void checkPlotClicked(Draw& d);
void drawNodes(vector<Marker>);
void drawLines(vector<Line>);
void drawLine(Line);
void drawMarker(Marker);
void addMarkerToDraw(Marker m, vector<Marker>& markers);
void addLineToDraw(Line m,vector<Line>& lines);
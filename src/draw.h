#pragma once 
#include "line.h"
#include "graph.h"
#include "ImPlot.h"
#include "marker.h"
#include "prims_algo.h"
#include <memory>
#include <atomic>

class Marker; 
class Line; 

using SharedMarkerPtr = std::shared_ptr<class Marker>;
using SharedLinePtr = std::shared_ptr<class Line>;

class Draw {

private:
	vector<SharedLinePtr> lines_;
	vector<SharedMarkerPtr> markers_;
	SharedMarkerPtr selectedMarker_ = NULL;
public:
	vector<SharedLinePtr>& getLines();
	vector<SharedMarkerPtr>& getMarkers();
	SharedMarkerPtr findMarker(ImPlotPoint p, bool& found);
	SharedLinePtr findLine(Line& l, bool& found);
	void setSelectedMarker(SharedMarkerPtr m);
	SharedMarkerPtr selectedMarker();
	void changeMarkerColour(SharedMarkerPtr m, MarkerColours c);
	void changeLineColour(Line* m, LineColours c);
	void changeLineThickness(Line* l, float thickness);
	bool hasMarkersToDraw();
	bool hasLinesToDraw();
	void resetLinesToDefault();
};

void createPlot(Draw &d, int window_width, int window_height);
bool checkPlotClicked(Draw& d);
void drawNodes(vector<SharedMarkerPtr>);
void drawLines(vector<SharedLinePtr>);
void drawLine(Line);
void drawMarker(Marker);
SharedMarkerPtr addMarkerToDraw(SharedMarkerPtr m, vector<SharedMarkerPtr>& markers);
SharedLinePtr addLineToDraw(SharedLinePtr l,vector<SharedLinePtr>& lines);
void drawFromSnapshots(int iteration, vector<Snapshot> s, Draw& d);
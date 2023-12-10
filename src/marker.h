#pragma once 
#include "ImPlot.h"
#include <random>
#include <sstream>
#include "node.h"

class Node;

enum class MarkerColours { WHITE, GREY };

using SharedNodePtr = std::shared_ptr<class Node>;

class Marker {
private:
	ImPlotPoint coordinates_;
	const char* id_;
	MarkerColours markerColour_;
	SharedNodePtr nodePtr_ = nullptr; 
public:
	Marker(Node& n);
	Marker(Marker& m);
	~Marker();
	const char* id();
	ImVec4 markerColour();
	const ImPlotPoint coordinates();
	friend bool operator==(Marker a, Marker b);
	void setMarkerColour(MarkerColours color);
	void setNodePtr(SharedNodePtr nodePtr);
	SharedNodePtr getNodePtr();
};



/* This code is not mine, credit to happy_sisyphus on stackoverflow.com */
const char* generateSimpleUuid();

#pragma once 
#include "ImPlot.h"
#include "node.h"
#include <random>
#include <sstream>

class Node;

enum class MarkerColours { WHITE, GREY };

class Marker {
private:
	ImPlotPoint coordinates_;
	const char* id_;
	MarkerColours markerColour_;
	Node* corresponding_node_; 
public:
	Marker(Node& n);
	~Marker();
	const char* id();
	ImVec4 markerColour();
	const ImPlotPoint coordinates();
	friend bool operator==(Marker a, Marker b);
	void setMarkerColour(MarkerColours color);
};



/* This code is not mine, credit to happy_sisyphus on stackoverflow.com */
const char* generateSimpleUuid();

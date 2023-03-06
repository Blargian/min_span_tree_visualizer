#pragma once 
#include <vector>
#include "node.h"

using namespace std;

class Node; 

class Graph {
private:
	vector<Node> nodeArray; 
public:
	// Constructor
	Graph();
	void insertNode(Node n);
	vector<Node> getNodes(); 
}; 


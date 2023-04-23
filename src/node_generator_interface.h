#pragma once 
#include <vector>
#include "node.h"

//Interface for a node generator 
class NodeGenerator {
private:
public:
	virtual ~NodeGenerator() {};
	virtual std::vector<Node> generateNodes(int n, int plot_width, int plot_height) = 0;
};
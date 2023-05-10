#pragma once
#include "edge_generator_interface.h"
#include <vector>
#include "triangle.h"

using edge = std::pair<std::pair<int, int>, std::pair<int, int>>;

//Based on paper "An implementation of Watson's algorithm for computing 2-dimensional Delaunay triangulations" 

class DelaunayEdgeGenerator : public EdgeGenerator {
private:
public:
	DelaunayEdgeGenerator();
	virtual ~DelaunayEdgeGenerator() {};
	std::vector<Triangle> generateEdges(std::vector<std::pair<int,int>> points);
};

std::vector<std::pair<int, int>> sortAscending(std::vector<std::pair<int, int>> points);

Triangle findSuperTriangle(std::vector<std::pair<int, int>> points);

//functions used as comparison functions in std::sort 
bool smallestX(std::pair<int, int> a, std::pair<int, int> b);
bool smallestY(std::pair<int, int> a, std::pair<int, int> b);
bool biggestY(std::pair<int, int> a, std::pair<int, int> b);
bool smallestEdge(edge a, edge b);
std::vector<edge> removeDuplicateEdges(std::vector<edge> withDuplicates);
std::vector<edge> removeOneOfDuplicateEdges(std::vector<edge> withDuplicates);
std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> TrianglesToEdgeList(std::vector<Triangle>);

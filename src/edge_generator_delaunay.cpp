#include "edge_generator_delaunay.h"
#include <algorithm>
#include <random>
#include <cmath>
#include <assert.h>
#include <utility>
#include <set>

DelaunayEdgeGenerator::DelaunayEdgeGenerator() {

};

//comparator functions 

bool smallestX(std::pair<int, int> a, std::pair<int, int> b) { return (a.first < b.first); };
bool smallestY(std::pair<int, int> a, std::pair<int, int> b) { return (a.second < b.second); };
bool biggestY(std::pair<int, int> a, std::pair<int, int> b) { return (a.second > b.second); };
bool smallestEdge(edge a, edge b) { return (a.first < b.first); };

//Implements Bower-Watson algorithm for delaunay triangulation
std::vector<Triangle> DelaunayEdgeGenerator::generateEdges(std::vector<std::pair<int, int>> points) {

	auto sorted_points = sortAscending(points);
	auto super_triangle = findSuperTriangle(sorted_points);
	std::vector<Triangle> triangles_formed = { super_triangle };
	int number_triangles_previously = triangles_formed.size();

	//for each point perform triangulation
	for (auto point : points)
	{
		if (triangles_formed.size() != 1) {
			if (triangles_formed.size() != number_triangles_previously + 2) {
				assert(triangles_formed.size() == number_triangles_previously + 2);
			}
		}

		std::vector<Triangle> bad_triangles;

		//find bad triangles (triangles are bad if their circumcenters contain the point)
		for (auto i = 0; i < triangles_formed.size(); i++)
		{
			auto d = sqrt(pow(point.first - triangles_formed[i].circumcenter.first, 2) + pow(point.second - triangles_formed[i].circumcenter.second,2));
			d = roundf(d * 1000) / 1000;
			if (d < triangles_formed[i].circumradius)
			{
				bad_triangles.push_back(triangles_formed[i]);
			}
		}

		std::vector<edge> polygon;
		for (auto triangle : bad_triangles)
		{

			//if edge is not shared by any other triangles in badTriangles then add it to the polygon 
			for (auto edge : triangle.edges) {
				bool rejectEdge = false;
				for (auto bad_triangle : bad_triangles) {
					if ((bad_triangle != triangle) & (bad_triangle.ContainsEdge(edge))) { //using logical && here shortcircuits the second check
						rejectEdge = true;
					}
				}

				if (!rejectEdge) {
					polygon.push_back(edge);
				}
			}
		}

		number_triangles_previously = triangles_formed.size();
		//remove bad triangles from the triangles formed
		for (auto bad_triangle : bad_triangles) {
			auto it = remove(begin(triangles_formed), end(triangles_formed), bad_triangle);
			triangles_formed.erase(it,end(triangles_formed));
		}

		//remove duplicates from the polygon to ensure edges of polygon are unique 
		polygon = removeDuplicateEdges(polygon);

		//Create the new triangles 
		for (auto e : polygon) {
			triangles_formed.push_back(Triangle(point, e.first, e.second));
		}
		
	}

	auto formed = triangles_formed.size();
	auto should_be_formed = (2 * points.size() + 1);
	
	if (formed != should_be_formed) {
		std::cout << "an error occured while generating the delaunay triangulation: expected number of triangles was: " << should_be_formed << " ; but triangles formed were: " << formed << std::endl;
		for (auto point : points) {
			std::cout << "( " << point.first << "," << "" << point.second << " )" << std::endl;
		}
	}
	

	std::vector<std::pair<int, int>> super_triangle_vertices = { super_triangle.A,super_triangle.B,super_triangle.C };
	
	//form the final triangulation by removing all triangles containing one or more of the supertriangle vertices
	auto it = std::remove_if(std::begin(triangles_formed), std::end(triangles_formed), [super_triangle_vertices](Triangle t)
		{
			int vertexMatch = false;
			for (auto vertex : t.vertices) {
				if (vertex == super_triangle_vertices[0] || vertex == super_triangle_vertices[1] || vertex == super_triangle_vertices[2]) {
					vertexMatch = true;
					break;
				}
			}
			return vertexMatch;
		});
	triangles_formed.erase(it, std::end(triangles_formed));

	return triangles_formed;
};

//Quick-sorts points in ascending x order 
std::vector<std::pair<int, int>> sortAscending(std::vector<std::pair<int, int>> points) {
	
	std::sort(points.begin(),points.end(), smallestX);
	return points;
};

//Finds a triangle which contains all of the points passed to the function
Triangle findSuperTriangle(std::vector<std::pair<int, int>> sortedPoints) {

	//define a rectangular window encompassing all points to be triangulated 
	
	//we already sorted points by X before calling this function 
	auto xmin = (sortedPoints.begin())->first;
	auto xmax = (sortedPoints.end()-1)->first;

	auto ymin = (*min_element(sortedPoints.begin(), sortedPoints.end(), smallestY)).second;
	auto ymax = (*min_element(sortedPoints.begin(), sortedPoints.end(), biggestY)).second;

	auto dmax = 3 * std::max(xmax - xmin, ymax - ymin); 
	auto xcen = 0.5 * (xmin + xmax);
	auto ycen = 0.5 * (ymin + ymax);

	//co-ordinates of supertriangle vertices 
	auto x_nPlus1 = xcen - 0.866*dmax; 
	auto x_nPlus2 = xcen + 0.866 * dmax;
	auto x_nPlus3 = xcen;
	auto y_nPlus1 = ycen - 0.5*dmax;
	auto y_nPlus2 = ycen - 0.5*dmax; 
	auto y_nPlus3 = ycen + dmax; 

	return Triangle(std::make_pair<int, int>(x_nPlus1, y_nPlus1), std::make_pair<int, int>(x_nPlus2, y_nPlus2), std::make_pair<int, int>(x_nPlus3, y_nPlus3));

}

std::vector<edge> removeDuplicateEdges(std::vector<edge> withDuplicates) {

	auto polygon = withDuplicates;

	auto it = std::remove_if(begin(withDuplicates), end(withDuplicates), [withDuplicates](edge y)
		{
			for (auto x : withDuplicates)
			{
				if (x.first == y.second)
				{
					if (y.first == x.second)
					{
						return true;
					}
				}
			}
			return false; 
		});
		withDuplicates.erase(it, end(withDuplicates)); 
		return withDuplicates;

	//return polygon;
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> TrianglesToEdgeList(std::vector<Triangle> triangles) {
	
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> edges;
	for (auto t : triangles) {
		for (auto e : t.edges) {
			edges.emplace_back(e);
		}
	}
	return edges;
}
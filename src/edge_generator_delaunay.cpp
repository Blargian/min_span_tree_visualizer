#include "edge_generator_delaunay.h"
#include <algorithm>
#include <random>
#include <cmath>
#include <assert.h>
#include <utility>

DelaunayEdgeGenerator::DelaunayEdgeGenerator() {

};

bool smallestX(std::pair<int, int> a, std::pair<int, int> b) { return (a.first < b.first); };
bool smallestY(std::pair<int, int> a, std::pair<int, int> b) { return (a.second < b.second); };
bool biggestY(std::pair<int, int> a, std::pair<int, int> b) { return (a.second > b.second); };
bool smallestEdge(edge a, edge b) { return (a.first < b.first); };
bool smallestTriangle(Triangle a, Triangle b) { return (a.A.first < b.A.first) && (a.B.first < b.B.first) && (a.C.first < b.C.first); };
bool containedIn(Triangle a, std::vector<Triangle> b) {
	for (auto triangle : b) {
		if (a == triangle) {
			return true;
		}
	}
	return false;
}
bool trianglesEqual(Triangle a, Triangle b) {
	if(
		a.A == b.A
		&& a.B == b.B
		&& a.C == b.C
	){
		return true;
	}
	else {
		return false;
	}
	 
};

//Implements Bower-Watson algorithm for delaunay triangulation
std::vector<Triangle> DelaunayEdgeGenerator::generateEdges(std::vector<std::pair<int, int>> points) {
	auto sorted_points = sortAscending(points);
	auto super_triangle = findSuperTriangle(sorted_points);
	std::vector<Triangle> triangles_formed = { super_triangle };

	//for each point perform triangulation
	for (auto point : points)
	{
		std::vector<Triangle> bad_triangles;

		//find bad triangles (triangles are bad if their circumcenters contain the point)
		for (auto i = 0; i < triangles_formed.size(); i++)
		{
			auto d = sqrt(pow(point.first - triangles_formed[i].circumcenter.first, 2) + pow(point.second - triangles_formed[i].circumcenter.second,2));
			if (d < triangles_formed[i].circumradius) //or d <= r put another way 
			{
				bad_triangles.push_back(triangles_formed[i]);
			}
		}

		std::vector<edge> polygon;
		for (auto triangle : bad_triangles)
		{

			//if edge is not shared by any other triangles in badTriangles then add it to the polygon 
			bool rejectEdge = false;
			for (auto edge : triangle.edges) {
				for (auto bad_triangle : bad_triangles) {
					if ((bad_triangle != triangle) && bad_triangle.ContainsEdge(edge)) {
						rejectEdge = true;
					}
				}

				if (!rejectEdge) {
					polygon.push_back(edge);
				}
			}
		}

		//remove duplicate bad triangles
		std::sort(bad_triangles.begin(), bad_triangles.end(),smallestTriangle);
		bad_triangles.erase(std::unique(bad_triangles.begin(), bad_triangles.end(), trianglesEqual), bad_triangles.end());

		std::cout << "size of triangles_formed is: " << triangles_formed.size() << std::endl;
		std::cout << "size of bad_tringles is: " << bad_triangles.size() << std::endl;
		for (auto triangle : triangles_formed) {
			std::cout << triangle << std::endl;
		}

		auto ib = bad_triangles.begin();
		auto iter = std::remove_if(
			triangles_formed.begin(), triangles_formed.end(),
			[&ib, &bad_triangles](Triangle t) -> bool {
				while (ib != bad_triangles.end() && *ib != t) 
					++ib;
				return (ib != bad_triangles.end() && *ib == t);
			});
		
		for (auto edge_of_poly : polygon) {
			triangles_formed.push_back(Triangle(std::make_pair(point.first, point.second), edge_of_poly.first, edge_of_poly.second));
		}
	}

	std::cout << "triangles formed: " << triangles_formed.size() << std::endl;
	std::cout << "triangles that should be formed: " << (2 * points.size() + 1) << std::endl;
	assert(triangles_formed.size() == (2 * points.size() + 1)); 

	std::vector<std::pair<int, int>> super_triangle_vertices = { super_triangle.A,super_triangle.B,super_triangle.C };
	//form the final triangulation by removing all triangles containing one or more of the supertriangle vertices 
	for (auto triangle = triangles_formed.begin(); triangle != triangles_formed.end(); ++triangle) {
		for (auto super_vertice : super_triangle_vertices) {
			if (super_vertice == triangle->A || super_vertice == triangle->B || super_vertice == triangle->C) {
				triangle = triangles_formed.erase(triangle);
			}
		}
	};

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
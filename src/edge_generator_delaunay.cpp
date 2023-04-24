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

struct Compare final
{
	bool operator()(const Triangle& a, const Triangle& b) const noexcept
	{
		//because ordering a triangle by it's vertices does not make physical sense, we will order by the area of the triangle instead

		//thus compute first the area of both triangles
		auto area_a = a.A.first * (a.B.second - a.C.second) + a.B.first * (a.C.second - a.A.second) + a.C.first * (a.A.second - a.B.second);
		auto area_b = b.A.first * (b.B.second - b.C.second) + b.B.first * (b.C.second - b.A.second) + b.C.first * (b.A.second - b.B.second);
		return area_a < area_b;
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

		//remove duplicate bad triangles and sort by area as part of that process
		bad_triangles = removeDuplicates(bad_triangles);

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

		//remove from the triangles_formed any of the bad triangles
		std::cout << "before removing bad triangles: " << triangles_formed.size() << std::endl; 
		triangles_formed.erase(std::remove_if(begin(triangles_formed), end(triangles_formed),
			[&](auto x) {return std::binary_search(begin(bad_triangles), end(bad_triangles), x); }), end(triangles_formed)
		);
		std::cout << "after removing bad triangles: " << triangles_formed.size() << std::endl;

		//Create the new triangles 
		for (auto e : polygon) {
			triangles_formed.push_back(Triangle(point, e.first, e.second));
		}
		
	}

	std::cout << "triangles formed: " << triangles_formed.size() << std::endl;
	std::cout << "triangles that should be formed: " << (2 * points.size() + 1) << std::endl;
	//assert(triangles_formed.size() == (2 * points.size() + 1)); 

	std::vector<std::pair<int, int>> super_triangle_vertices = { super_triangle.A,super_triangle.B,super_triangle.C };
	//form the final triangulation by removing all triangles containing one or more of the supertriangle vertices 

	std::cout << "before removing supra triangles: " << triangles_formed.size() << std::endl;
	for (auto triangle : triangles_formed) {
		for (auto supra_edge : super_triangle.edges) {
			triangles_formed.erase(std::remove_if(begin(triangles_formed), end(triangles_formed), [&supra_edge](const Triangle& triangle)
				{
					return triangle.edges[0] == supra_edge || triangle.edges[1] == supra_edge || triangle.edges[2] == supra_edge;
				}
			), end(triangles_formed));
		}
	};
	std::cout << "after removing supra triangles: " << triangles_formed.size() << std::endl;

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

std::vector<Triangle> removeDuplicates(std::vector<Triangle> withDuplicates) {

	std::set<Triangle, Compare> no_duplicates(withDuplicates.begin(), withDuplicates.end());
	std::vector<Triangle> without_duplicates;
	without_duplicates.assign(no_duplicates.begin(), no_duplicates.end()); 
	return without_duplicates;
}
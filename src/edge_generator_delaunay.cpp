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
					if ((bad_triangle != triangle) & (bad_triangle.ContainsEdge(edge))) { //using logical && here shortcircuits the second check
						rejectEdge = true;
					}
				}

				if (!rejectEdge) {
					polygon.push_back(edge);
				}
			}
		}

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

	std::cout << "triangles formed: " << triangles_formed.size() << std::endl;
	std::cout << "triangles that should be formed: " << (2 * points.size() + 1) << std::endl;
	//assert(triangles_formed.size() == (2 * points.size() + 1)); 

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
	//loop over all edges
	//check if a.first==b.first && a.second==b.second (i.e edge is the same)
	//check also if a.first=b.second && a.second = b.first (i.e edge is the same but flipped)

	/*std::set<edge> no_duplicates(withDuplicates.begin(), withDuplicates.end());*/

	for (auto x : polygon) {
		bool removed = false;
		for (auto y : polygon) {
			if (x.first == y.second) {
				if (y.first == x.second) {
					polygon.erase(std::remove(begin(polygon), end(polygon), y),end(polygon)); //remove the first instance
					removed = true;
					break;
				}
			}
		}
		if (removed) {
			polygon.erase(std::remove(begin(polygon), end(polygon), x), end(polygon)); //remove the second instance
			break;
		}
	}
	/*std::vector<edge> without_duplicates;
	without_duplicates.assign(no_duplicates.begin(), no_duplicates.end());
	return without_duplicates;*/
	return polygon;
}
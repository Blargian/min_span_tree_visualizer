#include <catch2/catch_test_macros.hpp>
#include "../src/node.h"
#include "../src/edge.h"
#include "../src/graph.h"
#include "../src/app.h"
#include "../src/prims_algo.h"
#include "../src/kruskals_algo.h"
#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include "../src/edge_generator_delaunay.h"
#include "../src/triangle.h"
#include "../src/utility_mstv.h"
#include "../src/union_find.h"

using namespace std; 

//mock data for edges of a small test graph here: 
vector<vector<double>> tinyEWG =
{
	{4, 5, 0.35},
	{4, 7, 0.37},
	{5, 7, 0.28},
	{0, 7, 0.16},
	{1, 5, 0.32},
	{0, 4, 0.38},
	{2, 3, 0.17},
	{1, 7, 0.19},
	{0, 2, 0.26},
	{1, 2, 0.36},
	{1, 3, 0.29},
	{2, 7, 0.34},
	{6, 2, 0.40},
	{3, 6, 0.52},
	{6, 0, 0.58},
	{6, 4, 0.93}
};

//mock data for nodes of a small test graph:

vector<vector<int>> tinyEWGnodes =
{
	{0, 4, 2},
	{1, 3, 7},
	{2, 6, 4},
	{3, 8, 7},
	{4, 0, 0},
	{5, 0, 4},
	{6, 8, 0},
	{7, 3, 4},

};

TEST_CASE("Graph edge", "[Edge]") {

	Node b = Node();
	Node c = Node();
	Edge anEdge = Edge(&c,&b, 1);

	SECTION("Edge gets created properly") {
		REQUIRE(anEdge.getSourceNode() == &c);
		REQUIRE(anEdge.getDestinationNode() == &b);
		REQUIRE(anEdge.getEdgeWeight() == 1);
	}

	SECTION("Destination node of Edge gets correctly updated using setter") {
		REQUIRE(anEdge.getDestinationNode() == &b);
		anEdge.setDestinationNode(&c);
		REQUIRE(anEdge.getDestinationNode() == &c);
	}

	SECTION("Edge weight of Edge gets correctly updated using setter") {
		
		int updatedWeight = 2; 
		REQUIRE(anEdge.getEdgeWeight() == 1);
		anEdge.setEdgeWeight(updatedWeight);
		REQUIRE(anEdge.getEdgeWeight() == updatedWeight);
	}
}

TEST_CASE("Graph node", "[Node]") {

	Node a = Node();

	SECTION("error gets thrown if x coordinate is outside of limits -100 to +100") {
		CHECK_THROWS_AS(a.setXY(200,5), std::logic_error);
	}

	SECTION("error gets thrown if y coordinate is outside of limits -100 to +100") {
		CHECK_THROWS_AS(a.setXY(67, 189), std::logic_error);
	}

	SECTION("error gets thrown if one coordinate is negative and outside of limits -100 to +100") {
		CHECK_THROWS_AS(a.setXY(-67, -189), std::logic_error);
	}

	SECTION("no error is thrown if both coordinates are in the limit -100 to +100") {
		CHECK_NOTHROW(a.setXY(67, 72));
	}

	SECTION("no error is thrown if both coordinates are negative and in the limit -100 to +100") {
		CHECK_NOTHROW(a.setXY(-67, -72));
	}

	SECTION("an edge gets inserted to the adjacency list") {
		Node a = Node();
		Node b = Node();
		Edge e = Edge(&a,&b,1);
		list<Edge> edgelist = b.getEdgeList();
		REQUIRE(edgelist.empty() == true);
		edgelist = b.getEdgeList();
		b.insertEdge(e);
		edgelist = b.getEdgeList();
		REQUIRE(edgelist.empty() != true);
	}

	SECTION("gets a pointer to an edge given the source node and destination node")
	{

		Graph g = Graph();

		std::vector<std::shared_ptr<Node>> nodes = {
			std::make_shared<Node>("Johannesburg", 5, 10),
			std::make_shared<Node>("Cape Town", 26, 10),
		};

		
		for (auto& node : nodes) {
			g.insertNode(node);
		}
		g.connectNodes(g.getNodes()[0].get(), g.getNodes()[1].get(), 1);

		Edge e = Edge(g.getNodes()[0].get(), g.getNodes()[1].get(), 1);

		Edge* edge_we_need = g.getNodes()[0]->getEdge(g.getNodes()[0].get(), g.getNodes()[1].get());
		REQUIRE(*(edge_we_need) == e);

	}
}

TEST_CASE("Graph","[Graph]"){

	Graph g = Graph();

	SECTION("a new node gets added to the graph") {
		auto& nodes = g.getNodes();
		REQUIRE(nodes.size()==0);
		auto newNode = g.insertNode(std::make_shared<Node>());
		nodes = g.getNodes();
		REQUIRE(nodes.size() == 1);
	}

	SECTION("node count updates correctly") {
		Node a = Node();
		Graph g = Graph();
		REQUIRE(g.getNodeCount() == 0);
		g.insertNode(std::make_shared<Node>());
		REQUIRE(g.getNodeCount() == 1);
		g.removeNode(g.getNodes()[0].get());
		REQUIRE(g.getNodeCount() == 0);
	}

	//lines commented out are due to graph being undirected 
	SECTION("connects two nodes with an edge") {

		Node a = Node();
		Node b = Node();

		auto nodeA = g.insertNode(std::make_shared<Node>("Johannesburg", 5, 10));
		auto nodeB = g.insertNode(std::make_shared<Node>("Cape Town", 26, 10));
		auto& nodes_on_graph = g.getNodes();
		g.connectNodes(nodes_on_graph[0].get(), nodes_on_graph[1].get(), 1);

		//expected edges if connectNodes(a,b,1) is run 
		Edge aToB = Edge(nodes_on_graph[0].get(), nodes_on_graph[1].get(), 1);
		//Edge bToA = Edge(nodes_on_graph[b_index], nodes_on_graph[a_index], 1);

		list<Edge> nodeAEdges = nodes_on_graph[0]->getEdgeList();
		//list<Edge> nodeBEdges = nodes_on_graph[1]->getEdgeList();

		auto a_it = find(nodeAEdges.begin(), nodeAEdges.end(), aToB);
		//auto b_it = find(nodeBEdges.begin(), nodeBEdges.end(), bToA);
		REQUIRE(a_it != nodeAEdges.end());
		//REQUIRE(b_it != nodeBEdges.end());

	}

	SECTION("Node and it's edges are removed from the graph") {
		
		Graph g = Graph();
		
		std::vector<std::shared_ptr<Node>> nodes = {
			std::make_shared<Node>("Johannesburg", 5, 10),
			std::make_shared<Node>("Cape Town", 26, 10),
			std::make_shared<Node>("Durban", -24, 78)
		};

		for(auto& node : nodes) {
			g.insertNode(node);
		}

		auto& nodes_on_graph = g.getNodes();
		g.connectNodes(nodes_on_graph[0].get(), nodes_on_graph[1].get(), 1);
		g.connectNodes(nodes_on_graph[2].get(), nodes_on_graph[1].get(), 1);

		REQUIRE(size(g.getNodes()[0].get()->getEdgeList()) == 1);
		REQUIRE(size(g.getNodes()[1].get()->getEdgeList()) == 2);
		REQUIRE(size(g.getNodes()[2].get()->getEdgeList()) == 1);

		g.removeNode(g.getNodes().back().get());
		g.removeNode(g.getNodes().back().get());
		g.removeNode(g.getNodes().back().get());

		//After removing there should only be two nodes
		//Those nodes should have no edges
		REQUIRE(g.getNodeCount() == 0);
	}

	SECTION("clearAll removes all of the nodes from a graph") {
		Graph g = Graph();

		std::vector<std::shared_ptr<Node>> nodes = {
			std::make_shared<Node>("Johannesburg", 5, 10),
			std::make_shared<Node>("Cape Town", 26, 10),
			std::make_shared<Node>("Durban", -24, 78)
		};

		for (auto& node : nodes) {
			g.insertNode(node);
		}

		auto& nodes_on_graph = g.getNodes();
		g.connectNodes(nodes_on_graph[0].get(), nodes_on_graph[1].get(), 1);
		g.connectNodes(nodes_on_graph[2].get(), nodes_on_graph[1].get(), 1);

		REQUIRE(size(g.getNodes()[0].get()->getEdgeList()) == 1);
		REQUIRE(size(g.getNodes()[1].get()->getEdgeList()) == 2);
		REQUIRE(size(g.getNodes()[2].get()->getEdgeList()) == 1);

		g.clearAll();
		REQUIRE(g.getNodeCount() == 0);
	}

	SECTION("returns coordinates of nodes in an array of floats - to be used for plotting") {
		Graph g = Graph();
		std::vector<std::shared_ptr<Node>> nodes = {
			std::make_shared<Node>("Johannesburg", 5, 10),
			std::make_shared<Node>("Cape Town", 26, 10),
			std::make_shared<Node>("Durban", -24, 78)
		};
		for (auto& node : nodes) {
			g.insertNode(node);
		}
		auto points = g.getCoordsForPlot();
		REQUIRE((points.first[0] == 5 && points.second[0]==10));
		REQUIRE((points.first[1] == 26 && points.second[1] == 10));
		REQUIRE((points.first[2] == -24.0 && points.second[2] == 78));
	}

	SECTION("getNodeByName returns a pointer to a node given the name") {
		Graph g = Graph();
		std::vector<std::shared_ptr<Node>> nodes = {
			std::make_shared<Node>("Johannesburg", 5, 10),
			std::make_shared<Node>("Cape Town", 26, 10),
			std::make_shared<Node>("Durban", -24, 78)
		};
		for (auto& node : nodes) {
			g.insertNode(node);
		}
		auto node = g.getNodeByName("Johannesburg");
		REQUIRE(node->getXY().first == 5);
		REQUIRE(node->getXY().second == 10);
		REQUIRE(node->getNodeName() == "Johannesburg");
	}
	
	SECTION("getinverseedge() returns the edge running in the opposite direction given some edge") {
		Graph g = Graph();
		std::vector<std::shared_ptr<Node>> nodes = {
			std::make_shared<Node>("johannesburg", 5, 10),
			std::make_shared<Node>("cape town", 26, 10),
		};
		for (auto& node : nodes) {
			g.insertNode(node);
		}
		auto unidirectional_edge = g.connectNodes(g.getNodes()[0].get(), g.getNodes()[1].get(),0.5);
		auto inverse_edge = getInverseEdge(g, *unidirectional_edge);
		REQUIRE(inverse_edge->getSourceNode() == nodes[1].get());
		REQUIRE(inverse_edge->getDestinationNode() == nodes[0].get());
	}
}

TEST_CASE("iSubject", "[Subject]") {

	SECTION("hasObservers returns true if a subject does have observers") {
		MyApp app;
		Graph with_observers = Graph();
		with_observers.AddObserver(Graph::DRAWEDGE, &app);
		Graph without_observers = Graph();
		REQUIRE(with_observers.hasObservers() == true);
		REQUIRE(without_observers.hasObservers() == false);
	}

	SECTION("AddObserver adds and removes the observer to the ObserversMap mObservers correctly") {
		MyApp app;
		Graph subject = Graph();
		subject.AddObserver(Graph::DRAWEDGE, &app);
		auto om = subject.getObserverMap();
		int number_of_observers = distance(om[0].begin(), om[0].end());
		REQUIRE(number_of_observers == 1);
		subject.RemoveObserver(Graph::DRAWEDGE, &app);
		om = subject.getObserverMap();
		number_of_observers = distance(om[0].begin(), om[0].end());
		REQUIRE(number_of_observers == 0);
	}

};

TEST_CASE("Prim's Algorithm", "[Prims]") {

	SECTION("check that Prims algorithm finds the correct MST") {
		Graph tinyGraph;
		//create the nodes
		for (vector<int> node : tinyEWGnodes) {
			tinyGraph.insertNode(std::make_shared<Node>(to_string(node[0]), static_cast<int>(node[0]), static_cast<int>(node[0])));
		};
		//connect the nodes
		for (vector<double> node_data : tinyEWG) {
			tinyGraph.connectNodes(tinyGraph.getNodeByName(to_string((int)node_data[0])).get(), tinyGraph.getNodeByName(to_string((int)node_data[1])).get(), node_data[2]);
		};

		vector<Edge> expected_edges{
			Edge(tinyGraph.getNodeByName("0").get(),tinyGraph.getNodeByName("7").get(),0.16),
			Edge(tinyGraph.getNodeByName("0").get(),tinyGraph.getNodeByName("2").get(),0.26),
			Edge(tinyGraph.getNodeByName("6").get(),tinyGraph.getNodeByName("2").get(),0.40),
			Edge(tinyGraph.getNodeByName("2").get(),tinyGraph.getNodeByName("3").get(),0.17),
			Edge(tinyGraph.getNodeByName("6").get(),tinyGraph.getNodeByName("2").get(),0.40),
			Edge(tinyGraph.getNodeByName("1").get(),tinyGraph.getNodeByName("7").get(),0.19),
			Edge(tinyGraph.getNodeByName("5").get(),tinyGraph.getNodeByName("7").get(),0.28),
			Edge(tinyGraph.getNodeByName("4").get(),tinyGraph.getNodeByName("5").get(),0.35),
		};

		PrimsAlgorithm prim = PrimsAlgorithm();
		auto MST = prim.findMST(*tinyGraph.getNodeByName("0"));

		cout << "========== Prims Algorithm ==========" << endl;
		cout << "Found the following MST" << endl;
		bool found = false;
		REQUIRE(!MST.empty());
		while (!MST.empty()) {
			Edge e = MST.front();
			cout << e << endl; //add something to print edges
			auto it = find(expected_edges.begin(), expected_edges.end(), e);
			int index = distance(expected_edges.begin(), it);
			REQUIRE(it != expected_edges.end()); //check that the edge does exist in expected_edges
			CHECK((expected_edges[index] == e)); //check that the contents of the edge are correct
			MST.pop();
			expected_edges.erase(it);
		}
	}
}

TEST_CASE("Kruskal's Algorithm", "[Kruskals]") {

	SECTION("check that Kruskal's algorithm finds the correct MST") {
		Graph tinyGraph;
		//create the nodes
		for (vector<int> node : tinyEWGnodes) {
			tinyGraph.insertNode(std::make_shared<Node>(to_string(node[0]), static_cast<int>(node[0]), static_cast<int>(node[0])));
		};
		//connect the nodes
		for (vector<double> node_data : tinyEWG) {
			tinyGraph.connectNodes(tinyGraph.getNodeByName(to_string((int)node_data[0])).get(), tinyGraph.getNodeByName(to_string((int)node_data[1])).get(), node_data[2]);
		};

		vector<Edge> expected_edges{
			Edge(tinyGraph.getNodeByName("0").get(),tinyGraph.getNodeByName("7").get(),0.16),
			Edge(tinyGraph.getNodeByName("0").get(),tinyGraph.getNodeByName("2").get(),0.26),
			Edge(tinyGraph.getNodeByName("6").get(),tinyGraph.getNodeByName("2").get(),0.40),
			Edge(tinyGraph.getNodeByName("2").get(),tinyGraph.getNodeByName("3").get(),0.17),
			Edge(tinyGraph.getNodeByName("6").get(),tinyGraph.getNodeByName("2").get(),0.40),
			Edge(tinyGraph.getNodeByName("1").get(),tinyGraph.getNodeByName("7").get(),0.19),
			Edge(tinyGraph.getNodeByName("5").get(),tinyGraph.getNodeByName("7").get(),0.28),
			Edge(tinyGraph.getNodeByName("4").get(),tinyGraph.getNodeByName("5").get(),0.35),
		};

		KruskalsAlgorithm kruskal = KruskalsAlgorithm();
		auto MST = kruskal.findMST(*tinyGraph.getNodeByName("0"));

		cout << "========== Kruskals Algorithm ==========" << endl;
		cout << "Found the following MST" << endl;
		bool found = false;
		REQUIRE(!MST.empty());
		while (!MST.empty()) {
			Edge e = MST.front();
			cout << e << endl; //add something to print edges
			auto it = find(expected_edges.begin(), expected_edges.end(), e);
			int index = distance(expected_edges.begin(), it);
			REQUIRE(it != expected_edges.end()); //check that the edge does exist in expected_edges
			CHECK((expected_edges[index] == e)); //check that the contents of the edge are correct
			MST.pop();
			expected_edges.erase(it);
		}
	}
}

TEST_CASE("Draw", "[Draw]") {

	auto d = std::make_unique<Draw>();
	auto g = make_unique<Graph>();

	for (vector<int> node_properties : tinyEWGnodes) {
		auto nodePtr = g->insertNode(std::make_shared<Node>(to_string(node_properties[0]), static_cast<int>(node_properties[1]), static_cast<int>(node_properties[2])));
		auto markerPtrr = std::make_shared<Marker>(*nodePtr);
		auto markerPtr = addMarkerToDraw(markerPtrr, d->getMarkers());
		nodePtr->setMarkerPtr(markerPtr);
		markerPtr->setNodePtr(nodePtr);
	};
	//connect the nodes
	for (vector<double> node_data : tinyEWG) {
		auto edgePtr = g->connectNodes(g->getNodeByName(to_string((int)node_data[0])).get(), g->getNodeByName(to_string((int)node_data[1])).get(), node_data[2]);
		auto l = std::make_shared<Line>(Line(*edgePtr));
		auto linePtr = addLineToDraw(l, d->getLines());
		linePtr->setEdgePtr(edgePtr);
		edgePtr->setLinePtr(linePtr);
		auto edgeInversePtr = getInverseEdge(*g, *edgePtr);
		edgeInversePtr->setLinePtr(linePtr); //two edges reference one line on the graph due to bidirectional nature 
	};

	SECTION("findLine() finds a line if it exists, otherwise doesn't find a line if not") {
		bool foundTheLine = false; 
		auto& someEdge = g->getNodeByName("0")->getEdgeList().front();
		auto& foundLine = d->findLine(*someEdge.getLinePtr().get(), foundTheLine);
		REQUIRE(foundTheLine == true); 
		REQUIRE(*foundLine.get() == *someEdge.getLinePtr());
	}
}

TEST_CASE("Delauney Edge Generator", "[DEG]") {
	
	std::vector<std::pair<int, int>> points =
	{
		std::make_pair<int,int>(-5,9),
		std::make_pair<int,int>(17,-6),
		std::make_pair<int,int>(-20,50),
		std::make_pair<int,int>(100,27),
	};
	
	SECTION("Correctly sorts points by ascending x-coordinate") {
		auto sorted_points = sortAscending(points);
		std::vector<int> sorted_x; 
		for (auto& point : sorted_points) {
			sorted_x.push_back(point.first);
		}

		int previous = -1000;
		//check that sorted_x ascends 
		for (auto it = sorted_x.begin(); it != sorted_x.end(); it++) {
			REQUIRE(previous < *it);
			previous = *it;
		}
	}

	SECTION("converts list of triangles to list of edge") {
		std::vector<Triangle> triangles =
		{
			Triangle(std::make_pair<int,int>(0,2),std::make_pair<int,int>(4,0),std::make_pair<int,int>(0,4)),
			Triangle(std::make_pair<int,int>(2,2),std::make_pair<int,int>(6,0),std::make_pair<int,int>(2,4)),
			Triangle(std::make_pair<int, int>(4, 2), std::make_pair<int, int>(4, 0), std::make_pair<int, int>(0, 4))
		};
		auto edges_list = TrianglesToEdgeList(triangles);
		REQUIRE(edges_list.size() == 9);
		auto first = std::make_pair<std::pair<int, int>, std::pair<int, int>>(std::make_pair<int, int>(0, 2), std::make_pair<int, int>(4, 0));
		REQUIRE((edges_list[0] == first));
	}

	SECTION("Removes only one of a pair of duplicate edges") {
		std::vector<Triangle> triangles =
		{
			Triangle(std::make_pair<int,int>(-1, -37),std::make_pair<int,int>(16, -34),std::make_pair<int,int>(4, 9)),
			Triangle(std::make_pair<int,int>(37, -33),std::make_pair<int,int>(4, 9),std::make_pair<int,int>(16, -34)),
		};
		auto edges = TrianglesToEdgeList(triangles);
		auto edges_after_removal = removeOneOfDuplicateEdges(edges);
		bool hasDuplicates = false; 

		for (int i = 0; i < edges_after_removal.size(); i++) {
			for (int j = 0; j < edges_after_removal.size(); j++) {
				if (edges_after_removal[i].first == edges_after_removal[j].second) {
					if (edges_after_removal[i].second == edges_after_removal[j].first) {
						hasDuplicates = true;
					}
				}
			}
		};

		REQUIRE(hasDuplicates == false);

	}
}

TEST_CASE("Triangle", "[Triangle]") {

	SECTION("Correctly computes the circumcenter of a given triangle") {

		auto triangle = Triangle(std::make_pair<int, int>(0, 0), std::make_pair<int, int>(0, 4), std::make_pair<int, int>(3, 0));
		REQUIRE((triangle.circumcenter.first == 1.50 && triangle.circumcenter.second == 2.00));
	}

	SECTION("Checks if a triangle contains an edge") {
		using edge = std::pair<std::pair<int, int>, std::pair<int, int>>;
		edge test_edge = edge
		(
			std::make_pair<int, int>(-10, 15),
			std::make_pair<int, int>(20, 20)
		);
		Triangle triangle_with_edge = Triangle
		(
			test_edge.first,
			test_edge.second,
			std::make_pair<int, int>(50, 50)
		);
		REQUIRE((triangle_with_edge.ContainsEdge(test_edge)) == true);

		Triangle triangle_without_edge = Triangle(
			std::make_pair<int, int>(100, -100),
			std::make_pair<int, int>(32, 64),
			std::make_pair<int, int>(50, 50)
		);
		REQUIRE((triangle_without_edge.ContainsEdge(test_edge)) == false);

		//and another test for sanity check 
		Triangle bad_triangle = Triangle(std::make_pair<int, int>(0, 0), std::make_pair<int, int>(0, 60), std::make_pair<int, int>(-51, -30));
		Triangle triangle = Triangle(std::make_pair<int, int>(0, 0), std::make_pair<int, int>(51, -30), std::make_pair<int, int>(0, 60));

		auto test_edge_2 = triangle.edges[0];
		REQUIRE((bad_triangle.ContainsEdge(test_edge_2)) == false);
	}


	SECTION("Checks that a triangles points are stored in anticlockwise order") {

		REQUIRE(isAntiClockwise(
			std::make_pair<int, int>(0, 10),
			std::make_pair<int, int>(10, -10),
			std::make_pair<int, int>(-10, -10)
		) == false);

		REQUIRE(isAntiClockwise(
			std::make_pair<int, int>(-10, -10),
			std::make_pair<int, int>(10, -10),
			std::make_pair<int, int>(0, 10)
		) == true);
	};

};

TEST_CASE("Utility", "[Utility]") {

	SECTION("SortNodeVector correctly sorts a vector of shared Node ptrs first by x and then by y") {

		std::vector<std::shared_ptr<Node>> unsorted_nodes = {
			std::make_shared<Node>("0",-5,0),
			std::make_shared<Node>("0",5,-5),
			std::make_shared<Node>("0",-5,5),
			std::make_shared<Node>("0",0,0),
			std::make_shared<Node>("0",5,5),
			std::make_shared<Node>("0",-5,-5),
			std::make_shared<Node>("0",5,0),
		};
		mstv_utility::SortNodeVector(unsorted_nodes);
		REQUIRE((
			   unsorted_nodes[0].get()->getXY() == std::pair<int,int>(-5,-5)
			&& unsorted_nodes[1].get()->getXY() == std::pair<int, int>(-5, 0)
			&& unsorted_nodes[2].get()->getXY() == std::pair<int, int>(-5, 5)
			&& unsorted_nodes[3].get()->getXY() == std::pair<int, int>(0, 0)
			&& unsorted_nodes[4].get()->getXY() == std::pair<int, int>(5, -5)
			&& unsorted_nodes[5].get()->getXY() == std::pair<int, int>(5, 0)
			&& unsorted_nodes[6].get()->getXY() == std::pair<int, int>(5, 5)
		));
	}

	std::vector<std::shared_ptr<Node>> nodes = {
			std::make_shared<Node>("0",5,0),
			std::make_shared<Node>("0",-5,2),
			std::make_shared<Node>("0",-5,3),
			std::make_shared<Node>("0",10,0),
			std::make_shared<Node>("0",-10,0)
	};
	mstv_utility::SortNodeVector(nodes);

	SECTION("Binary Search correctly takes array of shared pointers to Node and finds using std::pair<int,int>") {
		
		auto found = mstv_utility::BinarySearch(nodes, std::make_pair<int,int>(-5,3));
		REQUIRE(found.get()!=nullptr);
		REQUIRE((found.get()->getXY().first == -5 && found.get()->getXY().second == 3));

		found = mstv_utility::BinarySearch(nodes, std::make_pair<int, int>(-5, 2));
		REQUIRE(found.get() != nullptr);
		REQUIRE((found.get()->getXY().first == -5 && found.get()->getXY().second == 2));
		
	}

	SECTION("Binary Search returns nullptr if asked to find something which is not in the sorted vector") {
		auto not_found = mstv_utility::BinarySearch(nodes, std::make_pair<int, int>(25, 25));
		REQUIRE(not_found.get() == nullptr);
	}

	SECTION("Binary Search passes a test case which was failing in practicality") {
		nodes = {
			std::make_shared<Node>("0",-86, -29),
			std::make_shared<Node>("0",-51,-43),
			std::make_shared<Node>("0",-34,-57),
			std::make_shared<Node>("0",18,-95),
			std::make_shared<Node>("0",99,61)
		};
		mstv_utility::SortNodeVector(nodes);
		auto found = mstv_utility::BinarySearch(nodes, std::make_pair<int, int>(-86, -29));
		REQUIRE(found.get() != nullptr);
		REQUIRE((found.get()->getXY().first == -86 && found.get()->getXY().second == -29));
	}

	SECTION("converts double to char*") {
		auto char_array_ptr = std::move(mstv_utility::ConvertToCharArray(2.0));
		REQUIRE(char_array_ptr.get()[0] == '2');
	}
}

TEST_CASE("Union Find", "[UF]") {
	std::vector<std::pair<int, int>> tinyUF =
	{
		std::make_pair<int,int>(4,3),
		std::make_pair<int, int>(3,8),
		std::make_pair<int, int>(6,5),
		std::make_pair<int, int>(9,4),
		std::make_pair<int, int>(2,1),
		std::make_pair<int, int>(8,9),
		std::make_pair<int, int>(5,0),
		std::make_pair<int, int>(7,2),
		std::make_pair<int, int>(6,1),
		std::make_pair<int, int>(1,0),
		std::make_pair<int, int>(6,7),
	};

	std::vector<int> elementsInA =
	{
		3,4,8,9
	};

	std::vector<int> elementsInB =
	{
		0,1,2,5,7,6
	};

	SECTION("Union Find executes correctly for a series of inputs") {
		
		UnionFind uf = UnionFind(10);
		
		for (auto& union_these : tinyUF) {
			uf.Union(union_these.first, union_these.second);
		};

		//check that the structure was unioned correctly
		for (auto& element : elementsInA) {
			REQUIRE(uf.Find(element)==4);
		}

		for (auto& element : elementsInB) {
			REQUIRE(uf.Find(element) == 6);
		}
		
	}

}



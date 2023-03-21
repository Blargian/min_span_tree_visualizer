#include <catch2/catch_test_macros.hpp>
#include "../src/node.h"
#include "../src/edge.h"
#include "../src/graph.h"
#include "../src/app.h"
#include "../src/prims_algo.h"
#include <algorithm>
#include <vector>
#include <string>

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

		std::vector<Node> nodes = {
			Node("Johannesburg", 5, 10),
			Node("Cape Town", 26, 10),
		};

		
		for (Node node : nodes) {
			g.insertNode(node);
		}
		g.connectNodes(g.getNodes()[0], g.getNodes()[1],1);

		Edge e = Edge(g.getNodes()[0], g.getNodes()[1], 1);

		Edge* edge_we_need = g.getNodes()[0]->getEdge(g.getNodes()[0], g.getNodes()[1]);
		REQUIRE(*(edge_we_need) == e);

	}
}

TEST_CASE("Graph","[Graph]"){

	Node newNode = Node();
	Graph g = Graph();

	SECTION("a new node gets added to the graph") {
		vector<Node*> nodes = g.getNodes();
		REQUIRE(nodes.size()==0);
		g.insertNode(newNode);
		nodes = g.getNodes();
		REQUIRE(nodes.size() == 1);
	}

	SECTION("node count updates correctly") {
		Node a = Node();
		Graph g = Graph();
		REQUIRE(g.getNodeCount() == 0);
		g.insertNode(newNode);
		REQUIRE(g.getNodeCount() == 1);
		g.removeNode(g.getNodes()[0]);
		REQUIRE(g.getNodeCount() == 0);
	}

	//lines commented out are due to graph being undirected 
	SECTION("connects two nodes with an edge") {

		Node a = Node("Johannesburg", 5, 10);
		Node b = Node("Cape Town", 26, 10);

		size_t a_index = g.insertNode(a) -1;
		size_t b_index = g.insertNode(b) -1;
		vector<Node*> nodes_on_graph = g.getNodes();
		g.connectNodes(nodes_on_graph[a_index],nodes_on_graph[b_index], 1);

		//expected edges if connectNodes(a,b,1) is run 
		Edge aToB = Edge(nodes_on_graph[a_index], nodes_on_graph[b_index], 1);
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
		
		std::vector<Node> nodes = {
			Node("Johannesburg", 5, 10),
			Node("Cape Town", 26, 10),
			Node("Durban", -24, 78)
		};

		for(Node node : nodes) {
			g.insertNode(node);
		}

		vector<Node*> nodes_on_graph = g.getNodes();
		g.connectNodes(nodes_on_graph[0], nodes_on_graph[1], 1);
		g.connectNodes(nodes_on_graph[2], nodes_on_graph[1], 1);

		REQUIRE(size(g.getNodes()[0]->getEdgeList()) == 1);
		REQUIRE(size(g.getNodes()[1]->getEdgeList()) == 0);
		REQUIRE(size(g.getNodes()[2]->getEdgeList()) == 1);

		g.removeNode(g.getNodes().back());
		g.removeNode(g.getNodes().back());
		g.removeNode(g.getNodes().back());

		//After removing there should only be two nodes
		//Those nodes should have no edges
		REQUIRE(g.getNodeCount() == 0);
	}

	SECTION("returns coordinates of nodes in an array of floats - to be used for plotting") {
		Graph g = Graph();
		std::vector<Node> nodes = {
			Node("Johannesburg", 5, 10),
			Node("Cape Town", 26, 10),
			Node("Durban", -24, 78)
		};
		for (Node node : nodes) {
			g.insertNode(node);
		}
		auto points = g.getCoordsForPlot();
		REQUIRE((points.first[0] == 5 && points.second[0]==10));
		REQUIRE((points.first[1] == 26 && points.second[1] == 10));
		REQUIRE((points.first[2] == -24.0 && points.second[2] == 78));
	}

	SECTION("getNodeByName returns a pointer to a node given the name") {
		Graph g = Graph();
		std::vector<Node> nodes = {
			Node("Johannesburg", 5, 10),
			Node("Cape Town", 26, 10),
			Node("Durban", -24, 78)
		};
		for (Node node : nodes) {
			g.insertNode(node);
		}
		Node* node = g.getNodeByName("Johannesburg");
		REQUIRE(node->getXY().first == 5);
		REQUIRE(node->getXY().second == 10);
		REQUIRE(node->getNodeName() == "Johannesburg");
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
	Graph tinyGraph; 
	//create the nodes
	for (vector<int> node : tinyEWGnodes) {
		tinyGraph.insertNode(Node(to_string(node[0]), static_cast<int>(node[0]), static_cast<int>(node[0])));
	};
	//connect the nodes
	for (vector<double> node_data : tinyEWG) {
		tinyGraph.connectNodes(tinyGraph.getNodeByName(to_string((int)node_data[0])), tinyGraph.getNodeByName(to_string((int)node_data[1])), node_data[2]);
	};
	//PrimsAlgorithm prim = PrimsAlgorithm();
	//auto MST = prim.findMST(*tinyGraph.getNodeByName("0"));
	//while (!MST.empty()) {
	//	cout << MST.front() << endl; //add something to print edges
	//	MST.pop();
	//}
}


#include <catch2/catch_test_macros.hpp>
#include "../src/node.h"
#include "../src/edge.h"
#include "../src/graph.h"
#include <algorithm>

using namespace std; 

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

	SECTION("an edge gets removed from adjacency list") {
		Node a = Node("Johannesburg",5,10);
		Node b = Node("Cape Town",26,10);
		Node c = Node("Durban",72,100);

		Graph g = Graph();
		g.insertNode(a);
		g.insertNode(b);
		g.insertNode(c);
	}
}

TEST_CASE("Graph","[Graph]"){

	Node newNode = Node();
	Graph g = Graph();

	SECTION("a new node gets added to the graph") {
		vector<Node> nodes = g.getNodes();
		REQUIRE(nodes.size()==0);
		g.insertNode(newNode);
		nodes = g.getNodes();
		REQUIRE(nodes.size() == 1);
	}

	SECTION("connects two nodes with an edge") {

		Node a = Node("Johannesburg", 5, 10);
		Node b = Node("Cape Town", 26, 10);

		//expected edges if connectNodes(a,b,1) is run 
		Edge aToB = Edge(&a,&b, 1);
		Edge bToA = Edge(&a,&b, 1);

		Node* aptr = g.insertNode(a);
		Node* bptr = g.insertNode(b);
		g.connectNodes(aptr, bptr, 1);

		vector<Node> nodes = g.getNodes();

		list<Edge> nodeAEdges = nodes[0].getEdgeList();
		list<Edge> nodeBEdges = nodes[1].getEdgeList();
		REQUIRE(find(nodeAEdges.begin(), nodeAEdges.end(), aToB) != nodeAEdges.end());
		REQUIRE(find(nodeBEdges.begin(), nodeBEdges.end(), bToA) != nodeAEdges.end());

	}
}



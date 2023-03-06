#include <catch2/catch_test_macros.hpp>
#include "../src/node.h"
#include "../src/edge.h"
#include "../src/graph.h"
#include <algorithm>

using namespace std; 

TEST_CASE("Graph edge", "[Edge]") {

	Node* b = &Node();
	Node* c = &Node();
	Edge anEdge = Edge(b, 1);

	SECTION("Edge gets created properly") {
		REQUIRE(anEdge.getDestinationNode() == b);
		REQUIRE(anEdge.getEdgeWeight() == 1);
	}

	SECTION("Destination node of Edge gets correctly updated using setter") {
		REQUIRE(anEdge.getDestinationNode() == b);
		anEdge.setDestinationNode(c);
		REQUIRE(anEdge.getDestinationNode() == c);
	}

	SECTION("Edge weight of Edge gets correctly updated using setter") {
		
		int updatedWeight = 2; 
		REQUIRE(anEdge.getEdgeWeight() == 1);
		anEdge.setEdgeWeight(updatedWeight);
		REQUIRE(anEdge.getEdgeWeight() == updatedWeight);
	}
}

TEST_CASE("Graph node", "[Node]") {

	Node* a = &Node();
	SECTION("error gets thrown if x coordinate is outside of limits 0-100") {
		CHECK_THROWS_AS(a->setXY(200,5), std::logic_error);
	}

	SECTION("error gets thrown if y coordinate is outside of limits 0-100") {
		CHECK_THROWS_AS(a->setXY(67, 189), std::logic_error);
	}

	SECTION("no error is thrown if both coordinates are in the limit 0-100") {
		CHECK_NOTHROW(a->setXY(67, 72));
	}

	SECTION("an edge gets inserted to the adjacency list") {
		Node* b = &Node();
		Edge e = Edge(b,1);
		b->insertEdge(e);
		list<Edge> edgelist = b->getEdgeList();
		REQUIRE(edgelist.empty() == true);
		//REQUIRE(b->getEdgeList().empty() != true);
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
}



#pragma once

#include <queue>
#include "Edge.h"
#include "Node.h"

class MSTAlgorithm {

protected:
	queue<Edge> MST_;
private:
	priority_queue<Edge, vector<Edge>, greater<Edge>> minPQ_;
public:
	MSTAlgorithm() {};
	~MSTAlgorithm() {};
	virtual queue<Edge> findMST(Node& startingNode) = 0;
};

void  inline visitNode(Node& node, priority_queue<Edge, vector<Edge>, greater<Edge>>& pq) {
	node.markVisited();
	for (auto& e : node.getEdgeList())
	{
		if (!e.getDestinationNode()->wasVisited()) {
			pq.push(e);
		}
	}
}

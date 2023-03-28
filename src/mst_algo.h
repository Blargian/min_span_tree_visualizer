#pragma once

#include <queue>
#include "Edge.h"
#include "Node.h"
#include "snapshot.h"

class Snapshot;

class MSTAlgorithm {

protected:
	queue<Edge> MST_;
private:
	priority_queue<Edge, vector<Edge>, greater<Edge>> minPQ_;
	vector<Snapshot> solving_snapshots;
public:
	MSTAlgorithm() {};
	~MSTAlgorithm() {};
	virtual queue<Edge> findMST(Node& startingNode) = 0;
	void AddSnapshot(Snapshot s) {
		solving_snapshots.emplace_back(s);
	}
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

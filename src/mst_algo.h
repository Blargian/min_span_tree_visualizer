#pragma once

#include <queue>
#include "Edge.h"
#include "Node.h"
#include "snapshot.h"

class Snapshot;

class MSTAlgorithm {

protected:
	std::queue<Edge> MST_;
private:
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> minPQ_;
	std::vector<Snapshot> solving_snapshots;
public:
	MSTAlgorithm() {};
	~MSTAlgorithm() {};
	virtual std::queue<Edge> findMST(Node& startingNode) = 0;
	void AddSnapshot(Snapshot s) {
		solving_snapshots.emplace_back(s);
	};
	std::vector<Snapshot> Snapshots()
	{
		return solving_snapshots;
	};
};

void  inline visitNode(Node& node, std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>& pq) {
	node.markVisited();
	for (auto& e : node.getEdgeList())
	{
		if (!e.getDestinationNode()->wasVisited()) {
			pq.push(e);
		}
	}
}

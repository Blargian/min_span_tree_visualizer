#pragma once

#include <queue>
#include <algorithm>
#include <utility>
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
	std::queue<Edge> findMST(Node& startingNode);

	void AddSnapshot(Snapshot s) {
		solving_snapshots.emplace_back(s);
	};

	std::vector<Snapshot> getSnapshots()
	{
		return solving_snapshots;
	};

	void clearSnapshots() {
		solving_snapshots.clear();
	}

	void clearAll() {
		solving_snapshots.clear();

		//clear MST_ 
		std::queue<Edge> empty_MST;
		std::swap(MST_, empty_MST);
	}

	int getSnapshotLength() {
		return solving_snapshots.size();
	}
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

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
	std::vector<Snapshot> solving_snapshots;
private:
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> minPQ_;
	int iterationCount_ = 0;
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

	virtual void clearAll() = 0;

	int getSnapshotLength() {
		return solving_snapshots.size();
	}

	void increaseIteration() { iterationCount_++; };
	void resetIterationCount() { iterationCount_ = 0; };
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

#pragma once 
#include "edge.h"
#include <vector>
#include <queue>

class Snapshot {
public:
	Snapshot();
	~Snapshot();
	std::queue<Edge> getMST();
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> getPQ();
	Edge getEdgeLeastWeight();
	void AddMST(std::queue<Edge> mst);
	void AddPQ(std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq);
	void SetEdgeLeastWeight(Edge e);

private:
	std::queue<Edge> MST_;
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq_;
	Edge least_weight_ = Edge();
};
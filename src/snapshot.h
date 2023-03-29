#pragma once 
#include "edge.h"
#include <vector>
#include <queue>

class Snapshot {
public:
	Snapshot();
	~Snapshot();
	queue<Edge> MST();
	priority_queue<Edge, vector<Edge>, greater<Edge>> PQ();
	Edge EdgeLeastWeight();
	void AddMST(queue<Edge> mst);
	void AddPQ(priority_queue<Edge, vector<Edge>, greater<Edge>> pq);
	void SetEdgeLeastWeight(Edge e);

private:
	queue<Edge> MST_;
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq_;
	Edge least_weight_ = Edge();
};
#include "snapshot.h"
#include "edge.h"
#include <vector>
#include <queue>

using namespace std; 

Snapshot::Snapshot(){

};

Snapshot::~Snapshot() {

};

queue<Edge> Snapshot::MST() {
	return MST_;
}

priority_queue<Edge, vector<Edge>, greater<Edge>> Snapshot::PQ() {
	return pq_;
}

Edge Snapshot::EdgeLeastWeight() {
	return least_weight_;
}

void Snapshot::AddMST(queue<Edge> e) {
	MST_ = e;
}

void Snapshot::AddPQ(priority_queue<Edge, vector<Edge>, greater<Edge>> pq) {
	pq_ = pq;
}

void Snapshot::SetEdgeLeastWeight(Edge e) {
	least_weight_ = e;
}
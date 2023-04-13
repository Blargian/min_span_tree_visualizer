#include "snapshot.h"
#include <vector>
#include <queue>

using namespace std; 

Snapshot::Snapshot(){
};

Snapshot::Snapshot(std::queue<Edge> MST) {
	MST_ = MST; 
}

Snapshot::~Snapshot() {

};

queue<Edge> Snapshot::getMST() {
	return MST_;
}

priority_queue<Edge, vector<Edge>, greater<Edge>> Snapshot::getPQ() {
	return pq_;
}

Edge Snapshot::getEdgeLeastWeight() {
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
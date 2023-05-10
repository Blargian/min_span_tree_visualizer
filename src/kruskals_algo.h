#include "mst_algo.h"
#include <queue>

class KruskalsAlgorithm : public MSTAlgorithm {
private:
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> minPQ_;
	int iterationCount_ = 0;
public:
	KruskalsAlgorithm();
	~KruskalsAlgorithm();
	std::queue<Edge> findMST(Node& startingNode) override;
};
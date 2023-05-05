#pragma once 
#include "node.h"
#include <vector>

class Node;

using SharedNodePtr = std::shared_ptr<class Node>;

namespace mstv_utility {

	SharedNodePtr BinarySearch(std::vector<SharedNodePtr>& node_list_sorted, std::pair<int, int> coord);
	void SortNodeVector(std::vector<SharedNodePtr>& node_list_unsorted);
}
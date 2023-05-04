#include "utility_mstv.h"
#include <algorithm>

namespace mstv_utility {
	SharedNodePtr BinarySearch(std::vector<SharedNodePtr>& sorted_node_vector, std::pair<int, int> coord) {

		auto left = sorted_node_vector.begin();
		auto right = sorted_node_vector.end() - 1;

		while (left <= right) {
			std::vector<SharedNodePtr>::iterator middle = sorted_node_vector.begin() + (int)((std::distance(sorted_node_vector.begin(),left) + (std::distance(sorted_node_vector.begin(),right))) / 2);

			auto vector_coord = middle->get()->getXY();
			if (vector_coord.first == coord.first) 
			{
				//this only works if array is also sorted by y after x
				if (vector_coord.second == coord.second) 
				{
					return *middle;
				}
				else if (vector_coord.second < coord.second) 
				{
					left = middle + 1;
				}	
				else {
					right = middle - 1;
				}	
			}
			else if (vector_coord.first < coord.first) 
			{
				left = middle + 1;
			}
			else 
			{
				right = middle - 1;
			}
				
		}

		return nullptr;
	}

	void SortNodeVector(std::vector<SharedNodePtr>& node_list_unsorted) {
		std::sort(node_list_unsorted.begin(), node_list_unsorted.end(), [](auto a, auto b) {
			if (a->getXY().first != b->getXY().first) 
			{
				return a->getXY().first < b->getXY().first;
			}
			else {
				return a->getXY().second < b->getXY().second;
			}
			}
		);
	}
}
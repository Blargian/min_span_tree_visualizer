#pragma once 
#include "node.h"
#include <vector>
#include <memory>
#include <cassert>
#include <string>
#include <sstream>
#include <iomanip>

class Node;

using SharedNodePtr = std::shared_ptr<class Node>;

namespace mstv_utility {

	SharedNodePtr BinarySearch(std::vector<SharedNodePtr>& node_list_sorted, std::pair<int, int> coord);
	void SortNodeVector(std::vector<SharedNodePtr>& node_list_unsorted);
	void PrintPoints(std::vector<std::pair<int, int>>& points);
	
	template <typename T>
	std::unique_ptr<char []> ConvertToCharArray(T value) {

		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << value;

		std::string s = stream.str();

		const int length = s.length();

		auto char_array_ptr = std::make_unique<char[]>(length+1);

		strcpy(char_array_ptr.get(), s.c_str());

		return char_array_ptr;

	}

}
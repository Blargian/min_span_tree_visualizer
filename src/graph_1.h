#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <boost/config.hpp>
#include <vector>

struct VertexProperties {
  std::pair<int, int> coordinate; 
};

struct EdgeProperties {
  boost::edge_weight_t edge_weight;
};

typedef boost::adjacency_list
<
    boost::vecS,
    boost::vecS, 
    boost::undirectedS,
    VertexProperties, 
    EdgeProperties
>
BoostGraph;

namespace GraphHandler {
void createNodes(BoostGraph& g, const std::vector<std::pair<int,int>> points);
void clearNodes(BoostGraph& g);
}



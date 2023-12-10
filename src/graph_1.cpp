#include "graph_1.h"
#include <exception>

// given a vector of N integer coordinates, makes N vertices on the given graph
void GraphHandler::createNodes(BoostGraph& g,const std::vector<std::pair<int, int>> coords) {

  const int num_vertices_pre = boost::num_vertices(g); 
  typedef boost::graph_traits<BoostGraph>::vertex_descriptor VertexDescriptor;
  for (auto it = coords.begin(); it != coords.end(); ++it) {
    VertexDescriptor v;
    v = boost::add_vertex(g);
    g[v].coordinate = *it;  
  }
  const int num_vertices_post = boost::num_vertices(g); 
  if (num_vertices_post != num_vertices_pre + coords.size()) {
    throw std::logic_error("not all vertices were added to the graph");
  }
}

void GraphHandler::clearNodes(BoostGraph& g) {
  g.clear();
}
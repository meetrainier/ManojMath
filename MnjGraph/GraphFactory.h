#pragma once
#include "all_std.h" 
#include "GenericGraphHeader.h"

namespace GraphFactory
{

  void one_vertex_zero_edge_graph(int& V, int& E, vecVecI &adj);
  void one_vertex_self_edge_cyclic_graph(int& V, int& E, vecVecI &adj);
  void two_vertices_1_edge_dir_graph(int& V, int& E, vecVecI &adj);
  void two_vertices_2_edges_mutual_cycle_dir_graph(int& V, int& E, vecVecI &adj);
}
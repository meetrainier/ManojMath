#pragma once
#include "all_std.h" 
#include "GenericGraphHeader.h"

namespace GraphFactory
{

  void one_vertex_zero_edge_graph(int& V, int& E, vecVecI &adj);
  void one_vertex_self_edge_cyclic_graph(int& V, int& E, vecVecI &adj);
  
  void two_vertices_1_edge_dir_graph(int& V, int& E, vecVecI &adj);
  void two_vertices_2_edges_mutual_cycle_dir_graph(int& V, int& E, vecVecI &adj);

  void triangle_dir_graph(int& V, int &E, vecVecI& adj);

  //undirected 
  void triangle_undir_graph(int& V, vecVecI& adj);
  void v_shaped_undir_graph(int& V, vecVecI& adj);
}
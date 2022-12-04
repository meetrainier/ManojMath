//#pragma once
////Below is the syntax highlighted version of KruskalMST.java from §4.3 Minimum Spanning Trees.
///******************************************************************************
// */
// tbd: convert to C++
// /* Compilation:  javac KruskalMST.java
//  *  Execution:    java  KruskalMST filename.txt
//  *  Dependencies: EdgeWeightedGraph.java Edge.java Queue.java MinPQ.java
//  *                UF.java In.java StdOut.java
//  *  Data files:   https://algs4.cs.princeton.edu/43mst/tinyEWG.txt
//  *                https://algs4.cs.princeton.edu/43mst/mediumEWG.txt
//  *                https://algs4.cs.princeton.edu/43mst/largeEWG.txt
//  *
//  *  Compute a minimum spanning forest using Kruskal's algorithm.
//  *
//  *  %  KruskalMST tinyEWG.txt
//  *  0-7 0.16000
//  *  2-3 0.17000
//  *  1-7 0.19000
//  *  0-2 0.26000
//  *  5-7 0.28000
//  *  4-5 0.35000
//  *  6-2 0.40000
//  *  1.81000
//  */
//  //  KruskalMST mediumEWG.txt
//  //  168-231 0.00268
//  //  151-208 0.00391
//  //  7-157   0.00516
//  //  122-205 0.00647
//  //  8-152   0.00702
//  //  156-219 0.00745
//  //  28-198  0.00775
//  //  38-126  0.00845
//  //  10-123  0.00886
//  //  ...
//  //  10.46351
//  //
//
//
//
//#include "GenericGraphHeader.h"
//extern class Edge;
////extern class IllegalArgumentException;
////#include <queue> 
////Note: When converting to C++ , the following coventions are used. 
//class EdgeWeightedGraph {
//  //tbd 
//  //static const std::string NEWLINE = System.getProperty("line.separator");
//
//  int V;
//  int E;
//  std::vector<std::multiset<Edge>> adj;
//
//  /**
//   * Initializes an empty edge-weighted graph with {@code V} vertices and 0 edges.
//   *
//   * @param  V the number of vertices
//   * @throws IllegalArgumentException if {@code V < 0}
//   */
//public:
//  EdgeWeightedGraph(int V);
//
///**
// * Initializes a random edge-weighted graph with {@code V} vertices and <em>E</em> edges.
// *
// * @param  V the number of vertices
// * @param  E the number of edges
// * @throws IllegalArgumentException if {@code V < 0}
// * @throws IllegalArgumentException if {@code E < 0}
// */
//  EdgeWeightedGraph(int V, int E);
//
///**
// * Initializes an edge-weighted graph from an input stream.
// * The format is the number of vertices <em>V</em>,
// * followed by the number of edges <em>E</em>,
// * followed by <em>E</em> pairs of vertices and edge weights,
// * with each entry separated by whitespace.
// *
// * @param  in the input stream
// * @throws IllegalArgumentException if {@code in} is {@code null}
// * @throws IllegalArgumentException if the endpoints of any edge are not in prescribed range
// * @throws IllegalArgumentException if the number of vertices or edges is negative
// */
//  EdgeWeightedGraph(std::istream in);
//
//
///**
// * Initializes a new edge-weighted graph that is a deep copy of {@code G}.
// *
// * @param  G the edge-weighted graph to copy
// */
// EdgeWeightedGraph(EdgeWeightedGraph G);
//
//
///**
// * Returns the number of vertices in this edge-weighted graph.
// *
// * @return the number of vertices in this edge-weighted graph
// */
//int V() {
//  return V;
//}
//
///**
// * Returns the number of edges in this edge-weighted graph.
// *
// * @return the number of edges in this edge-weighted graph
// */
//int E() {
//  return E;
//}
//
//// throw an IllegalArgumentException unless {@code 0 <= v < V}
//  private:
//    void validateVertex(int v) {
//      if (v < 0 || v >= V)
//      {
//        std::string msg("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(V - 1));
//        //throw new IllegalArgumentException("vertex " + v + " is not between 0 and " + (V - 1));
//        throw new IllegalArgumentException(msg);
//      }
//    }
//
//    /**
//     * Adds the undirected edge {@code e} to this edge-weighted graph.
//     *
//     * @param  e the edge
//     * @throws IllegalArgumentException unless both endpoints are between {@code 0} and {@code V-1}
//     */
//  public:
//    void addEdge(Edge e); 
//
//    /**
//     * Returns the edges incident on vertex {@code v}.
//     *
//     * @param  v the vertex
//     * @return the edges incident on vertex {@code v} as an Iterable
//     * @throws IllegalArgumentException unless {@code 0 <= v < V}
//     */
//  
//    std::multiset<Edge> adj(int v) {
//      validateVertex(v);
//      return adj[v];
//    }
//
//    /**
//     * Returns the degree of vertex {@code v}.
//     *
//     * @param  v the vertex
//     * @return the degree of vertex {@code v}
//     * @throws IllegalArgumentException unless {@code 0 <= v < V}
//     */
//    int degree(int v) {
//      validateVertex(v);
//      return adj[v].size();
//    }
//
//    /**
//     * Returns all edges in this edge-weighted graph.
//     * To iterate over the edges in this edge-weighted graph, use foreach notation:
//     * {@code for (Edge e : G.edges())}.
//     *
//     * @return all edges in this edge-weighted graph, as an iterable
//     */
//  public:
//    Iterable<Edge> edges() {
//      //Bag<Edge> list = new Bag<Edge>();
//      std::multiset<Edge> list;;
//      for (int v = 0; v < V; v++) {
//        int selfLoops = 0;
//        for (Edge e : adj(v)) {
//          if (e.other(v) > v) {
//            list.add(e);
//          }
//          // add only one copy of each self loop (self loops will be consecutive)
//          else if (e.other(v) == v) {
//            if (selfLoops % 2 == 0) list.add(e);
//            selfLoops++;
//          }
//        }
//      }
//      return list;
//    }
//
//    /**
//     * Returns a string representation of the edge-weighted graph.
//     * This method takes time proportional to <em>E</em> + <em>V</em>.
//     *
//     * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,
//     *         followed by the <em>V</em> adjacency lists of edges
//     */
//  public:
//    std::string toString() {
//      //StringBuilder s = new StringBuilder();
//      //s.append(V + " " + E + NEWLINE);
//      //for (int v = 0; v < V; v++) {
//      //  s.append(v + ": ");
//      //  for (Edge e : adj[v]) {
//      //    s.append(e + "  ");
//      //  }
//      //  s.append(NEWLINE);
//      //}
//      //return s.toString();
//
//      std::string s ;
//      s.append(std::to_string(V) + " " + std::to_string(E) + std::string(NEWLINE));
//      for (int v = 0; v < V; v++) {
//        s.append(v + ": ");
//        for (Edge e : adj[v]) {
//          s.append(e + std::string("  "));
//        }
//        s.append(std::string(NEWLINE));
//      }
//      return s;
//
//    }
//
//
//};
//

//#pragma once
///******************************************************************************
//Tbd: this is an attempt to convert the Edge java code from Sedgewick's book to C++ code.  
// *  Compilation:  javac Edge.java
// *  Execution:    java Edge
// *  Dependencies: StdOut.java
// *
// *  Immutable weighted edge.
// *
// ******************************************************************************/
//
//
// /**
//  *  The {@code Edge} class represents a weighted edge in an
//  *  {@link EdgeWeightedGraph}. Each edge consists of two integers
//  *  (naming the two vertices) and a real-value weight. The data type
//  *  provides methods for accessing the two endpoints of the edge and
//  *  the weight. The natural order for this data type is by
//  *  ascending order of weight.
//  *  <p>
//  *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/43mst">Section 4.3</a> of
//  *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
//  *
//  *  @author Robert Sedgewick
//  *  @author Kevin Wayne
//  */
//#include "GenericGraphHeader.h"
//
////class IllegalArgumentException : public std::exception
////{
////  std::string str;
////public:
////  IllegalArgumentException(const std::string is)
////  {
////    str = is;
////  }
////
////  virtual const char* what() const throw()
////  {
////    return str.c_str();
////  }
////};
//
//
//class Edge //tbd: implements Comparable<Edge> 
//{
//
//  int v;
//  int w;
//  double weight;
//
//  /**
//   * Initializes an edge between vertices {@code v} and {@code w} of
//   * the given {@code weight}.
//   *
//   * @param  v one vertex
//   * @param  w the other vertex
//   * @param  weight the weight of this edge
//   * @throws IllegalArgumentException if either {@code v} or {@code w}
//   *         is a negative integer
//   * @throws IllegalArgumentException if {@code weight} is {@code NaN}
//   */
//public:
//  Edge(int v, int w, double weight);
//  /**
//   * Returns the weight of this edge.
//   *
//   * @return the weight of this edge
//   */
//  double Weight();
//
//  /**
//   * Returns either endpoint of this edge.
//   *
//   * @return either endpoint of this edge
//   */
//  int either();
//
//  /**
//   * Returns the endpoint of this edge that is different from the given vertex.
//   *
//   * @param  vertex one endpoint of this edge
//   * @return the other endpoint of this edge
//   * @throws IllegalArgumentException if the vertex is not one of the
//   *         endpoints of this edge
//   */
//  int other(int vertex);
//
//  /**
//   * Compares two edges by weight.
//   * Note that {@code compareTo()} is not consistent with {@code equals()},
//   * which uses the reference equality implementation inherited from {@code Object}.
//   *
//   * @param  that the other edge
//   * @return a negative integer, zero, or positive integer depending on whether
//   *         the weight of this is less than, equal to, or greater than the
//   *         argument edge
//   */
//   //@Override
//  int compareTo(Edge that);
//
//  /**
//   * Returns a string representation of this edge.
//   *
//   * @return a string representation of this edge
//   */
//  std::string toString(); 
//
//  /**
//   * Unit tests the {@code Edge} data type.
//   *
//   * @param args the command-line arguments
//   */
//   //void main(string[] args) {
//   //Edge e = new Edge(12, 34, 5.67);
//   //StdOut.println(e);
// //}
//};

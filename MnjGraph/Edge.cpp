///******************************************************************************
// *  Compilation:  javac Edge.java
// *  Tbd: this is an attempt to convert the Edge java code from Sedgewick's book to C++ code.  
// 
// *
// *  
// *
// ******************************************************************************/
//
//
///**
// *  The {@code Edge} class represents a weighted edge in an
// *  {@link EdgeWeightedGraph}. Each edge consists of two integers
// *  (naming the two vertices) and a real-value weight. The data type
// *  provides methods for accessing the two endpoints of the edge and
// *  the weight. The natural order for this data type is by
// *  ascending order of weight.
// *  <p>
// *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/43mst">Section 4.3</a> of
// *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
// *
// *  @author Robert Sedgewick
// *  @author Kevin Wayne
// */
//#include "GenericGraphHeader.h"
//#include "Edge.h"
//
//
//
//Edge::Edge(int v, int w, double weight) {
//    if (v < 0) throw new IllegalArgumentException(std::string("vertex index must be a non-negative integer"));
//    if (w < 0) throw new IllegalArgumentException(std::string( "vertex index must be a non-negative integer"));
//    //tbd if (Double.isNaN(weight)) throw new IllegalArgumentException("Weight is NaN");
//    this->v = v;
//    this->w = w;
//    this->weight = weight;
//  }
//
//  double Edge::Weight() {
//    return weight;
//  }
//
//  /**
//   * Returns either endpoint of this edge.
//   *
//   * @return either endpoint of this edge
//   */
//  int Edge::either() {
//    return v;
//  }
//
//  /**
//   * Returns the endpoint of this edge that is different from the given vertex.
//   *
//   * @param  vertex one endpoint of this edge
//   * @return the other endpoint of this edge
//   * @throws IllegalArgumentException if the vertex is not one of the
//   *         endpoints of this edge
//   */
//  int Edge::other(int vertex) {
//    if (vertex == v) return w;
//    else if (vertex == w) return v;
//    else throw new IllegalArgumentException("Illegal endpoint");
//  }
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
//  int Edge::compareTo(Edge that) {
//    //return Double.compare(this.weight, that.weight);
//    //return compare(this->weight, that.weight);
//    return int(that.weight - this->weight);
//  }
//
//  /**
//   * Returns a string representation of this edge.
//   *
//   * @return a string representation of this edge
//   */
//    std::string Edge::toString() {
//    // std::string.format("%d-%d %.5f", v, w, weight);
//    return std::to_string(v)+std::string("-")+std::to_string(w)+std::to_string(weight);//tbd: weight only upto 5 digits
//  }
//
//  /**
//   * Unit tests the {@code Edge} data type.
//   *
//   * @param args the command-line arguments
//   */
//    //void main(string[] args) {
//    //Edge e = new Edge(12, 34, 5.67);
//    //StdOut.println(e);
//  //}
//

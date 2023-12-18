// graph.h
// Name: Anupam Sai Sistla
// UIN: 659340448
// NetID: Asistl2

// Project 5: Open Street Maps
// The purpose of this project is to implement a GPS like algorithm that determines the best/nearest meeting point building between two people at two buildings,
// while outputing the path from each building to the meeting point. Each building is stored as a Vertex in the graph, and each Pathway is stored as a vector of Nodes
//

// Graph class for adjacency list implementation. The adjacency list has been implemented in the form of a map of a map. 
// graph.h has been implemented with the help of object oriented programming, maps, sets, vectors, pass-by-reference variables and templated variables
// This implementation allows for a stack alloc and stack free, without the need to worry about dynamic memory allocation.
// If dynamic memory allocation were used, a hash table can be a good alternative
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {
 private:

 map<VertexT, map<VertexT, WeightT>> myGraph; //adjacency list is implemeted in the from of a map of a map
  
 public:
 
  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const {
    int count = 0;
    for(auto temp : myGraph){
        count ++;
    }
    return count;
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    int count = 0;
    
    for(auto temp : myGraph){ //loop through the entire graph
      count = count + temp.second.size(); //count the number of edges
    }

    return count;
  }

  //
  // addVertex
  //
  // Add vertex V to a graph. Since this is an adjacency list implementation, we do not
  // need to worry about not having space
  //
  bool addVertex(VertexT v){ 
      if(myGraph.find(v) == myGraph.end()){ //check if the vertex already exists in the graph, if yes, return false, else return true
          map<VertexT, WeightT> myGraphAdj;
          myGraph[v] = myGraphAdj; //vertex added to the map
          return true; 
      }
      else{ //vertex already in the map 
        return false;
      }

    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist false is returned.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight) { 
    if(myGraph.find(from) == myGraph.end()){ //if vertex does not exist, return false
      return false;
    }
    else if(myGraph.find(to) == myGraph.end()){ //if vertex does not exist, return false
      return false;
    }

    else{
      if(myGraph[from].find(to) == myGraph[from].end()){ //edge does not exist
        myGraph[from][to] = weight; //add the weight for the new edge and return true
        return true;
      }
      else{
        myGraph[from][to] = weight; //edge already exists, overwrite existing weight
        return true;
      }
    }

    return true; //just for compilation
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
    if(myGraph.find(from) == myGraph.end()){ //vertex does not exist
      return false;
    }

    if((myGraph.at(from)).find(to) == myGraph.at(from).end()){ //edge does not exist
      return false;
    }

    weight = myGraph.at(from).at(to); //get the edge weight between two vertices
    return true;
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    set<VertexT>  S;

    if(myGraph.find(v) == myGraph.end()){ //vertex does not exist, return empty set
      return S;
    }

    for(auto temp : myGraph.at(v)){ //insert all neighbours of Vertex V into the set
      S.insert(temp.first);
    }

    return S; //return the set
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const {
    vector<VertexT> allVertices;
    
    for(auto & v : myGraph){ //loop through the graph
      allVertices.push_back(v.first); //push_back each vertex from the graph into the vector
    }

    return allVertices; //return the vector of all vertices
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //

  void dump(ostream& output) const {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
    int i =0;
    for(auto temp : myGraph){
      cout << i  << " : " << temp.first << endl;
      i++;
    }

    output << endl;
    output << "**Edges:" << endl;
    int count =0;
    for(auto temp1 : myGraph){
      output << " row " << count << ": ";
      for(auto temp2: temp1.second){
        output << "(T," << temp2.second <<  ") ";
      }
      output << endl;
      count ++;
    }
    output << "**************************************************" << endl;
  }
};

// application.cpp 

// Name: Anupam Sai Sistla
// UIN: 659340448
// NetID: Asistl2
//
// Project 5: Open Street Maps
// The purpose of this project is to implement a GPS like algorithm for UIC that determines the best/nearest meeting point building between two people at two buildings,
// while outputing the path from each building to the meeting point. Each building is stored as a Vertex in the graph, and each Pathway is stored as a vector of Nodes.
// The underlying implementation for the graph is an adjacency list enabled by a map of a map where the first map contains all vertices in the graph and the second map contains
// the neighbours for each vertex.
//
// application.cpp was implemented with the help of object oriented programming, Djikstra's Algorithm, custom priority queue, stack, map, vectors, pass-by-reference variables, 
// assertions, INF,  XML, templated variables and strings 

// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <iomanip>  /*setprecision*/
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <queue>
#include <stack>
#include <set>


#include "tinyxml2.h"
#include "dist.h"
#include "graph.h"
#include "osm.h"


using namespace std;
using namespace tinyxml2;

const double INF = numeric_limits<double>::max(); //global variable for infinity

class prioritize{ //custom class for priority queue that enables comparison of two pairs
  public:
    bool operator()(const pair<long long,double>& p1, const pair<long long, double>& p2) const{ //operator overloader for (), return true if weight of p1 > weight of p2
      return p1.second > p2.second;
    }
};

vector<long long> getPath(map<long long, long long>& predecessors, long long endVertex){ //This function returns a path from start vertex to the end vertex
  stack<long long> nodes; //stack to store all nodes
  vector<long long> path; //path tor return

  long long currV = endVertex; 
  while(predecessors.find(currV) != predecessors.end()){ 
    nodes.push(currV); //add each predecessor of currV into the stack
    currV = predecessors[currV]; //set currV to the next vertex and loop through its predecessors
  }

  while(!nodes.empty()){ //put each element of the stack into the vector. In the first iteration the top of the stack would be the start vertex
    currV = nodes.top(); 
    nodes.pop();
    path.push_back(currV);
  }

  return path; //return the path that is obtained
}

void DijkstraShortestPath(long long startV, graph<long long, double>& G, map<long long, double>& distances, map<long long, long long>& predecessors){ //Implement Dijkstra's algorithm to find the shortest path b/w two nodes in a graph
  priority_queue<pair<long long, double>, vector<pair<long long, double>>, prioritize> unvisitedQueue; //priority queue for each unvisited element of the graph
  long long currV;

  vector<long long> visited; //vector for visited vertices
  for(auto tempV: G.getVertices()){ //loop through all vertices in the graph
    distances[tempV] = INF; //set all distances to INF
    predecessors[tempV] = 0; //no predecessors for each vertex
    unvisitedQueue.push(make_pair(tempV, INF)); //push each element into the priority queue
  }

  distances[startV] = 0; //set initial distance for starting vertex to 0 and push into the priority queue
  unvisitedQueue.push(make_pair(startV, 0)); 

  while(!unvisitedQueue.empty()){ //visit each unvisited element
    currV = unvisitedQueue.top().first; //get current vertex 
    unvisitedQueue.pop();

    if(distances[currV] == INF){ //if distance is infinity - no path - break
      break;
    }
    else if(find(visited.begin(), visited.end(), currV) != visited.end()){ //continue if the vertex has already been visited
      continue;
    }
    else{ //vertex has been visited push_back into vector
      visited.push_back(currV);
    }
    
    for(auto adjV: G.neighbors(currV)){ //loop through all adjacent vertices
        double edgeWeight =0;
        G.getWeight(currV, adjV, edgeWeight); //get the edge weight b/w currV and adjV. Store in edgeWeight
        double alternativePathDistance = distances[currV] + edgeWeight; 

        if(alternativePathDistance < distances[adjV]){ //check if new path is shorter than old path
          distances[adjV] = alternativePathDistance; //if yes, update new distance for adjV
          predecessors[adjV] = currV; //Predecessor of adjV is currV
          unvisitedQueue.push(make_pair(adjV, alternativePathDistance)); //now continue iteration as adjV has not been visited
      }
    }
  }
}

BuildingInfo searchBuildings(string query, vector<BuildingInfo>& Buildings){ //Function that returns a BuildingInfo object whose "fullname" or "abbrev" is the same as query
  BuildingInfo search;
  for(auto temp : Buildings){ //First search all abbreviations
    string abvName = temp.Abbrev;
    if(abvName == query){ //if BuildingInfo object is found return the temp object
      return temp;
    }
  }

  for(auto temp : Buildings){ //Otherwise, search all Fullnames for each BuildingInfo object in the vector
    string FullName = temp.Fullname; 
    if(FullName.find(query) != string::npos){ //if BuildingInfo object with "Fullname" matching query is found, return that BuildingInfo Object. string::npos supports if similar names to the "Fullname" are entered
      return temp;
    }
  }

  return search; //return empty BuildingInfo object if Builing is not found
}

BuildingInfo nearestBuilding(BuildingInfo& BuildingInfo1, BuildingInfo& BuildingInfo2, vector<BuildingInfo>& Buildings){ //Function to find the nearest building between 2 buildings
  Coordinates midPoint = centerBetween2Points(BuildingInfo1.Coords.Lat, BuildingInfo1.Coords.Lon, BuildingInfo2.Coords.Lat, BuildingInfo2.Coords.Lon); //find the coordinates of the center b/w the two buildings

  double min = INF;
  BuildingInfo meetingPoint;
  for(auto temp : Buildings){ //loop through all buildings to find the building with the shortest distance to midPoint
    double tempDistance = distBetween2Points(midPoint.Lat, midPoint.Lon, temp.Coords.Lat, temp.Coords.Lon); //obtain the distance between each building and midPoint
    if(tempDistance < min){ //find the building with the minimum distance
      min = tempDistance; //set new min
      meetingPoint = temp; //set meetingPoint
    }
  }
  return meetingPoint; //return the meetingPoint
}

//Similar to the above functions, supports finding nearest meeting point multiple times if there is no valid path between either P1 and P2 to meeting point
BuildingInfo nearestBuildingAgain(BuildingInfo& BuildingInfo1, BuildingInfo& BuildingInfo2, vector<BuildingInfo>& Buildings, stack<BuildingInfo>& visited){
  Coordinates midPoint = centerBetween2Points(BuildingInfo1.Coords.Lat, BuildingInfo1.Coords.Lon, BuildingInfo2.Coords.Lat, BuildingInfo2.Coords.Lon);

  double min = INF;
  BuildingInfo meetingPoint;
  for(auto temp : Buildings){
    double tempDistance = distBetween2Points(midPoint.Lat, midPoint.Lon, temp.Coords.Lat, temp.Coords.Lon);
    if(tempDistance < min){
      min = tempDistance;
      meetingPoint = temp;
      visited.push(meetingPoint); //stack to store all nearest meeting points
    }
  }
  return meetingPoint; //return original meeting point
}

Coordinates nearestNodetoBuilding(vector<FootwayInfo>& Footways, BuildingInfo Building, map<long long, Coordinates>& Nodes, long long& nearestNode){ //function to find the nearest node to a building
  double min = INF;
  Coordinates nearestCord;
  
  for(auto temp : Footways){ //loop through all FootwayInfo objects
    for(int i =0 ; i<temp.Nodes.size(); i++){ //loop through vector of nodes along a footway 
      double tempDistance = distBetween2Points(Building.Coords.Lat, Building.Coords.Lon, Nodes[temp.Nodes[i]].Lat, Nodes[temp.Nodes[i]].Lon); //get distance between a node on the footway and the Building
      if(tempDistance < min){ //find min distance
        min = tempDistance; //set new min
        nearestCord = Nodes[temp.Nodes[i]]; //get the new nearestCord
        nearestNode = temp.Nodes[i]; //get the new nearestNode
      }
    }
  }
  return nearestCord; //return coordinates of the nearest node
}

//The purpose of this function is to implement the interative interface, prompts the user to input two buildings and finds the nearest meeting point for both buildings. 
//It also returns the path for each building to the meeting point (Building)
void application(map<long long, Coordinates>& Nodes, vector<FootwayInfo>& Footways, vector<BuildingInfo>& Buildings, graph<long long, double>& G) {  
  string person1Building, person2Building;

  cout << endl;
  cout << "Enter person 1's building (partial name or abbreviation), or #> ";
  getline(cin, person1Building);

  while (person1Building != "#") { //while user doesn't exit the application
    bool invalidP1 = false;
    bool invalidP2 = false;
    BuildingInfo BuildingInfo1 = searchBuildings(person1Building, Buildings); //search all Buildings for person1building

    if(BuildingInfo1.Coords.ID == 0){ //this means that the building does not exist
      invalidP1 = true;
    }

    cout << "Enter person 2's building (partial name or abbreviation)> ";
    getline(cin, person2Building);
    
    if(invalidP1){ //Person 1's building does not exist
      cout << "Person 1's building not found" << endl;
    }

    if(person2Building == "#"){ //check if user wants to exit the application
      return;
    }

    BuildingInfo BuildingInfo2 = searchBuildings(person2Building, Buildings); //search all Buildings for Person 2's building
    if(BuildingInfo2.Coords.ID == 0){ //this means that Person 2's building does not exist
      invalidP2 = true;
      cout << "Person 2's building not found" << endl;
    }

    while(invalidP1 || invalidP2){ //loop till while user inputs valid Person 1 building and Person 2 building
        cout << "Enter person 1's building (partial name or abbreviation), or #> ";
        getline(cin, person1Building);
        if(person1Building == "#"){
          return;
        }

        BuildingInfo1 = searchBuildings(person1Building, Buildings);
        if(BuildingInfo1.Coords.ID != 0){ //valid Person 1 building has been found 
          invalidP1 = false;
        }

        cout << "Enter person 2's building (partial name or abbreviation)> ";
        getline(cin, person2Building);
        if(person2Building == "#"){
          return;
        }

        BuildingInfo2 = searchBuildings(person2Building, Buildings);
        if(BuildingInfo2.Coords.ID != 0){ //valid Person 2 building has been found
          invalidP2 = false;
        }
    }

    cout << endl;
    cout << "Person 1's point:" << endl;
    cout << " " << BuildingInfo1.Fullname << endl; //Output Person 1's building with exact coordinates
    cout << " (" << BuildingInfo1.Coords.Lat << ", " << BuildingInfo1.Coords.Lon  << ")" << endl;

    cout << "Person 2's point:" << endl;
    cout << " " << BuildingInfo2.Fullname << endl; //Output Person 2's building with exact coordinates
    cout << " (" << BuildingInfo2.Coords.Lat << ", " << BuildingInfo2.Coords.Lon  << ")" << endl;

    BuildingInfo meetingPoint = nearestBuilding(BuildingInfo1, BuildingInfo2, Buildings); //Find nearest building between Person 1's building and Person 2's building

    cout << "Destination Building:" << endl;
    cout << " " << meetingPoint.Fullname << endl; //Output nearest meeting point (Building) with exact coordinates
    cout <<  " (" << meetingPoint.Coords.Lat << ", " << meetingPoint.Coords.Lon  << ")" << endl;

    long long p1NearestNode;
    long long p2NearestNode;
    long long desNearestNode;

    Coordinates p1NearestCord = nearestNodetoBuilding(Footways, BuildingInfo1, Nodes, p1NearestNode); //find coordinates of nearest node to P1 building
    Coordinates p2NearestCord = nearestNodetoBuilding(Footways, BuildingInfo2, Nodes, p2NearestNode); //find coordinates of nearest node to P2 building
    Coordinates desNearestCord = nearestNodetoBuilding(Footways, meetingPoint, Nodes, desNearestNode); //find coordinates of nearest node to meeting point building

    cout << endl;
    cout << "Nearest P1 node:" << endl;
    cout << " " << p1NearestCord.ID << endl; //Output details of nearest node to P1 building with coordinates
    cout << " (" << p1NearestCord.Lat << ", " << p1NearestCord.Lon << ")" << endl;

    cout << "Nearest P2 node:" << endl;
    cout << " " << p2NearestCord.ID << endl; //output details of nearest node to P2 building with coordinates
    cout << " (" << p2NearestCord.Lat << ", " << p2NearestCord.Lon << ")" << endl;

    cout << "Nearest destination node:" << endl;
    cout << " " << desNearestCord.ID << endl; //output details of nearest node to meeting point building with coordinates
    cout << " (" << desNearestCord.Lat << ", " << desNearestCord.Lon << ")" << endl;
  
    cout << endl;
    map<long long, double> distances1;
    map<long long, long long> predecessors1;
    map<long long, double> distances2;
    map<long long, long long> predecessors2;

    DijkstraShortestPath(p1NearestNode, G, distances1, predecessors1); //get shortest path between P1 building and meeting point building using Djikstra's algorithm
    DijkstraShortestPath(p2NearestNode, G, distances2, predecessors2); //get shortest path between P2 building and meeting point building using Djikstra's algorithm

    if(distances1[p2NearestNode] >= INF){ //after calling Djikstra's algorithm if distance is still infinity that means no valid path to the meeting point exists
      cout << "Sorry, destination unreachable." << endl << endl;
      cout << "Enter person 1's building (partial name or abbreviation), or #>" << endl;
      getline(cin, person1Building);
      continue;
    }
    

    stack<BuildingInfo> visited; //stack of all visited meeting points
    meetingPoint =  nearestBuildingAgain(BuildingInfo1, BuildingInfo2, Buildings, visited); //get new meeting point
    while(distances1[desNearestNode] >= INF || distances2[desNearestNode] >= INF){// while a meeting point with a valid path for both P1 and P2 is obtained
      cout << "At least one person was unable to reach the destination building. Finding next closest building..." << endl << endl;
      visited.pop();

      meetingPoint = visited.top(); //get new meeting point from the stack
      visited.pop();

      cout << "New destination building:" << endl;
      cout << " " <<  meetingPoint.Fullname << endl; //output details of new meeting point building with exact coordinates
      cout << " (" << meetingPoint.Coords.Lat << ", " << meetingPoint.Coords.Lon << ")" << endl;

      desNearestCord = nearestNodetoBuilding(Footways, meetingPoint, Nodes, desNearestNode); //get coordinates of nearest node to meeting point
      cout << "Nearest destination node:" << endl;
      cout << " " << desNearestCord.ID << endl; //output details of the nearest node with exact coordinates
      cout << " (" << desNearestCord.Lat << ", " << desNearestCord.Lon << ")" << endl;
      DijkstraShortestPath(p1NearestNode, G, distances1, predecessors1); //get shortest path between P1 building and new meeting point
      DijkstraShortestPath(p2NearestNode, G, distances2, predecessors2); //get shortest path between P2 building and new meeting point
    }

    cout <<  "Person 1's distance to dest: " << distances1[desNearestNode] << " miles" << endl; //output distace from Person 1 Node to meeting point node

    cout << "Path: ";
    vector<long long>path = getPath(predecessors1, desNearestNode); //vector to store the path from Person 1 building to meeting point building
    cout << path[0];
    for(int i = 1; i<path.size(); i++){ //output the path
      cout << "->" << path[i];
    }

    cout << endl;
    cout << endl;

    cout <<  "Person 2's distance to dest: " << distances2[desNearestNode] << " miles" << endl; //output distance from Person 2 Node to meeting point node

    cout << "Path: ";
    path = getPath(predecessors2, desNearestNode); //get path from Person 2 building to meeting point building
    cout << path[0];
    for(int i = 1; i<path.size(); i++){ //output the path
      cout << "->" << path[i];
    }

    cout << endl;
    cout << endl;
    cout << "Enter person 1's building (partial name or abbreviation), or #> ";
    getline(cin, person1Building);
  }    
}

void buildGraph(graph<long long, double>& G, map<long long, Coordinates>&  Nodes, vector<FootwayInfo>& Footways, vector<BuildingInfo>& Buildings){ //The purpose of this funtion is to build the graph where all the buildings are vertices and the footways are nodes
  bool result = true;
  for(auto temp : Nodes){ //loop through all Nodes 
      result = G.addVertex(temp.first); //add the vertex into the graph
  }

  double distance = 0;
  for(auto temp : Footways){
    for(int i = 0; i<temp.Nodes.size()-1; i++){
        distance = distBetween2Points((Nodes[temp.Nodes[i]]).Lat, (Nodes[temp.Nodes[i]]).Lon, (Nodes[temp.Nodes[i+1]]).Lat, (Nodes[temp.Nodes[i+1]]).Lon); //get the edge weight
        result = G.addEdge(temp.Nodes[i], temp.Nodes[i+1], distance); //add edge (to and from)
        result = G.addEdge(temp.Nodes[i+1], temp.Nodes[i], distance); //add edge (from and to)
    }
  }
}


int main() {
  graph<long long, double> G; 
  // maps a Node ID to it's coordinates (lat, lon)
  map<long long, Coordinates>  Nodes;
  // info about each footway, in no particular order
  vector<FootwayInfo>          Footways;
  // info about each building, in no particular order
  vector<BuildingInfo>         Buildings;
  XMLDocument                  xmldoc;

  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << std::setprecision(8);

  string def_filename = "map.osm";
  string filename;

  cout << "Enter map filename> ";
  getline(cin, filename);

  if (filename == "") {
    filename = def_filename;
  }

  //
  // Load XML-based map file
  //
  if (!LoadOpenStreetMap(filename, xmldoc)) {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }

  //
  // Read the nodes, which are the various known positions on the map:
  //
  int nodeCount = ReadMapNodes(xmldoc, Nodes);

  //
  // Read the footways, which are the walking paths:
  //
  int footwayCount = ReadFootways(xmldoc, Footways);

  //
  // Read the university buildings:
  //
  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

  //
  // Stats
  //
  assert(nodeCount == (int)Nodes.size());
  assert(footwayCount == (int)Footways.size());
  assert(buildingCount == (int)Buildings.size());

  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;

  buildGraph(G, Nodes, Footways, Buildings);

  //
  // Build the graph, output stats:
  //
  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  cout << endl;

  // Execute Application
  application(Nodes, Footways, Buildings, G);

  //
  // done:
  //

  cout << endl;
  cout << "** Done **" << endl;
  return 0;
}

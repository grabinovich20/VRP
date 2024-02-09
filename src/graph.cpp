#include "graph.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

//Will store elements in our tree based off of closest distance
bool CustomComparator::operator()(const Node& a, const Node& b) const {
    if (a.isPickUp && !b.isPickUp) {
        return true;
    }else if (!a.isPickUp && b.isPickUp) {
        return false;
    }else{
        return (a.edge + a.parentDist) < (b.edge + b.parentDist);
    }

}

//Finds the Euclidean distance
double distanceEuclidean(double x1, double x2, double y1, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;

    double distanceSquared = dx * dx + dy * dy;

    return sqrt(distanceSquared);
}

//Lets us hash our Nodes
namespace std {
    template <>
    struct hash<Node> {
        size_t operator()(const Node& n) const {
            // Hash the id field of the Node
            return hash<double>()(n.id);
        }
    };
}

//Prints the output in the requried format
void printOutput(vector<int> &path) {
    if (path.empty()) {
        return;
    }

    cout << "[";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i+1 != path.size()) {
            cout << ",";
        }
    }
    cout << "]";
}

//add an edge to the adjacency list
void Graph::makeEdge(Node node1, Node node2) {
    (*adjList)[node1].insert(node2);
}

//add a vertex to the adjacency list
 void Graph::makeVertex(Node node) {
    auto it = adjList->find(node);

    if (it == adjList->end()) {
        (*adjList)[node] = {};
    }
 }

//Finds the shortes path. Uses as combination of BFS and Dijkstra's algorithm ideas.
 void Graph::findShortestPath(Node &start, int size) {
    vector<double> distance;
    distance.push_back(0);
    queue<Node> q;
    q.push(start);
    unordered_map<Node, bool> *visited = new unordered_map<Node, bool>();
    (*visited)[start] = true;
    double max = 12 * 60;
    bool pickUp = true, newDriver = false;
    int drivers = 1;
    int current = 0;
    vector<vector<int>> order(drivers, vector<int>());
    int total = 0;

    while (!q.empty()) {
        Node element = q.front();
        q.pop();

        if (total == size) {
            break;
        }

        //need a new driver
        if (newDriver) {
            newDriver = false;
            drivers++;
            distance.push_back(0);
            order.push_back(vector<int>());
            current = drivers-1;
        }

        auto it = adjList->find(element);

        if (it == adjList->end()) {
            continue;
        }

        //keep track of the current driver
       int i = current;

        //loop through the neighbors
         for (auto &a : it->second) {
            if ((*visited)[a] != true && pickUp) {
                double totalRound = distance[i] + a.edge + destination[a.id-1] + backHome[a.id-1];
                if (totalRound >= max && current == i) {
                    newDriver = true;
                    break;
                }else if (current == i){
                    if (newDriver) {
                        newDriver = false;
                    }
                    (*visited)[a] = true;
                    q.push(a);
                    pickUp = false;
                    distance[i] += a.edge + destination[a.id-1];
                    break;
                }

            }else if ((*visited)[a] != true && a.destId == element.id) {
                (*visited)[a] = true;
                q.push(a);
                pickUp = true;
                order[i].push_back(a.destId);
                total += 1;
                break;
            }

         }

        //if there is a new driver, have them start at (0,0)
        if (newDriver) {
            q.push(Node(0));
        }
    }

    //prints out the paths
    int count = 0;
    for (auto &a : order) {
        printOutput(a);
        if (count != 0 || count + 1 != order.size()) {
            cout << endl;
        }
        count++;
    }

    //Exit our program, bypasses all memory cleanup since we are exiting the program
    exit(0);

    delete visited;

 }

 //constructor
 Graph::Graph() {
   adjList = new unordered_map<Node, set<Node, CustomComparator>>();
}

//will print our adjacency list
void Graph::printAdjList() {
   ofstream out;
   out.open("test.txt");


   if (out.fail()) {
       cerr << "couldn't open output file" << endl;
       exit(-1);
   }

   for (const auto &a : *adjList) {
       auto name = a.first;
       out << "(" << name.id << ", " << name.edge << "): ";
       for (const auto &b : a.second) {
           out << "(" << b.id << ", " << b.edge + b.parentDist << "), ";
       }
       out << endl;
   }

}

//checks if a node is in our adjacency list
bool Graph::containsNode(Node node1, Node node2) {
   auto iteratorMap = adjList->find(node1);


   if (iteratorMap != adjList->end()) {
       auto it = iteratorMap->second.find(node2);
       if (it != iteratorMap->second.end()) {
           return true;
       }
   }


   return false;
}

//memory cleanup
 Graph::~Graph() {
   delete adjList;
}
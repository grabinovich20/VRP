#include "graph.h"
#include <fstream>
#include <iostream>
#include <unordered_set>

using namespace std;

bool CustomComparator::operator()(const Node& a, const Node& b) const {
    return a.edge < b.edge;
}

void Graph::makeEdge(Node node1, Node node2) {
    (*adjList)[node1.id].insert(node2);
}

 void Graph::makeVertex(Node node) {
    auto it = adjList->find(node.id);

    if (it == adjList->end()) {
        (*adjList)[node.id] = {};
    }
 }

 void Graph::findShortestPath() {
    
 }

 Graph::Graph() {
   adjList = new unordered_map<double, set<Node, CustomComparator>>();
}


void Graph::printAdjList() {
   ofstream out;
   out.open("test.txt");


   if (out.fail()) {
       cerr << "couldn't open output file" << endl;
       exit(-1);
   }

   for (const auto &a : *adjList) {
       auto name = a.first;
       out << "(" << name << "): ";
       for (const auto &b : a.second) {
           out << "(" << b.id << ", " << b.edge << "), ";
       }
       out << endl;
   }

}

bool Graph::containsNode(Node node1, Node node2) {
   auto iteratorMap = adjList->find(node1.id);


   if (iteratorMap != adjList->end()) {
       auto it = iteratorMap->second.find(node2);
       if (it != iteratorMap->second.end()) {
           return true;
       }
   }


   return false;
}


 Graph::~Graph() {
   delete adjList;
}
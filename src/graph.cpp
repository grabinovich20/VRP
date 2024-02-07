#include "graph.h"
#include <fstream>
#include <iostream>
#include <unordered_set>

using namespace std;

void Graph::makeEdge(Node node1, Node node2) {
    (*adjList)[node1].insert(node2);
}

 void Graph::makeVertex(Node node) {
    auto it = adjList->find(node);

    if (it == adjList->end()) {
        (*adjList)[node] = {};
    }
 }

 void Graph::findShortestPath() {
    
 }


void Graph::printAdjList(int goal) {
   ofstream out;
   out.open("test.txt");


   if (out.fail()) {
       cerr << "couldn't open output file" << endl;
       exit(-1);
   }

}

 Graph::~Graph() {
   delete adjList;
}
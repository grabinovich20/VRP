#ifndef GRAPH
#define GRAPH

#include <unordered_map>
#include <set>
#include <utility>
#include "node.h"

struct CustomComparator {
    bool operator()(const Node& a, const Node& b) const;
};


class Graph {
    public:
        Graph();
        void makeEdge(Node node1, Node node2);
        void makeVertex(Node node);
        void findShortestPath();
        void printAdjList();
        bool containsNode(Node node1, Node node2);
        ~Graph();
    private:
        std::unordered_map<double, std::set<Node, CustomComparator>>* adjList;
};


#endif
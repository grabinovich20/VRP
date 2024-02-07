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
        Graph(int vertices);
        void makeEdge(Node node1, Node node2);
        void makeVertex(Node node);
        void findShortestPath();
        void printAdjList(int goal);
        ~Graph();
    private:
        std::unordered_map<Node, std::set<Node, CustomComparator>>* adjList;
};


#endif
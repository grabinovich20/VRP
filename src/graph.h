#ifndef GRAPH
#define GRAPH

#include <unordered_map>
#include <set>
#include <utility>
#include <vector>
#include "node.h"

struct CustomComparator {
    bool operator()(const Node& a, const Node& b) const;
};


class Graph {
    public:
        Graph();
        void makeEdge(Node node1, Node node2);
        void makeVertex(Node node);
        void findShortestPath(Node &start, int size);
        void printAdjList();
        bool containsNode(Node node1, Node node2);
        int shortestHelper(int numberOfDrivers, Node &start, std::vector<std::vector<int>> &order);
        ~Graph();
    private:
        std::unordered_map<Node, std::set<Node, CustomComparator>>* adjList;
};


#endif
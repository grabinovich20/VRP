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
        void setDestination(const std::vector<double>& newDestination) {
            destination = newDestination;
        }
        void setHome(const std::vector<double>& newHome) {
            backHome = newHome;
        }
        std::vector<double> getDestination() const {
            return destination;
        }
        std::vector<double> getHome() const {
            return backHome;
        }
        ~Graph();
    private:
        //Our adjacency list will be a hash map of trees. This will help with efficiency.
        std::unordered_map<Node, std::set<Node, CustomComparator>>* adjList;
        std::vector<double> destination;
        std::vector<double> backHome;
};


#endif
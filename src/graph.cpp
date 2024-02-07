#include "graph.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <algorithm>
#include <chrono>
#include <unordered_set>

using namespace std;

bool CustomComparator::operator()(const Node& a, const Node& b) const {
    if (a.isPickUp && !b.isPickUp) {
        return true;
    }else if (!a.isPickUp && b.isPickUp) {
        return false;
    }else{
        return (a.edge + a.parentDist) < (b.edge + b.parentDist);
    }

}

vector<int> generateRandomNumbers(int min, int max) {
    vector<int> numbers;
    for (int i = min; i < max; ++i) {
        numbers.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(numbers.begin(), numbers.end(), gen);

    return numbers;
}

//Finds the Euclidean distance
double distanceEuclidean(double x1, double x2, double y1, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;

    double distanceSquared = dx * dx + dy * dy;

    return sqrt(distanceSquared);
}

namespace std {
    template <>
    struct hash<Node> {
        size_t operator()(const Node& n) const {
            // Hash the id field of the Node
            return hash<double>()(n.id);
        }
    };
}

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

void Graph::makeEdge(Node node1, Node node2) {
    (*adjList)[node1].insert(node2);
}

 void Graph::makeVertex(Node node) {
    auto it = adjList->find(node);

    if (it == adjList->end()) {
        (*adjList)[node] = {};
    }
 }

 void Graph::findShortestPath(Node &start, int size) {
    double distance = 0;
    // unordered_map<Node, bool> *visited = new unordered_map<Node, bool>();
    // queue<Node> q;
    // q.push(start);
    // (*visited)[start] = true;
    // bool pickUp = true;
    // vector<int> path;

    // while (!q.empty()) {
    //     Node element = q.front();
    //     start = element;
    //     q.pop();

    //     auto it = adjList->find(element);

    //     if (it == adjList->end()) {
    //         continue;
    //     }

    //    for (auto &a : it->second) {
    //        if ((*visited)[a] != true && pickUp) {
    //           (*visited)[a] = true;
    //           q.push(a);
    //           pickUp = false;
    //           distance += a.edge;
    //           break;
    //        }
        
    //        if ((*visited)[a] != true && a.destId == element.id) {
    //           (*visited)[a] = true;
    //           q.push(a);
    //           pickUp = true;
    //           distance += a.edge;
    //           path.push_back(a.destId);
    //           break;
    //        }

    //     }
    // }

       auto it = adjList->find(start);
       distance += it->first.edge;

       for (auto &a : it->second) {
            Node node(a.destId);
            auto itDist = adjList->find(node);
            distance += a.edge + a.parentDist + itDist->first.edge;
        }



    int numberOfDrivers = (distance / (12 * 60)) + 1;

    // if (numberOfDrivers == 1) {
    //     printOutput(path);
    // }

    double total = 0;
    bool found = true;

    while (found) {
        vector<vector<int>> order(numberOfDrivers, vector<int>());
        total = shortestHelper(numberOfDrivers, start, order);
        numberOfDrivers++;

        if (total == size) {
            int count = 0;
            for (auto &a : order) {
                printOutput(a);
                if (count != 0 || count + 1 != order.size()) {
                    cout << endl;
                }
                count++;
            }
            break;
        }
    }


    // delete visited;


 }

 int Graph::shortestHelper(int numberOfDrivers, Node &start, vector<vector<int>> &order) {
    queue<Node> qArr[numberOfDrivers];
    vector<double> location(numberOfDrivers, 0);
    vector<bool> pickUp(numberOfDrivers, true);
    double distances[numberOfDrivers];
    double total = 0;
    double max = 12 * 60;
    double buffer = 200;
    int min = INT_MAX;

    //Setting our random seed
    // random_device rd;
    // mt19937 gen(rd());
    // uniform_int_distribution<int> dis(0, numberOfDrivers - 1); 

    unordered_map<Node, bool> *visited = new unordered_map<Node, bool>();

    for (int i = 0; i < numberOfDrivers; i++) {
        qArr[i] = queue<Node>();
        qArr[i].push(start);
        distances[i] = 0;
    }

    bool empty = true;
    // vector<int> randomNumbers = generateRandomNumbers(0, numberOfDrivers);

    while (empty) {
        // reverse(randomNumbers.begin(), randomNumbers.end());
        for (auto &a : order) {
            if (a.size() > 0 && a.size() < min) {
                min = a.size();
            }
        }

        // for (int k = 0; k < randomNumbers.size(); k++) {
        for (int i = 0; i < numberOfDrivers; i++) {

            // int i = randomNumbers[k];

            if (qArr[i].empty()) {
                continue;
            }

            Node element = qArr[i].front();
            qArr[i].pop();

            auto it = adjList->find(element);

            if (it == adjList->end()) {
                continue;
            }

            for (auto &a : it->second) {

                if ((*visited)[a] != true && pickUp[i]) {
                    auto itLast = adjList->find(Node(a.destId));
                    if ((distances[i] + a.edge + a.parentDist + itLast->first.edge) < max) {
                        (*visited)[a] = true;
                        qArr[i].push(a);
                        pickUp[i] = false;
                        distances[i] += a.edge + a.parentDist;
                        break;
                    }
                }

                if ((*visited)[a] != true && a.destId == element.id && a.destId != 0) {
                    (*visited)[a] = true;
                    qArr[i].push(a);
                    pickUp[i] = true;
                    order[i].push_back(a.destId);
                    // if (i == 0) {
                    //     total += a.edge;
                    // }   
                    break;
                }

            }
        

        for (auto &a : qArr) {
          if (a.empty()) {
            empty = false;
          }else if (!a.empty()) {
            empty = true;
            break;
          }
        }
      }
    }
 
    for (auto &a : order) {
        total += a.size();
    }
    // cout << total << endl;

    delete visited;

    return total;
 }

 Graph::Graph() {
   adjList = new unordered_map<Node, set<Node, CustomComparator>>();
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
       out << "(" << name.id << ", " << name.edge << "): ";
       for (const auto &b : a.second) {
           out << "(" << b.id << ", " << b.edge + b.parentDist << "), ";
       }
       out << endl;
   }

}

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


 Graph::~Graph() {
   delete adjList;
}
#include <fstream>
#include <sstream>
#include <cmath>
#include "graph.h"
#include "input.h"

using namespace std;

//store the input in a vector
void readInput(vector<string> &input, string inputFile) {
    ifstream in;
    in.open(inputFile);


    if (in.fail()) {
        cerr << "Could not open file!" << endl;
        exit(-1);
    }

    string line;

    while (getline(in,line)) {
        input.push_back(line);
    }

    in.close();
}

//Constructs our graph
void makeGraph(string inputFile) {
    vector<string> input;

    //storing the input into a vector
    readInput(input, inputFile);

    //Converting the input file to the proper type
    string firstLine;
    char open, comma, close, space;
    int id;
    double pickupX, pickupY, dropX, dropY;
    vector<double> pX, pY, dX, dY;

    for (size_t i = 1; i < input.size(); i++) {
        istringstream stream(input[i]);

        // Read the data from the current line
        stream >> id >> open >> pickupX >> comma >> pickupY >> close >> space >> dropX >> comma >> dropY >> close;

        // Store the data into corresponding vectors
        pX.push_back(pickupX);
        pY.push_back(pickupY);
        dX.push_back(dropX);
        dY.push_back(dropY);
    }

    //Making our graph
    Graph *graph = new Graph();

    Node start(0, 0, false, false, 0, true, 0, 0, 0);

    vector<bool> visited(pX.size(), false);
    vector<double> weights(pX.size(), 0), home(pX.size(), 0);

    graph->makeVertex(start);

    //Make min number of edges
    for (size_t i = 0; i < pX.size(); i++) {
        double d1 = distance(0, pX[i], 0, pY[i]);
        double d2 = distance(pX[i], dX[i], pY[i], dY[i]);
        double d3 = distance(0, dX[i], 0, dY[i]);
        Node temp(i+1, d1, true, false, 0, false, pX[i], pY[i], d2);
        graph->makeEdge(start, temp);
        home[i] = d3;
        weights[i] = d2;

    }

    //Add edges from all destination nodes to all pick up nodes (besides correlated pick up nodes)
    for (size_t i = 0; i < pX.size(); i++) {
        Node currentP(i+1, 0, true, false, i+1.5, false, pX[i], pY[i], 0);
        Node currentD(i+1.5, 0, false, true, i-0.5, false, dX[i], dY[i], 0);
        for (int j = 0; j < pX.size(); j++) {
            double d1 = distance(currentP.x, currentD.x, currentP.y, currentD.y);
            double d2 = distance(pX[j], currentD.x, pY[j], currentD.y);

            if (j+1 == currentP.id) {
                graph->makeEdge(currentP, Node(j+1.5, d1, true, false, j+1, false, pX[j], pY[j], 0));
            }else{
                graph->makeEdge(currentD, Node(j+1, d2, true, false, j+1.5, false, dX[j], dY[j], 0));
            }
        }
    }

    graph->setDestination(weights);
    graph->setHome(home);
    // graph->printAdjList();
    graph->findShortestPath(start, pX.size());

    delete graph;

}

//Finds the Euclidean distance
double distance(double x1, double x2, double y1, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;

    double distanceSquared = dx * dx + dy * dy;

    return sqrt(distanceSquared);
}
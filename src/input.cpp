#include <fstream>
#include <sstream>
#include <cmath>
#include <queue>
#include "graph.h"
#include "input.h"

using namespace std;

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

    // cout << "out of initial" << endl;

    in.close();
}

void makeGraph(string inputFile) {
    vector<string> input;

    cout << inputFile << endl;

    //storing the input into a vector
    readInput(input, inputFile);

    //Converting the input file to the proper type
    string firstLine;
    char open, comma, close, space;
    int id;
    double pickupX, pickupY, dropX, dropY;
    vector<double> pX, pY, dX, dY;

    for (int i = 1; i < input.size(); i++) {
        istringstream stream(input[i]);

        // Read the data from the current line
        stream >> id >> open >> pickupX >> comma >> pickupY >> close >> space >> dropX >> comma >> dropY >> close;

        cout << "Read values: " << id << ", (" << pickupX << ", " << pickupY << "), (" << dropX << ", " << dropY << ")" << endl;

        // Store the data into corresponding vectors
        pX.push_back(pickupX);
        pY.push_back(pickupY);
        dX.push_back(dropX);
        dY.push_back(dropY);
    }

    //Making our graph

    Graph *graph = new Graph();

    Node start(0, 0, false, false, 0, true, 0, 0);

    graph->makeVertex(start);

    for (int i = 0; i < pX.size(); i++) {
        Node temp(i+1, distance(0, pX[i], 0, pY[i]), true, false, i+1.5, false, pX[i], pY[i]);
        graph->makeEdge(start, temp);
        graph->makeEdge(temp, start);

        temp = Node(i+1.5, distance(pX[i], dX[i], pY[i], dY[i]), false, true, i+1, false, dX[i], dY[i]);
        graph->makeEdge(start, temp);
        graph->makeEdge(temp, start);
    }

    vector<bool> visited(pX.size(), false);


    for (int i = 0; i < pX.size(); i++) {
        Node currentP(i+1, 0, true, false, i+1.5, false, pX[i], pY[i]);
        Node currentD(i+1.5, 0, false, true, i-0.5, false, dX[i], dY[i]);
        for (int j = 0; j < pX.size(); j++) {
            graph->makeEdge(currentP, Node(j+1.5, distance(pX[j], dX[i], pY[j], dY[i]), true, false, j+1, false, pX[j], pY[j]));
            graph->makeEdge(currentD, Node(j+1, distance(pX[i], dX[j], pY[i], dY[j]), true, false, j+1.5, false, dX[j], dY[j]));
        }
    }

    graph->printAdjList();

    delete graph;

}

//Finds the Euclidean distance
double distance(double x1, double x2, double y1, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;

    double distanceSquared = dx * dx + dy * dy;

    return sqrt(distanceSquared);
}
#include <fstream>
#include <sstream>
#include <queue>
#include "graph.h"
#include "input.h"

using namespace std;

void readInput(vector<string> &input, string inputFile) {
    ifstream in;
    //For debugging
    // string input_file = "0-sample_in.txt";
    in.open(inputFile);
    // in.open(input_file);

    if (in.fail()) {
        cerr << "Could not open file!" << endl;
        exit(-1);
    }

    string line;

    while (getline(in,line)) {
        input->push_back(line);
    }

    // cout << "out of initial" << endl;

    in.close();
}

void makeGraph(string inputFile) {
    vector<string> input;

    //storing the input into a vector
    readInput(input, inputFile);
}
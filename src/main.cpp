#include "input.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    if (argc > 2) {
        cerr << "Invalid number of arguments!" << endl;
        return -1;
    }

    makeGraph(string(argv[1]));

    return 0;
}
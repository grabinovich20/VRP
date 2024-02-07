#ifndef INPUT
#define INPUT

#include <vector>
#include <iostream>

void readInput(std::vector<std::string> *input, std::string inputFile);
void makeGraph(std::string inputFile);
double distance(double x1, double x2, double y1, double y2);

#endif
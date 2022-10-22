#include <iostream>
#include <string>
#include <vector>
#include "include/InputFile.hpp"
#include "include/NearestNeighborsSearch.hpp"

using namespace std;

int main(int argc, char **argv)
{
    string name, weightType;
    string fileName(argv[1]);

    InputFile inputFile(fileName);
    vector<pair<double, double>> graph = inputFile.getFileContent(name, weightType);

    NearestNeighborsSearch nearestNeighborsSearch(graph);
    double cicleSize = nearestNeighborsSearch.tsp(weightType);

    cout << name << " " << weightType << " " << cicleSize << endl;

    return 0;
}
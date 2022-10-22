#include <vector>
#include <string>
#include <cmath>
#include <time.h>

#define INF 0x3f3f3f3f

using namespace std;

class NearestNeighborsSearch
{
private:
    vector<pair<double, double>> points;
    double getEuclideanDistance(const pair<double, double> xiYi, const pair<double, double> xjYj);
    double getPseudoEuclideanDistance(const pair<double, double> xiYi, const pair<double, double> xjYj);

public:
    NearestNeighborsSearch(vector<pair<double, double>> points);
    ~NearestNeighborsSearch();
    double tsp(const string weightType);
};

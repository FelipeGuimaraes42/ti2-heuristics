#include "include/NearestNeighborsSearch.hpp"

NearestNeighborsSearch::NearestNeighborsSearch(vector<pair<double, double>> points)
{
    this->points = points;
}

NearestNeighborsSearch::~NearestNeighborsSearch()
{
}

double NearestNeighborsSearch::getEuclideanDistance(const pair<double, double> xiYi, const pair<double, double> xjYj)
{
    double xd = xiYi.first - xjYj.first;
    double yd = xiYi.second - xjYj.second;
    return floor(sqrt(xd * xd + yd * yd));
}

double NearestNeighborsSearch::getPseudoEuclideanDistance(const pair<double, double> xiYi, const pair<double, double> xjYj)
{
    double xd = xiYi.first - xjYj.first;
    double yd = xiYi.second - xjYj.second;
    double rij = sqrt((xd * xd + yd * yd) / 10.0);
    double tij = floor(rij);

    if (tij < rij)
    {
        return tij + 1.0;
    }
    return tij;
}

double NearestNeighborsSearch::tsp(const string weightType)
{
    srand(time(0));
    int n = this->points.size();

    bool visitedCities[n] = {false};

    int first = rand() % n;
    visitedCities[first] = true;

    int u = first;

    double result = 0;

    while (true)
    {
        bool run = false;
        for (int i = 0; i < n; i++)
        {
            if (visitedCities[i] == false)
            {
                run = true;
            }
        }
        if (!run)
        {
            break;
        }

        int distance = INF;
        int vertice = -1;

        for (int v = 0; v < n; v++)
        {
            if (!visitedCities[v])
            {
                double currentDistance;
                if (weightType == "EUC_2D")
                {
                    currentDistance = getEuclideanDistance(this->points[u], this->points[v]);
                }
                else
                {
                    currentDistance = getPseudoEuclideanDistance(this->points[u], this->points[v]);
                }

                if (currentDistance < distance)
                {
                    vertice = v;
                    distance = currentDistance;
                }
            }
        }

        visitedCities[vertice] = true;
        result += distance;
        u = vertice;
    }

    return result + (weightType == "EUC_2D" ? getEuclideanDistance(this->points[first], this->points[u]) : getPseudoEuclideanDistance(this->points[first], this->points[u]));
}
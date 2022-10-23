#include "include/VND.hpp"

VND::VND(vector<pair<int, int>> points, string weightType)
{
    this->points = points;
    this->weightType = weightType;
}

VND::~VND()
{
}

double VND::getEuclideanDistance(const pair<int, int> xiYi, const pair<int, int> xjYj)
{
    double xd = xiYi.first - xjYj.first;
    double yd = xiYi.second - xjYj.second;
    return floor(sqrt(xd * xd + yd * yd));
}

double VND::getPseudoEuclideanDistance(const pair<int, int> xiYi, const pair<int, int> xjYj)
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

TSPSolution VND::getConstructiveSolution()
{
    srand(time(0));
    int n = this->points.size();

    bool visitedCities[n] = {false};

    int first = rand() % n;
    visitedCities[first] = true;

    int u = first;

    double solutionValue = 0;

    vector<pair<int, int>> solutionPoints;

    while (true)
    {
        solutionPoints.push_back(this->points.at(u));
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
                if (this->weightType == "EUC_2D")
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
        solutionValue += distance;
        u = vertice;
    }

    solutionValue += (this->weightType == "EUC_2D" ? getEuclideanDistance(this->points[first], this->points[u]) : getPseudoEuclideanDistance(this->points[first], this->points[u]));

    TSPSolution solution(solutionValue, solutionPoints);

    return solution;
}

TSPSolution VND::getTwoOptSolution(TSPSolution previousSolution)
{
    TSPSolution newSolution;
    double minSolution = previousSolution.getValue();
    int size = this->points.size();

    while (true)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                vector<pair<int, int>> twoOpt, aux;
                for (int k = 0; k < i; k++)
                {
                    twoOpt.push_back(this->points.at(k));
                }

                for (int k = i; k < j; k++)
                {
                    aux.push_back(this->points.at(k));
                }

                reverse(aux.begin(), aux.end());

                for (int k = 0; k < aux.size(); k++)
                {
                    twoOpt.push_back(aux.at(k));
                }

                for (int k = j; k < size; k++)
                {
                    twoOpt.push_back(this->points.at(k));
                }
            }
        }
    }
    return newSolution;
}

double VND::tsp()
{
    TSPSolution initialSolution = this->getConstructiveSolution();

    TSPSolution solution(initialSolution.getValue(), initialSolution.getPoints());
    int k = 0;
    double minSolution = solution.getValue();

    while (k < MAX_TENTATIVES)
    {
        if (k == 0)
        {
            solution = this->getTwoOptSolution(solution);
        }
        else
        {
            solution = this->getThreeOptSolution(solution);
        }

        if (solution.getValue() < minSolution)
        {
            minSolution = solution.getValue();
            k = 0;
        }
        else
        {
            k++;
        }
    }

    return solution.getValue();
}

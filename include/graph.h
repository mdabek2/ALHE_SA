#pragma once

#include "node.h"
#include "agent.h"
#include <fstream>
#include <cmath>
#include <iomanip>
#include <climits>
#include <bits/stdc++.h>

using namespace std;


class Graph {
private:
    float temperature;
    vector<Node> nodes;
    double streetCapacity[24]; //index = hour

public:
    void readGraphFromFile(std::string fileName, int scale);

    void drawGraph();

    void updateTemperature(int startTemp, int iteration, int coolOption);

    long long generateNewCases(int time);

    bool emptyNodes();

    long long getSumOfCases();

    long long getAverageOfCases();

    long long getCasesOfNeigh(int nodeId, int neighNumber);

    void setStreetCapacity();

    double getStreetCapacity(int hour);

    float getProbability(int currNodeId, int bestNodeIndex, int worseNodeIndex, int version);

    int checkNextLevelOfNeighbors(int version, int currNodeId, int level);

    int numOfCasesApproach(int currNodeId, int version);

    int distanceApproach(int currNodeId, int version);

    int chooseNode(int currNodeId, int version);

    void startAlgorithm(Agent &agent, int version, int startTemp, int option, FILE *file);

};

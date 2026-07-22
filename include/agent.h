#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Agent {
private:
    int capacity;
    long long vaccinesCount;
    int distanceFromStart;
    vector<int> route;  // vector of nodes inclued in route (id)

public:
    Agent() : capacity(0), distanceFromStart(0) {}

    int getDistanceFromStart();

    void setDistanceFromStart(int distance);

    long long getVaccinesCount();

    void setVaccinesCount(long long count);

    void addNode(int i);
};

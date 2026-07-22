#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Node {
private:
    int id; // id=0 starting point
    int distanceFromStart;
    vector<pair<int, int>> neighbors;  // neigbours vector: (id, distance)
    bool clear;
    long long casesInNode;

public:
    Node() : id(-1), distanceFromStart(0), clear(0), casesInNode(0) {}

    Node(int i, int distance, long long casesOfDisease)
            : id(i), distanceFromStart(distance), casesInNode(casesOfDisease) {}

    int getId();

    void setID(int i);

    bool getClear();

    void setClear(bool value);

    long long getCasesInNode();

    void setCasesInNode(long long i);

    int getDistanceFromStart();

    void setDistanceFromStart(int distance);

    int getNumberOfNeighbors();

    int getIdOfNeigh(int i);

    int getDistanceFromNeigh(int i);

    int getDistanceFromNeighWithId(int i);

    void addNeighbor(int i, int dist);
};


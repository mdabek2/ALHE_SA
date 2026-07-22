#include "../include/node.h"

int Node::getId() {
    return id;
}

void Node::setID(int i) {
    id = i;
}

bool Node::getClear() {
    return clear;
}

void Node::setClear(bool value) {
    clear = value;
}

long long Node::getCasesInNode() {
    return casesInNode;
}

void Node::setCasesInNode(long long i) {
    casesInNode = i;
}

int Node::getDistanceFromStart() {
    return distanceFromStart;
}

void Node::setDistanceFromStart(int distance) {
    distanceFromStart = distance;
}

int Node::getNumberOfNeighbors() {
    return neighbors.size();
}

int Node::getIdOfNeigh(int i) {
    if ((unsigned) i < neighbors.size()) return neighbors[i].first;
    else return -1;
}

int Node::getDistanceFromNeigh(int i) {
    if ((unsigned) i < neighbors.size()) return neighbors[i].second;
    else return -1;
}

int Node::getDistanceFromNeighWithId(int i) {
    unsigned k = 0;
    for (; k < neighbors.size() && neighbors[k].first != i; k++) {}

    if (neighbors[(int) k].first != i) {
        cout << "Error! Node " << this->id << " has no neighbour with id = " << i << endl;
        return -1;
    } else {
        return neighbors[k].second;
    }
}

void Node::addNeighbor(int i, int dist) {
    neighbors.push_back(make_pair(i, dist));
}

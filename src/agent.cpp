#include "../include/agent.h"

int Agent::getDistanceFromStart() {
    return distanceFromStart;
}

void Agent::setDistanceFromStart(int distance) {
    distanceFromStart = distance;
}

long long Agent::getVaccinesCount() {
    return vaccinesCount;
}

void Agent::setVaccinesCount(long long count) {
    vaccinesCount = count;
}

void Agent::addNode(int i) {
    route.push_back(i);
}

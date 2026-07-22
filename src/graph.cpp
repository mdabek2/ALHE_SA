#include "../include/graph.h"

void Graph::readGraphFromFile(std::string fileName, int scale) {
    std::ifstream file;
    file.open(fileName, std::fstream::in);
    if (file.is_open()) {
        char c;
        while (file >> c) {
            int id, distance, cases;
            //read new node
            if (c == '{') {
                file >> id >> distance >> cases >> c;
                Node node(id, distance*scale, cases);
                node.setClear(0);
                //read neighbours
                while ((file >> c) && c == '{') {
                    file >> id >> distance >> c;
                    node.addNeighbor(id, distance*scale);
                }
                nodes.push_back(node);
            }
        }
    }
}

void Graph::drawGraph() {
    for (unsigned i = 0; i < nodes.size(); i++) {
        cout << "Node " << i << ":" << endl;
        cout << "Distance from starting point: " << nodes[i].getDistanceFromStart() << endl;
        cout << "Number of cases: " << nodes[i].getCasesInNode() << endl;

        for (int k = 0; k < nodes[i].getNumberOfNeighbors(); k++)
            cout << "\t ------ " << nodes[i].getDistanceFromNeigh(k) << " -------> " << nodes[i].getIdOfNeigh(k)
                 << " (" << getCasesOfNeigh(i, k) << ")" << endl;

        cout << endl;
    }
}

void Graph::updateTemperature(int startTemp, int iteration, int coolOption) {
    float newTemperature;
    switch (coolOption) {
        case 1: //logarythmic cooling
            newTemperature = (float) startTemp / (2 * log10(iteration));
            break;
        case 2: //linear cooling
            newTemperature = (float) startTemp / (iteration);
            break;
        case 3: //geometric cooling
            newTemperature = (float) pow(2, iteration) * startTemp;
            break;
    }
    temperature = newTemperature;
}

long long Graph::generateNewCases(int time) {
    long long sumOfNewCases = 0;
    long long newCases;
    //id = 0 is a starting point, no cases there
    for (unsigned i = 1; i < nodes.size(); i++) {
        if (nodes[i].getClear() == 0) {
            if (nodes[i].getCasesInNode() == 0) {
                newCases = 0.3 * getAverageOfCases();
            } else {
                newCases = nodes[i].getCasesInNode() + pow(nodes[i].getCasesInNode(), time);
            }
            nodes[i].setCasesInNode(newCases);
            sumOfNewCases += newCases;
        } else
            nodes[i].setClear(1);
    }
    return sumOfNewCases;
}

bool Graph::emptyNodes() {
    //id = 0 is a starting point, no cases there
    for (unsigned i = 1; i < nodes.size(); i++)
        if (nodes[i].getClear() == 0) return false;

    return true;
}

long long Graph::getSumOfCases() {
    long long sum = 0;
    for (unsigned i = 0; i < nodes.size(); i++)
        sum += nodes[i].getCasesInNode();

    return sum;
}

long long Graph::getAverageOfCases() {
    return getSumOfCases() / nodes.size();
}

long long Graph::getCasesOfNeigh(int nodeId, int neighNumber) {
    int neighId = nodes[nodeId].getIdOfNeigh(neighNumber);
    return nodes[neighId].getCasesInNode();
}

void Graph::setStreetCapacity() {
    for (int i = 0; i < 24; ++i) {
        if (i < 7 || i >= 20)
            streetCapacity[i] = 1;
        else if (i == 7 || i == 15 || i == 16)
            streetCapacity[i] = 0.5;
        else if (i == 8 || i == 9 || i == 13 || i == 14)
            streetCapacity[i] = 0.7;
        else
            streetCapacity[i] = 0.8;
    }
}

double Graph::getStreetCapacity(int hour) {
    return streetCapacity[hour];
}

float Graph::getProbability(int currNodeId, int bestNodeIndex, int worseNodeIndex, int version) {
    float probability = 0.0f;
    switch (version) {
        case 3:
            probability = exp(-1 * (nodes[bestNodeIndex].getCasesInNode() - nodes[worseNodeIndex].getCasesInNode()) /
                              temperature);
            break;
        case 4:
            probability = exp(-1 * (nodes[bestNodeIndex].getCasesInNode() - nodes[worseNodeIndex].getCasesInNode()) /
                              temperature);
            break;
        default:
            break;
    }
    return probability;
}

int Graph::checkNextLevelOfNeighbors(int version, int currNodeId, int level) {
    vector<int> checked;
    vector <pair<int, pair <int, long long>>> v1;     // pair: first - id of the node we want to reach,
                                                // second.first - id of the first node's neighbour, that we need to visit to get to it
                                                // second.second - distance to the node we want to reach from currNodeId
    vector <pair<int, pair <int, long long>>> v2;
    int nodeId;
    long long maximum = LONG_LONG_MIN;
    long long minimum = LONG_LONG_MAX;
    int nextIndex = 0;
    long long distance;

    v1.push_back(make_pair(currNodeId, make_pair(0, 0)));
    checked.push_back(currNodeId);

    for (int i = 0; i < nodes[currNodeId].getNumberOfNeighbors(); i++) {
        distance = nodes[currNodeId].getDistanceFromNeigh(i);
        v2.push_back(make_pair(nodes[currNodeId].getIdOfNeigh(i), make_pair(nodes[currNodeId].getIdOfNeigh(i), distance)));
        checked.push_back(nodes[currNodeId].getIdOfNeigh(i));
    }
    
    for (int i = 1; i < level; i++) {
        v1.clear();
        for (unsigned j = 0; j < v2.size(); j++)
            v1.push_back(v2[j]);

        v2.clear();
        for (unsigned j = 0; j < v1.size(); j++) {
            for (int k = 0; k < nodes[v1[j].first].getNumberOfNeighbors(); k++) {

                nodeId = nodes[v1[j].first].getIdOfNeigh(k);
                distance = nodes[v1[j].first].getDistanceFromNeigh(k);
                if (find(checked.begin(), checked.end(), nodeId) == checked.end()) {
                    v2.push_back(make_pair(nodeId, make_pair(v1[j].second.first, (v1[j].second.second + distance))));
                    checked.push_back(nodeId);
                }
            }
        }
        // if we check all the neigbours, return -1
        if (v2.empty()) return -1;

    }
    
    // when there are neighbours on this level, check if they have been served
    for (unsigned i = 0; i < v2.size(); i++) {
        nodeId = v2[i].first;
        if (nodes[nodeId].getClear() == 1) v2.erase(v2.begin() + i);
    }

    // if we served all nejghbours on his level, search deeper
    if (v2.empty()) return 0;

    if (version == 2 || version == 4) {
        // if there are any neighbours left on this level, chose the one with the biggest number of cases
        for (unsigned i = 0; i < v2.size(); i++) {
            if (nodes[v2[i].first].getCasesInNode() >= maximum) {
                maximum = nodes[v2[i].first].getCasesInNode();
                nextIndex = v2[i].second.first;
            }
        }

        if (version == 4){
            for (unsigned i = 0; i < v2.size(); i++) {
                if (nodes[v2[i].first].getCasesInNode() <= maximum){
                    if ((float) rand() / RAND_MAX < getProbability(currNodeId, nextIndex, v2[i].first, version))
                        nextIndex = v2[i].second.first;
                }
            }
        }
    }
    else if (version == 1 || version == 3) {
        // if there are any neighbours left on this level, chose the one with the smallest distance
        for (unsigned i = 0; i < v2.size(); i++) {
            if (v2[i].second.second <= minimum) {
                minimum = v2[i].second.second;
                nextIndex = v2[i].second.first;
            }
        }

        if (version == 3){
            for (unsigned i = 0; i < v2.size(); i++) {
                if (v2[i].second.second >= minimum){
                    if ((float) rand() / RAND_MAX < getProbability(currNodeId, nextIndex, v2[i].first, version)){
                        nextIndex = v2[i].second.first;
                    }
                }
            }
        }
    }
    cout << nextIndex << endl;
    
    return nextIndex;
}

int Graph::numOfCasesApproach(int currNodeId, int version) {
    int numOfNeigh = nodes[currNodeId].getNumberOfNeighbors();
    int isClear;
    int neighId;
    long long maximum = LONG_LONG_MIN;
    int maxIndex = 0;

    for (int i = 0; i < numOfNeigh; i++) {
        neighId = nodes[currNodeId].getIdOfNeigh(i);
        isClear = nodes[neighId].getClear();
        if (getCasesOfNeigh(currNodeId, i) >= maximum && isClear == 0) {
            maximum = getCasesOfNeigh(currNodeId, i);
            maxIndex = neighId;
        }
    }

    if (version == 4) {
        // Simulated Annealing alg
        if (maxIndex != 0) {
            for (int i = 0; i < numOfNeigh; i++) {
                neighId = nodes[currNodeId].getIdOfNeigh(i);
                isClear = nodes[neighId].getClear();

                if (getCasesOfNeigh(currNodeId, i) <= maximum && isClear == 0)
                    if ((float) rand() / RAND_MAX < getProbability(currNodeId, maxIndex, neighId, version))
                        maxIndex = neighId;
            }
        }
    }

    // if we are stuck - there is no unserved nodes around - we check other neighbours
    if (maxIndex == 0) {
        int i = 1;
        while (maxIndex == 0) {
            i++;
            maxIndex = checkNextLevelOfNeighbors(version, currNodeId, i);
        }

        // if we checked all neighbours, we get back to the starting point
        if (maxIndex == -1) maxIndex = 0;
    }

    return maxIndex;
}

int Graph::distanceApproach(int currNodeId, int version) {
    int numOfNeigh = nodes[currNodeId].getNumberOfNeighbors();
    int isClear;
    int neighId;
    long long minimum = LONG_LONG_MAX;
    int minIndex = 0;

    for (int i = 0; i < numOfNeigh; i++) {
        neighId = nodes[currNodeId].getIdOfNeigh(i);
        isClear = nodes[neighId].getClear();
        if (nodes[currNodeId].getDistanceFromNeigh(i) <= minimum && isClear == 0) {
            minimum = nodes[currNodeId].getDistanceFromNeigh(i);
            minIndex = neighId;
        }
    }
    
    if (version == 3) {
        // Simulated Annealing alg
        if (minIndex != 0) {
            for (int i = 0; i < numOfNeigh; i++) {
                neighId = nodes[currNodeId].getIdOfNeigh(i);
                isClear = nodes[neighId].getClear();
                if (nodes[currNodeId].getDistanceFromNeigh(i) >= minimum && isClear == 0) {
                    if ((float) rand() / RAND_MAX < getProbability(currNodeId, minIndex, neighId, version))
                    {
                        minIndex = neighId;
                    }
                }
            }
        }
    }
    
    // if we are stuck - there is no unserved nodes around - we check other neighbours
    if (minIndex == 0) {
        int i = 1;
        while (minIndex == 0) {
            i++;
            minIndex = checkNextLevelOfNeighbors(version, currNodeId, i);
        }

        // if we checked all neighbours, we get back to the starting point
        if (minIndex == -1) minIndex = 0;
    }

    return minIndex;
}

int Graph::chooseNode(int currNodeId, int version) {
    int nextNodeId = 0;
    switch (version) {
        case 1: 
            nextNodeId = distanceApproach(currNodeId, version);
            break;
        case 2: 
            nextNodeId = numOfCasesApproach(currNodeId, version);
            break;
        case 3:
            nextNodeId = distanceApproach(currNodeId, version);
            break;
        case 4: 
            nextNodeId = numOfCasesApproach(currNodeId, version);
            break;
    }
    return nextNodeId;
}

void Graph::startAlgorithm(Agent &agent, int version, int startTemp, int option, FILE *file) {
    int iteration = 0;
    double time = 0; // days
    double tmpTime = time; // hours
    int countOfVaccines = getSumOfCases();
    long long casesFromStart = countOfVaccines;
    int distance;
    agent.setVaccinesCount(countOfVaccines);

    int startId = 0;
    int destinationId;

    nodes[startId].setClear(1);

    //printing into a file
        fprintf(file, " %f", time * 24);
        fprintf(file, " %f", tmpTime);
        fprintf(file, " %d", startId);
        fprintf(file, " %lld", getSumOfCases());
        fprintf(file, " %lld", agent.getVaccinesCount());
        fprintf(file, " %lld", casesFromStart);
        fprintf(file, " \n");
        
    while (!emptyNodes() && iteration < 100) {
        // temperature updated every iteration
        updateTemperature(startTemp, iteration, option);

        cout << setprecision(4);
        destinationId = chooseNode(startId, version);

        distance = nodes[startId].getDistanceFromNeighWithId(nodes[destinationId].getId());

        for (int i=0; i<distance; i++)
        {
            tmpTime = tmpTime + 1/(60*getStreetCapacity((int)tmpTime%24));
        }

        if (tmpTime >= 24) {
            time++;
            tmpTime -= 24;
            casesFromStart += generateNewCases(time);
            cout << "Polnoc:" << endl;
            drawGraph();
        }

        // leaving vaccines
        if (nodes[destinationId].getCasesInNode() > agent.getVaccinesCount()) {
            nodes[destinationId].setCasesInNode(nodes[destinationId].getCasesInNode() - agent.getVaccinesCount());
            agent.setVaccinesCount(0);
        } else {
            agent.setVaccinesCount(agent.getVaccinesCount() - nodes[destinationId].getCasesInNode());
            nodes[destinationId].setCasesInNode(0);
            nodes[destinationId].setClear(1);
        }

        // adding agents route
        agent.addNode(nodes[destinationId].getId());
        agent.setDistanceFromStart(nodes[destinationId].getDistanceFromStart());

        // if he has any vaccines left, agent moves forward
        if (agent.getVaccinesCount() != 0) {
            //new starting point
            startId = destinationId;
        } else {
            //agent needs to get back to starting point
            for (int i = 0; i < agent.getDistanceFromStart(); i++)
            {
                tmpTime += 1/(60*getStreetCapacity((int) tmpTime % 24));
            }
            if (tmpTime >= 24) {
                time++;
                tmpTime -= 24;
                casesFromStart += generateNewCases(time);
            }

            agent.setVaccinesCount(getSumOfCases());
            agent.setDistanceFromStart(0);
            startId = 0;
        }
        iteration++;
        
        //printing into a file
        fprintf(file, " %f", time * 24);
        fprintf(file, " %f", tmpTime);
        fprintf(file, " %d", startId);
        fprintf(file, " %lld", getSumOfCases());
        fprintf(file, " %lld", agent.getVaccinesCount());
        fprintf(file, " %lld", casesFromStart);
        fprintf(file, " \n");
    }
    return;
}
#include <cstdio>
#include <iostream>

#include "graph.h"
#include "agent.h"
#include "node.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 4) {
        cout << "Wrong number of parameters! Insert filepath." << std::endl;
        return 0;
    }
    FILE *resultFile = fopen("resultFile.gnumeric", "w");
    int version, startTemp, coolOption;
    Agent agent;
    Graph warsaw;
    int seed = atoi(argv[3]);
    srand(seed);
    warsaw.readGraphFromFile(argv[1], atoi(argv[2]));
    warsaw.drawGraph();

    warsaw.setStreetCapacity();

    cout << "Which version of algorithm do you choose:" << endl;
    cout << "1 - greedy algorithm, with nearest neighbour priority" << endl;
    cout << "2 - greedy algorithm, with highest infection priority" << endl;
    cout << "3 - simulated annealing, with nearest neighbour priority" << endl;
    cout << "4 - simulated annealing, with highest infection priority" << endl;
    cin >> version;
    cout << "You chose version number " << version << endl;

    if (version == 3 || version == 4) {
        cout << "You chose simulated annealing. Eneter starting point temperature: " << endl;
        cin >> startTemp;
        cout << "Chose cooling algorithm: (1 - logarythmic, 2 - linear, 3 - geometric)" << endl;
        cin >> coolOption;
    }
    
    fprintf(resultFile, " %s", "Algorithm_option:");
    switch (version) {
        case 1: 
            fprintf(resultFile, " %s", "Greedy_Algorithm, with_nearest_neighbour_priority");
            break;
        case 2: 
            fprintf(resultFile, " %s", "Greedy_Algorithm, with_highest_infection_priority");
            break;
        case 3:
            fprintf(resultFile, " %s", "Simulated_Annealing, with_nearest_neighbour_priority"); 
            fprintf(resultFile, " %s", "start.Temp");
            fprintf(resultFile, " %d", startTemp);   
            fprintf(resultFile, " %s", "cool.Option");
            fprintf(resultFile, " %d", coolOption);   
            break;
        case 4: 
            fprintf(resultFile, " %s", "Simulated_Annealing, with_highest_infection_priority");
            fprintf(resultFile, " %s", "start.Temp");
            fprintf(resultFile, " %d", startTemp);   
            fprintf(resultFile, " %s", "cool.Option");
            fprintf(resultFile, " %d", coolOption);   
            break;
    }
    
    fprintf(resultFile, " %s", "\n");
    fprintf(resultFile, " %s", "seed");
    fprintf(resultFile, " %d", seed);
    fprintf(resultFile, " %s", "\n");
    fprintf(resultFile, " %s", "time");
    fprintf(resultFile, " %s", "time_tmp");
    fprintf(resultFile, " %s", "loc.agent");
    fprintf(resultFile, " %s", "n.cases");
    fprintf(resultFile, " %s", "n.vaccines");
    fprintf(resultFile, " %s", "all.cases");
    fprintf(resultFile, " \n");

    warsaw.startAlgorithm(agent, version, startTemp, coolOption, resultFile);
   
    fclose(resultFile);

    cout << "Results of the experiment were successfully saved to a resultFile.gnumeric file." << endl;
    return 0;
}

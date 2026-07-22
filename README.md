# Vaccine Distribution Optimization using Simulated Annealing

## Overview

This project was developed in **C++** as part of an optimization algorithms course. The goal was to optimize the distribution of vaccines across a city while minimizing both delivery time and the spread of an infectious disease.

The problem combines elements of graph optimization, route planning, and heuristic search under dynamic traffic conditions.

## Problem Description

The city is represented as a weighted graph:
- **Vertices** represent vaccination centers and a central depot.
- **Edges** represent the shortest routes between locations.
- Road capacity changes throughout the day, affecting travel times.
- The number of infected people at each vaccination center increases exponentially until vaccines are delivered. After delivery, new infections stop accumulating at that location.

Example graph for the city of Warsaw:

<img src="/graphs/warszawa.png" width="50%">

The objective is to determine the order in which vaccination centers should be visited in order to:
- minimize the total delivery time,
- minimize the total number of new infections,
- efficiently utilize a vehicle with limited carrying capacity.
 
## Implemented Algorithms

Two routing heuristics were investigated:

- **Nearest Neighbor** – always visit the closest unvisited vaccination center.
- **Highest Infection Priority** – visit the center with the largest number of infected people.

Each heuristic was evaluated using two optimization approaches:

- Greedy Algorithm
- Simulated Annealing with three cooling schedules: logarithmic, linear and geometric.

Different initial temperatures and cooling parameters were tested during the experiments.

## Simulation Assumptions

The simulation includes several realistic constraints:

- one delivery vehicle,
- limited vehicle capacity,
- vaccines are restocked every 24 hours,
- vaccination centers submit new orders every 24 hours,
- road capacity varies depending on the time of day,
- direct return to the depot is always possible,
- the simulation terminates when all orders are completed or after 100 iterations.

## Experiments

The algorithms were evaluated on five different graph instances. One of the vertices in each graph represents the starting point (the depot), from which the agent collects the vaccines. This vertex is connected to every other vertex, allowing direct returns to the depot. For clarity, the connections to vertex 0 have been omitted from the graph visualizations.

- 5 nodes
<img src="/graphs/graph5.png" width="30%">

- 8 nodes
<img src="/graphs/graph8.png" width="30%">

- 10 nodes (Variant I)
<img src="/graphs/graph10_v1.png" width="30%">

- 10 nodes (Variant II)
<img src="/graphs/graph10_v2.png" width="30%">

- 12 nodes
<img src="/graphs/graph12.png" width="30%">

For every graph experiments compared:
- Greedy vs. Simulated Annealing
- Nearest Neighbor vs. Highest Infection Priority
- Different cooling schedules

Performance was evaluated using:

- total delivery time,
- total number of infections.

## Results

The experiments showed that no single algorithm consistently outperformed all others.

Main observations:

- The **Greedy Algorithm** performed better on several smaller and simpler graphs.
- **Simulated Annealing** often produced better solutions when prioritizing highly infected vaccination centers.
- Among the tested cooling schedules, the **logarithmic schedule** generally produced the best results.
- The **geometric schedule** usually achieved the weakest performance.

The effectiveness of each approach strongly depended on the graph structure and the optimization objective.


## Build

Compile the project using:

```bash
make
```

Run the executable from the `bin` directory:

```bash
./run <graph_file> <scale> <random_seed>
```

where:

- `graph_file` – input .txt file with graph description,
- `scale` – graph scale parameter (typically: 1),
- `random_seed` – seed used by `srand()`.

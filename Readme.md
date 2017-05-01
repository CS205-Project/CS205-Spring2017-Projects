# CS205 Spring 2017 Project: Evacuation Strategy

Sonu Mehta, Tomas Gudmundsson,  Dali Moghimi

## Project Description(Problem Statement)

The goal of the project is to find exit selections for evacuees in an emergency situation such that each person is directed to one of the nearest exits taking into account the congestion of the exit. To describe in detail, we start with a floor plan of a building. This plan is converted to a graph with nodes representing a number of floor features (doors, hallways, etc...) and exits available. The graph has the property of being connected with edge weights corresponding to the distance between two nodes. In the case of an emergency evacuation, the goal is to assign each person their nearest exit whilst taking into account possible congestion at the exits. Each exit has its own capacity to safely accomodate evacuees. The algorithm is expected to output the optimal or (near optimal) assignment of evacuees to exits such that the cost is minimized. The cost, in this problem is defined as the sum of the distances of each person from their assigned exit and the added penalty for congestion at each exit.

## Algorithm

We start with an adjacency matrix of the graph representing the floor plan of a building. This graph is a randomly generated, connected, and weighted graph with a few random nodes assigned as exits. For each exit, we use Dijkstra's algorithm to find the shortest distances to each node (representing a location occuppied by an evacuee). Once we have the path to each exit for every evacuee, we assign the nearest exit to each person and calculate the cost of the assignment. In calculating the cost, for now, we assume that the congestion can only be at the exits and not at intervening edges, i.e. any number of persons can pass through an edge at a given point of time. 

Once we have this assignment, we use simulated annealing to try to find the minimal cost configuration. At each iteration, we generate a new configuration by changing the exit assignment of one the persons at random. If the new assignment has lower cost than the older assignment, we accept the configuration and if the cost is higher , we accept the new configuration with probability $= exp((newCost - oldCost))/T$ where $T$ is the temperature. This is continued for a certain number of iterations after which the temperature is reduced to $0.8T$. Ultimately the algorithm settles at some lower cost configuration.

## Parallel Implementation

The above algorithm is sequential and calculates the shortest path distance using Dijkstra one by one. The calculation of shortest paths from a particular exit is independent of the other exits, therefore, we parallelize the algorithm using openmp to calculate the shortest distance from all exits in parallel. This leads to a significant speed-up and speed is crucial in emergency situations requiring an evacuation. Similarly, for simulated annealing, instead of starting with one initial configuration, we start with multiple initial configurations in  parallel and take the best solution at the end. 

Preliminary results:
The following plot shows how long the sequential algorithm took to calculate shortest paths for everyone and apply the simulated annealing technique for graphs of sizes 500, 5000, and 10000 (i.e. the number of people that are evacuated):

![alt tag](https://raw.githubusercontent.com/CS205-Project/CS205-Spring2017-Projects/master/sequentialEvacuationTime.png)


# CS205 Spring 2017 Project: Evacuation Strategy

Sonu Mehta, Tomas Gudmundsson,  Dali Moghimi

## Project Description(Problem Statement)

The goal of the project is to find exit selections for evacuees in an emergency situation such that each person is directed to one of the nearest exits taking into account the congestion of the exit. To describe in detail, we start with a floor plan of a building. This plan is converted to a graph with nodes equal to the sum of number of persons and exits available. The graph is connected graph with edge weights representing the distance between two nodes. In case of an emergency evacuation, the goal is to assign each person their nearest exit but at the same time, taking into account there is no congestion at exits. Each exit has its own capacity to safely evacuate persons. The algorithm is expected to output the best or (near to best) assignment of evacuees to exits such that the cost is minimized. The cost , in this problem is defined as the sum of the distances of each person from their assigned exit and the penalty added for congestion at each exit.

## Algorithm

We start with an adjacent matrix of the graph representing the floor plan of a building. This graph is randomly generated connected weighted graph with few random nodes assigned as exits. For each exit, we use Dijkstra algorithm to find the shortest distances to each node(representing a person). Once we have the  distance to each exit for every person, we assign the nearest exit to each person and calculate the cost of the assignment. While calculating the cost,for now, we assume that the congestion can only be at exits and not at edges , i.e., any number of persons can pass through an edge at a given point of time. 

Once we have this assignment, we use simulated annealing to find the min. cost configuration. We start with a high temperature and each iteration, we generate a new configuration by changing the exit assignment of one the persons at random. If the new assignment has lower cost that the older assignment, we accept the configuration and if the cost is higher , we accept the new configuration with probability $= exp((newCost - oldCost))/T$ where $T$ is the temperature. We continue this for a certain number of iterations after which the temperature is reduced to $0.8T$. Ultimately the algorithm settles at the low-cost configuration.
## Parallel Implementation

The above algorithm is sequential and calculates the shorted distance using Dijkstra one by one. Since Dijkstra from one exit is not affected by another exit, we parallelize the algorithm by using openmp to calculate the shortest distance from all exits in parallel. This speeds up the process of calculation of shortest distance. Similarly, for simulated annealing, instead of starting with 1 initial configuration, we start with multiple initial configurations in  parallel and take the best solution at the end. 

![alt tag](https://raw.githubusercontent.com/CS205-Project/CS205-Spring2017-Projects/master/sequentialEvacuationTime.png)


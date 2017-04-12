// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

#include <stdio.h>
#include <limits.h>

// Number of vertices in the graph
#define V 8

void printgraph(int matrix[V][V])
{
    for(int i = 0; i< V; i++)
    {
        for(int j = 0; j< V; j++)
        {
            if(matrix[i][j] == INT_MAX)
            {
                printf("\t %s", "Inf");
            }
            else
            printf("\t %d", matrix[i][j]);
        }
        printf("\n");
    }
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], int sptSet[])
{
// Initialize min value
int min = INT_MAX, min_index;

for (int v = 0; v < V; v++)
	if (sptSet[v] == 0 && dist[v] <= min)
		min = dist[v], min_index = v;

return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int n)
{
printf("Vertex Distance from Source\n");
for (int i = 1; i <= V; i++)
    {
        if(dist[i-1] == INT_MAX)
            printf("%d \t\t %s\n", i, "Inf");
        else
            
        printf("%d \t\t %d\n", i, dist[i-1]);
    }
	
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph_org[V][V], int src, int exits[V])
{
    
    int graph[V][V];

    for (int i =0;i< V;i++)
    {
        for(int j = 0; j< V;j++)
       {
            if(  (exits[i] == 1 && i != src) ||  (exits[j] == 1 && j!=src))
            {
                
                graph[i][j] =INT_MAX;  
                
            }
            else
            {
                graph[i][j]=  graph_org[i][j];           
            }
       }
  
    }

    printgraph(graph);

	int dist[V];	 // The output array. dist[i] will hold the shortest
					// distance from src to i

	int sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
					// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = 0;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V-1; count++)
	{
	// Pick the minimum distance vertex from the set of vertices not
	// yet processed. u is always equal to src in first iteration.
	int u = minDistance(dist, sptSet);

	// Mark the picked vertex as processed
	sptSet[u] = 1;

	// Update dist value of the adjacent vertices of the picked vertex.
	for (int v = 0; v < V; v++)

		// Update dist[v] only if is not in sptSet, there is an edge from 
		// u to v, and total weight of path from src to v through u is 
		// smaller than current value of dist[v]
		if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && graph[u][v]!= INT_MAX
									&& dist[u]+graph[u][v] < dist[v]) {
			if (dist[u] == INT_MAX || graph[u][v] == INT_MAX)
			{
			    dist[v] = INT_MAX;
			} else
			{
			    dist[v] = dist[u] + graph[u][v];
			}
		
		}
	}

	// print the constructed distance array
	printSolution(dist, V);
}

// driver program to test above function
int main()
{
/* Let us create the example graph discussed above */
// int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
// 					{4, 0, 8, 0, 0, 0, 0, 11, 0},
// 					{0, 8, 0, 7, 0, 4, 0, 0, 2},
// 					{0, 0, 7, 0, 9, 14, 0, 0, 0},
// 					{0, 0, 0, 9, 0, 10, 0, 0, 0},
// 					{0, 0, 4, 14, 10, 0, 2, 0, 0},
// 					{0, 0, 0, 0, 0, 2, 0, 1, 6},
// 					{8, 11, 0, 0, 0, 0, 1, 0, 7},
// 					{0, 0, 2, 0, 0, 0, 6, 7, 0}
// 					};

/* Let us create the example graph discussed above */
int graph[V][V] = {{INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 4, INT_MAX, INT_MAX},
                   {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 6},
                   {INT_MAX, INT_MAX, INT_MAX, 6, 7, 3, INT_MAX, INT_MAX},
                   {INT_MAX, INT_MAX, 6, INT_MAX, 1, INT_MAX, INT_MAX, INT_MAX},
                   {INT_MAX, INT_MAX, 7, 1, INT_MAX, 2, INT_MAX, 7},
                   {4, INT_MAX, 3, INT_MAX, 2, INT_MAX, 5, INT_MAX},
                   {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 5, INT_MAX, INT_MAX},
                   {INT_MAX, 6, INT_MAX, INT_MAX, 7, INT_MAX, INT_MAX, INT_MAX}};


//int graph[V][V] = {{0,100,200,50}, {INT_MAX, 0,75,INT_MAX},{INT_MAX,INT_MAX,0,INT_MAX},{INT_MAX,45,85,0}};

    int exits[]={1,1,0,0,0,0,0,0};  
	dijkstra(graph, 0, exits);
//	dijkstra(graph, 1, exits);
	//dijkstra(graph, 1);

	return 0;
}

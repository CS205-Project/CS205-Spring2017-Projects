// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

// When everything seems to be going against you, remember that 
// the airplane takes off against the wind, not with it." -Henry Ford

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

// Number of vertices in the graph
#define V 15000

// Number of edges in the graph
#define NUME 75000

// Number of exits:
#define E 50

// Penalties:
#define HPENALTY 100
#define LPENALTY 2

#define PRINT 0

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


float calculate_cost(int exit_choices[V][E], int final_matrix[V][E], int exits[], int max_capacities[])
{

    if (PRINT) printf("\nIn cost fucntion; Exit choicex, final mat\n");
     for (int i = 0; i< V; i++)
    {
        for(int j = 0; j< E;j++)
            if (PRINT) printf("\t %d",exit_choices[i][j]);
        if (PRINT) printf("\n");
    }
   if (PRINT)  printf("\nIn cost fucntion; Exit choicex, final mat\n");
     for (int i = 0; i< V; i++)
    {
        for(int j = 0; j< E;j++)
            if (PRINT) printf("\t %d",final_matrix[i][j]);
        if (PRINT) printf("\n");
    }
    
    float cost = 0;
            //printf("\n %f", cost);
    for(int i =0 ;i< V; i++)
    {
        for(int j = 0; j< E; j++)
        {
            cost+= (exit_choices[i][j]* final_matrix[i][j]);
            //printf("\n %f", cost);
        }
            
    }

    int existing_capacities[E];
    
    for(int i = 0;i < E; i++)
    {
        existing_capacities[i] = 0;
    }
    for(int i  = 0; i< E; i++)
    {
    
        for (int j = 0; j< V; j++)
        {
            if(exits[j] ==0) 
            { 
                existing_capacities[i] +=exit_choices[j][i];
            }
        }
        
        if (PRINT) printf("\nExisting cap %d", existing_capacities[i]);
    }

    for(int i = 0; i< E;i++)
    {
        if(exits[i] == 1)
        {
            if(  (existing_capacities[i] - max_capacities[i]) > 0)
            {
                cost += (existing_capacities[i] - max_capacities[i]) * HPENALTY;
                
            }
            else
            {
                cost += LPENALTY/(max_capacities[i] - existing_capacities[i] + 0.1) ;
                                
            }
        }
    }
    return cost;

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
void dijkstra(int graph[V][V], int src, int exits[V], int final_matrix[V][E])
{
	// The output array. dist[i] will hold the shortest
	// distance from src to i

	int sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
					// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	int dist[V];
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
	for (int v = 0; v < V; v++) {
		// Don't look at other exit vertices:
		if (exits[v] == 1 && v != src) continue;		

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
	}
	// print the constructed distance array
	//printSolution(dist, V);
	
	for (int j =0 ;j< V;j++)
        {
            if (PRINT) printf(" %d ", src);
            final_matrix[j][src] = dist[j];
        }
}

// driver program to test above function
int main() {
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
	//int graph[V][V] = {{INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 4, INT_MAX, INT_MAX},
	//                   {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 6},
	//                   {INT_MAX, INT_MAX, INT_MAX, 6, 7, 3, INT_MAX, INT_MAX},
	//                   {INT_MAX, INT_MAX, 6, INT_MAX, 1, INT_MAX, INT_MAX, INT_MAX},
	//                   {INT_MAX, INT_MAX, 7, 1, INT_MAX, 2, INT_MAX, 7},
	//                   {4, INT_MAX, 3, INT_MAX, 2, INT_MAX, 5, INT_MAX},
	//                   {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 5, INT_MAX, INT_MAX},
	//                   {INT_MAX, 6, INT_MAX, INT_MAX, 7, INT_MAX, INT_MAX, INT_MAX}};
	//

	int graph[V][V];

	// Assign INT_MAX to all edges in adjacency graph:
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			graph[i][j] = i==j ? 0 : INT_MAX;
		}
	}

	//printgraph(graph);
     	char str[999];
     	FILE * file;
     	if (PRINT) printf("\n Graph \n");
     	file = fopen( "g.txt" , "r");
     
     	// Ignore first lines:
     	fscanf(file, "%s", str);
     	fscanf(file, "%s", str);

	int V1, V2, w;

	// Fill in adjacency matrix:     
     	for(int i = 0; i< NUME; i++) {
		// Read in V1, V2, w:
		fscanf(file, "%i", &V1);
		fscanf(file, "%i", &V2);
		fscanf(file, "%i", &w);

		// If weight of edge is less than any previous read weight update it:
		if (w < graph[V1-1][V2-1]) {
			graph[V1-1][V2-1] = w;
			graph[V2-1][V1-1] = w;
		}
     	}

	// Print matrix;
	//printgraph(graph);

	//int graph[V][V] = {{0,100,200,50}, {INT_MAX, 0,75,INT_MAX},
	//{INT_MAX,INT_MAX,0,INT_MAX},{INT_MAX,45,85,0}};
	//printgraph(graph);
    	
	int exits[V];
    	for (int i = 0; i< E; i++)
    		exits[i] = 1;
	
	int dist[V];
    	int final_matrix[V][E];
    	int exit_choices[V][E];
    	int max_capacities[E];
    
    	if (PRINT) printf("\nMax capacities\n");
    	for(int i = 0;i< E; i++) {
        	max_capacities[i] = ((V-E)*1.4)/E;
        	if (PRINT) printf("\t %d",max_capacities[i]);
    	}
    
    
    	for (int i = 0; i< V; i++) {
        	for(int j = 0; j< E;j++) {
            		final_matrix[i][j] = 0;
            		exit_choices[i][j] = 0;
        	}
   	 }
    
        struct timeval time_start;
	struct timeval time_end;
        long long execution_time;
	gettimeofday(&time_start, NULL);
  
  
   	#pragma omp parallel for
    	for(int i = 0; i< E; i++) {
        	dijkstra(graph, i, exits, final_matrix);
        
       	//  for (int j =0 ;j< V;j++)
	//         {
	//             printf(" %d ", i);
	//             final_matrix[j][i] = dist[j];
	//         
	//         }

        //printSolution(dist, V);
    	}
    
	gettimeofday(&time_end, NULL);

        execution_time = 1000000LL  * (time_end.tv_sec  - time_start.tv_sec) + (time_end.tv_usec - time_start.tv_usec);
       //printf("\n ENd %d %d", time_end.tv_sec, time_start.tv_sec);
		 printf("\nTime: %lld %llds\n", execution_time, execution_time/1000000);
	
	//     for (int i = 0; i< V; i++)
	//     {
	//         for(int j = 0; j< E;j++)
	//             printf("\t %d",final_matrix[i][j]);
	//         printf("\n");
	//     }
        
	
	for(int i = 0; i< V; i++){
		int min_dist = INT_MAX;
		int min_index  = 0;
		for(int j = 0;j< E; j++) {
	        	if(final_matrix[i][j]< min_dist) {
	            		min_dist = final_matrix[i][j];
	            		min_index = j;
	       	 	}
	    	}
	      	exit_choices[i][min_index] = 1;
	}
	
	
	// for (int i = 0; i< V; i++)
	//     {
	//         for(int j = 0; j< E;j++)
	//             printf("\t %d",exit_choices[i][j]);
	//         printf("\n");
	//     }
	//     
	float best_cost = calculate_cost(exit_choices, final_matrix, exits, max_capacities);    
		if (PRINT) printf("\nNew Cost %f\n",best_cost);
		
		
	float old_cost = best_cost;	
	
	// Simulated Annealing //
	int node, exit_r, old_index;
	float T = 100;
	float new_cost;
	
	for (int epoch = 0; epoch< 30; epoch++)
	{
	    for (int l = 0;l < 10;l++)
	    {
	        /* new slution*/
	        node  = rand() % 8 +2;
	        if (PRINT) printf("%d",node);
	        exit_r = rand() % 2;
	        if (PRINT) printf("%d",exit_r);
	
	
	        for (int i = 0; i< E; i++)
	        {
	            if(exit_choices[node][i] == 1)
	                {
	                old_index = i;
	                exit_choices[node][i] = 0;
	                break;
	                }
	        }
	        exit_choices[node][exit_r] = 1;
	        
	        new_cost = calculate_cost(exit_choices, final_matrix, exits, max_capacities);
	        
	        float prob = ((float)rand()/(float)(RAND_MAX)) * 1;
	        
	        if (PRINT) printf("\nNew Cost %f\n",new_cost);
	        //printf(" prob %f  \n" , exp( (old_cost-new_cost) /T));
	        if( new_cost < old_cost ||  prob < exp( (old_cost-new_cost) /T) )
	        {
	            if (PRINT) printf("\n New solution accepted");
	            old_cost = new_cost;
	            best_cost = new_cost;
	        }
	        
	        else
	        {
	            exit_choices[node][exit_r] = 0;
	            exit_choices[node][old_index] = 1;
	            if (PRINT) printf("\n New solution rejected");
	        }
	        
	    }
	    T = T *0.8;
	    
	}
	// Simulated Annealing ends here //

	printf("\n Best solutoin %f\n", best_cost);
	return 0;
}

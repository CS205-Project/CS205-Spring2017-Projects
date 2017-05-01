# include <stdlib.h>
# include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

# include "mpi.h"


// Number of vertices in the graph
#define V 15000

// Number of edges in the graph
#define NUME 75000

// Number of exits:
#define E 2

// Penalties:
#define HPENALTY 100
#define LPENALTY 2

#define PRINT 0

#define CORES 4

// variables used by all processes:
int exits[V];
int final_matrix[V][E];
int max_capacities[E];
int exit_choices[V][E];
float best_cost;
 int sender;

void printgraph(int matrix[V][V])
{
    int i,j;
    for( i = 0; i< V; i++)
    {
        for( j = 0; j< V; j++)
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
	int v;
	for ( v = 0; v < V; v++)
		if (sptSet[v] == 0 && dist[v] <= min)
			min = dist[v], min_index = v;
	
	return min_index;
}


float calculate_cost(int exit_choices[V][E], int final_matrix[V][E], int exits[], int max_capacities[])
{

    if (PRINT) printf("\nIn cost fucntion; Exit choicex, final mat\n");
    int i,j;
     for ( i = 0; i< V; i++)
    {
        for( j = 0; j< E;j++)
            if (PRINT) printf("\t %d",exit_choices[i][j]);
        if (PRINT) printf("\n");
    }
   if (PRINT)  printf("\nIn cost fucntion; Exit choicex, final mat\n");
     for ( i = 0; i< V; i++)
    {
        for( j = 0; j< E;j++)
            if (PRINT) printf("\t %d",final_matrix[i][j]);
        if (PRINT) printf("\n");
    }
    
    float cost = 0;
            //printf("\n %f", cost);
    for( i =0 ;i< V; i++)
    {
        for( j = 0; j< E; j++)
        {
            cost+= (exit_choices[i][j]* final_matrix[i][j]);
            //printf("\n %f", cost);
        }
            
    }

    int existing_capacities[E];
    
    for( i = 0;i < E; i++)
    {
        existing_capacities[i] = 0;
    }
    for( i  = 0; i< E; i++)
    {
    
        for ( j = 0; j< V; j++)
        {
            if(exits[j] ==0) 
            { 
                existing_capacities[i] +=exit_choices[j][i];
            }
        }
        
        if (PRINT) printf("\nExisting cap %d", existing_capacities[i]);
    }

    for( i = 0; i< E;i++)
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
	int i;
	printf("Vertex Distance from Source\n");
	for ( i = 1; i <= V; i++)
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
	int i, count,v ,j;
	for (i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = 0;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for ( count = 0; count < V-1; count++)
	{
	// Pick the minimum distance vertex from the set of vertices not
	// yet processed. u is always equal to src in first iteration.
	int u = minDistance(dist, sptSet);

	// Mark the picked vertex as processed
	sptSet[u] = 1;

	// Update dist value of the adjacent vertices of the picked vertex.
	for ( v = 0; v < V; v++) {
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
	
	for ( j =0 ;j< V;j++)
        {
            if (PRINT) printf(" %d ", src);
            final_matrix[j][src] = dist[j];
        }
}


int main ( int argc, char *argv[] );
void timestamp ( );

/******************************************************************************/

int main ( int argc, char *argv[] )

/******************************************************************************/

{
  MPI_Comm even_comm_id;
        struct timeval time_start;
  MPI_Group even_group_id;
  
  int i;
  int id;
  int ierr;
  int j;
 
  int p;
  MPI_Group world_group_id;
  double wtime;
/*
  Initialize MPI.
*/
  ierr = MPI_Init ( &argc, &argv );
/*
  Get the number of processes.
*/
  ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
/*
  Get the individual process ID.
*/
  ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );
/*
  Process 0 prints an introductory message.
*/
  if ( id == 0  ) 
  {
    //printf ( "COMMUNICATOR_MPI - Master process:\n" );
    printf ( "  The number of processes is %d.\n", p );
   // printf ( "\n" );
    timestamp ( );
    
    int graph[V][V];
    char str[999];
    FILE * file;
    int V1, V2, w;
    int i, j;
	// Assign INT_MAX to all edges in adjacency graph:
	for ( i = 0; i < V; i++) {
		for ( j = 0; j < V; j++) {
			graph[i][j] = i==j ? 0 : INT_MAX;
		}
	}

	//printgraph(graph);
     	
     	if (PRINT) printf("\n Graph \n");
     	file = fopen( "g15000.txt" , "r");
     
     	// Ignore first lines:
     	fscanf(file, "%s", str);
     	fscanf(file, "%s", str);

	

	// Fill in adjacency matrix:     
     	for( i = 0; i< NUME; i++) {
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


    	gettimeofday(&time_start, NULL);
  
	// Print matrix;
	//printgraph(graph);

	//int graph[V][V] = {{0,100,200,50}, {INT_MAX, 0,75,INT_MAX},
	//{INT_MAX,INT_MAX,0,INT_MAX},{INT_MAX,45,85,0}};
	//printgraph(graph);
    	
	
    for ( i = 0; i< E; i++)
    		exits[i] = 1;
	
	    int dist[V];
    
    	if (PRINT) printf("\nMax capacities\n");
    	for( i = 0;i< E; i++) {
        	max_capacities[i] = ((V-E)*1.4)/E;
        	if (PRINT) printf("\t %d",max_capacities[i]);
    	}
    
    
    	for ( i = 0; i< V; i++) {
        	for( j = 0; j< E;j++) {
            		final_matrix[i][j] = 0;
            		exit_choices[i][j] = 0;
        	}
   	 }
    

   	#pragma omp parallel for
    	for( i = 0; i< E; i++) 
    	{
        	dijkstra(graph, i, exits, final_matrix);
       
    	}
    

	for( i = 0; i< V; i++){
		int min_dist = INT_MAX;
		int min_index  = 0;
		for(j = 0;j< E; j++) {
	        	if(final_matrix[i][j]< min_dist) {
	            		min_dist = final_matrix[i][j];
	            		min_index = j;
	       	 	}
	    	}
	      	exit_choices[i][min_index] = 1;
	}


    	 best_cost = calculate_cost(exit_choices, final_matrix, exits, max_capacities);    
	 printf("\nInitial Cost %f\n",best_cost);
    	
        		
	
	// Simulated Annealing ends here //
  }

MPI_Bcast (exit_choices, V*E, MPI_INT, 0, MPI_COMM_WORLD);
MPI_Bcast (&best_cost, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
MPI_Bcast (final_matrix, V*E, MPI_INT, 0, MPI_COMM_WORLD);

MPI_Barrier(MPI_COMM_WORLD);
if(1)
{


int i,j;
//    float old_cost = best_cost;	
    float old_cost = best_cost;
    printf("\n Initial solution  in process %d , :%f\n",id, best_cost);
	timestamp ( );
	int node, exit_r, old_index, epoch,l, ii,jj;
    
    float T = 100;
	float new_cost, prob;
	int existing_capacities[E];
	
	for (epoch = 0; epoch< 5; epoch++)
	{
	    for (l = 0;l < 10;l++)
	    {
	        node  = (rand() + id) % V +E;
	        if(PRINT) printf(" %d ",node);
	        exit_r = (rand() + id)% E;
	       if(PRINT)  printf(" %d \n",exit_r);
	
	
	        for ( ii = 0; ii< E; ii++)
	        {
	            if(exit_choices[node][ii] == 1)
	                {
	                old_index = ii;
	                exit_choices[node][ii] = 0;
	                break;
	                }
	        }
	        exit_choices[node][exit_r] = 1;
	        
	        new_cost = calculate_cost(exit_choices, final_matrix, exits, max_capacities);
	        
        

	        prob = ((float)rand()/(float)(RAND_MAX)) * 1;

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
	    
	    float *costs = NULL;

        if (id == 0) {
          costs = malloc(sizeof(float) * CORES);
          
        }
        MPI_Gather(&best_cost, 1, MPI_FLOAT, costs, 1, MPI_FLOAT, 0,
                   MPI_COMM_WORLD);
                   
            sender =0;
         if (id == 0) 
         {
            printf("\n  Gathered costs %f, %f, %f, %f", costs[0], costs[1], costs[2],costs[3]);
            
            for( i =0 ; i< CORES; i++)
            {
                if(costs[i] < best_cost)
                {
                    best_cost = costs[i];
                    sender = i;

                }
        
            }
        // struct timeval time_end;
//         long long execution_time;    
//         printf("\n The best sender this time is %d", sender);
//         gettimeofday(&time_end, NULL);
//         execution_time = 1000000LL  * (time_end.tv_sec) + (time_end.tv_usec );
//         printf("\nTime: %lld \n", execution_time/1000000);

       

        }
         MPI_Bcast (&best_cost, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);    
         MPI_Bcast (&sender, 1, MPI_INT, 0, MPI_COMM_WORLD);    
         MPI_Bcast (exit_choices, V*E, MPI_INT, sender, MPI_COMM_WORLD);    
         MPI_Barrier(MPI_COMM_WORLD);
        printf("\n Best solution after transfer is %d->%d , :%f\n",sender,id, best_cost);
	    
	}

    printf("\n Best solution  in process %d , :%f\n",id, best_cost);
//     for(i = 0 ;i<V; i++)
//     {
//         for (j = 0; j< E;j++)
//         {
//             printf(" %d ", exit_choices[i][j]);
//         }
//         printf("\n");
//     }
    

}

/*
  Terminate MPI.
*/
  ierr = MPI_Finalize ( );
/*
  Terminate
*/


  if ( id == 0 )
  {
struct timeval time_end;
  gettimeofday(&time_end, NULL);


        long long execution_time;
  execution_time = 1000000LL  * (time_end.tv_sec  - time_start.tv_sec) + (time_end.tv_usec - time_start.tv_usec);

        // printf("\n ENd %d %d", time_end.tv_sec, time_start.tv_sec);



   // printf ( "\n" );
    printf ( "COMMUNICATOR_MPI:\n" );
    printf ( "  Normal end of execution.\n" );
    //printf ( "\n" );
    printf("=============================================================================================");
    printf("\nEXECUTION TIME: %lld %llds\n", execution_time, execution_time/1000000);
    timestamp ( );
  }
  return 0;
}
/******************************************************************************/

void timestamp ( void )

/******************************************************************************/

{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  size_t len;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  //fprintf ( stdout, "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}

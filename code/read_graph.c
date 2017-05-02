#include <stdio.h>
#include <limits.h>
#include <string.h>

int main()

{
    
    char str[999];
    FILE * file;
    int V,E;
    file = fopen( "hello.txt" , "r");
    if (file) {
        fscanf(file, "%s", str);
         V = atoi(str);
            printf("\n%d",V);
        fscanf(file, "%s", str);
        
        E = atoi(str);
            printf("\n%d\n",E);
        
        
    }
    
    int adjacency_matrix[V][V];
    for (int i = 0; i < V ;i++)
    {
        for(int j = 0; j< V; j++)
        {
            adjacency_matrix[i][j] = INT_MAX;    
        }
        
    }
    
    int a, b, w;
    for(int i =0; i<E; i++)
    {
        fscanf(file, "%s", str);
         a = atoi(str);
         fscanf(file, "%s", str);
         b = atoi(str);
         fscanf(file, "%s", str);
         w = atoi(str);
         adjacency_matrix[a-1][b-1] = w;
         adjacency_matrix[b-1][a-1] = w;
         
        
    }
    
    fclose(file);
    file = fopen( "hello_graph.txt" , "w");
    
    for (int i = 0; i < V ;i++)
    {
        for(int j = 0; j< V; j++)
        {
            if(adjacency_matrix[i][j] == INT_MAX)
            {
                printf("\tInf,");
                fprintf(file, "%s", " INT_MAX,");
            }
            else
            {
                printf("\t%d,",adjacency_matrix[i][j]);
                fprintf(file, " %d,", adjacency_matrix[i][j]);
            }
        }
        printf("\n");
        fprintf(file, "%s", "\n");
        
    }
    
    fclose(file);
    file = fopen( "hello_graph.txt" , "r");
    int new_matrix[V][V] ;
    for(int i = 0; i< V; i++)
    {
        for(int j = 0; j<V;j ++)
        {
            fscanf(file, "%s", str);
            if(strcmp("INT_MAX,", str)==0)
                {
                    printf("\t%s", str);
                    new_matrix[i][j] = INT_MAX;
                    
                
                }
            else
            {
                a = atoi(str);
                printf("\t%d, ",a);
                new_matrix[i][j] = a;    
            }
        }
        printf("\n");
    
    }
    
    
    
    
    
    
    
}
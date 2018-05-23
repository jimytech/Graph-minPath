//Version 16.05-2018
//Author: Jimy Santana
/*////////////////////////////////////////////////////////////////////
Function floydW
Parameters:           
dist: array 2D the distances with minimun cost
next: array 2D of the path with ....           
///////////////////////////////////////////////////////////////////*/
#include <stdlib.h>
#include <stdio.h>
#define INFINITY 9999

void floydW (Graph* graph, int** dist, int** next){ 
int i, j, k;
int aux_dist;
int numNodes = graph->V;

//Initialization of the matrix dist a INFINITY
for (i = 0; i<numNodes; i++){
    for (j = 0; j<numNodes; j++)
    {
        if (i==j)
           dist[i][j] = 0;
        else   
           dist[i][j] = INFINITY;
    }   
}    
//Initialization of the matrix of previous nodes
for (i = 0; i<numNodes; i++)
    for (j = 0; j<numNodes; j++)
           next[i][j] = -1;
//Assignment of the weights to the dist matrix and next         
for (i = 0; i<numNodes; i++){
   EdgeNodePtr pCrawl = graph->edges[i].head;
   if (pCrawl != NULL){
      do {
          dist[i][pCrawl->edge->to_vertex] = pCrawl->edge->weight; 
          next[i][pCrawl->edge->to_vertex] = i;
          pCrawl = pCrawl->next;
      }while(pCrawl != NULL);         
   }    
}       
//calculation of the minimum distances and minimum path 
for (k = 0; k<numNodes; k++)
   for (i = 0; i<numNodes; i++)
      for (j = 0; j<numNodes; j++)
      {
           aux_dist = dist[i][k] + dist[k][j];
           if (aux_dist<dist[i][j]){
               dist[i][j] = aux_dist;
               next[i][j] = next[k][j];                         
           }
      }
printf("\nEnergy floydW to node %d es %d \n", graph->V, dist[0][numNodes-1]);       
               
}//End function floydW

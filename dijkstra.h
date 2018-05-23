//Version 22.05-2018
//Author: Jimy Santana
/* For a given source node in the graph, the algorithm finds the shortest path between that node and
every other, it can also be used for finding the shortest paths from a single node to a single
destination node by stopping the algorithm once the shortest path to the destination node has
been determined.*/
#include <stdlib.h>
#include <stdio.h>
#define INFINITY 9999
#define UNDEFINED -1

void dijkstra(Graph* graph, int source, int* dist, int* pred){
  int i,j; //indice
  int n; //Num de vertices
  
  int count; //Num de vertices marcados
  int min_dist; //aux distacia minima de los vertices actuales
  int aux_v; //aux vertex
  int next_node; // nodo marcado
  n = graph->V;
  //Conjunto de vertices visitados
  int visited[n];
  //Inicializamos el array de vertices y distancia
  for (i=0; i<n; i++)
  {
    visited[i] = 0;
    dist[i] = INFINITY;
    pred[i] = source;
  }
  dist[source] = 0;//dist inicial del nodo fuente es 0
  count = 0;
  //Inicia la busqueda del camino más corto desde el vertice fuente
  while (count < n-1){
    min_dist = INFINITY;
    //next node is the node at min_dist
    for (i=0; i<n; i++)
      if (dist[i]<min_dist && !visited[i])
      {
          min_dist = dist[i];
          next_node = i;
      }
    //check if a better path exist through next_node
    visited[next_node] = 1;
    EdgeNodePtr pCrawl = graph->edges[next_node].head;
    while(pCrawl != NULL){
       // If shortest distance to v is not finalized yet, and distance to v
       // through u is less than its previously calculated distance
       if (!visited[pCrawl->edge->to_vertex])
          if (min_dist + pCrawl->edge->weight < dist[pCrawl->edge->to_vertex])
          {
              dist[pCrawl->edge->to_vertex] = min_dist+pCrawl->edge->weight;
              pred[pCrawl->edge->to_vertex] = next_node;
          }
       pCrawl = pCrawl->next;
    }//end while pCrael
    count++;
  }//while count

  printf("\n Energy dijkstra of node %d is = %d \n", n, dist[n-1]);
}//Fin dijkstra

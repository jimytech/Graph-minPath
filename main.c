//Version 1.2 22.05-2018
//Jimy Santana

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "dem.h"
#include "dijkstra.h"
#include "floydW.h"

//local functions prototype
void setNodesAdy (Graph*, int**, int, char);
void printPath (int, int, int**, int*);
void printPath2D (int, int, int**, int**);

int main() {

    int** DEM; //DEM Matrix
    int size; // size*size. Numbers of nodes. Part A.
    int source = 0; //source node
    int i;//index, key
    int V;//number of nodes
    char ch;
    do {
        printf ("\n Enter the value of size (and press Enter) ");
        printf ("\n The size should be one more than a power of 2 (e.g. 9, 17, 33, 65): ");
        scanf ("%d", &size); 
        printf ("\n Select option 'd' (dijktra), option 'f' (floyd-warshall: ");
        ch = getche ();              
        // create the graph 
        V = size*size;//number of nodes
        Graph* graph = createGraph(V);        
        switch(ch){

           case 'd':
               //Does the calculation of the DEM
               DEM = make_dem(size, size*9);
               //Converts it to an adjacency list using const_funcA
               setNodesAdy(graph, DEM, size, 'd');
               //calculates the shortest paths from vertex 0 (top left in the DEM)
               //reconstructs the path to the last vertex (bottom right in the DEM)
               int* dist = (int *) malloc(V*sizeof(int));//distance matrix
               int* prev = (int *) malloc(V*sizeof(int)); //previous node matrix
               source = 0;//vertex 0
               dijkstra(graph, source, dist, prev);
               //creates a copy of the DEM with the heights changed to -1 for 
               //any vertex on the path.
               //prints the DEM to show the path
               printPath (size, source, DEM, prev);
             break;
             case 'f':
               //converts it to an adjacency list using const_funcB
               setNodesAdy(graph, DEM, size, 'f');
               //calculates the shortest paths from vertex 0 (top left in the DEM)
               //reconstructs the path to the last vertex (bottom right in the DEM)
               int** next2D = malloc(V * sizeof *next2D); //Array2D of the path
               int ** dist2D = malloc(V * sizeof *dist2D); //Array2D minimum distances
               for (i = 0; i<V; i++){
                  dist2D[i] = malloc(V * sizeof *dist2D[i]);
                  next2D[i] = malloc(V * sizeof *next2D[i]);
               }
               floydW (graph, dist2D, next2D);
               //creates a copy of the DEM with the heights changed to -1 for 
               //any vertex on the path.
               //prints the DEM to show the path
               printPath2D (size, source, DEM, next2D);
             break;          
        } 
        printf("\n continue y/n ");
    }while ( getche() == 'y');   
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
//function that determines the adjacent nodes of the DEM to add them to the graph with its weight
//option = d, function calculated weight cost_funcA, else is funcB
///////////////////////////////////////////////////////////////////////////////////////////
  void  setNodesAdy (Graph *graph, int** DEM, int size, char option)
  {
    int i, j; 
    int weight;//Weight between two adjacent nodes
    for (i = 0; i <size; i++)
    {
      for (j=0; j<size-1; j++){
         //In the east-west direction
         if (option == 'd')
           weight = cost_funcA(DEM[i][j]-DEM[i][j+1]); //Weight between two adjacent nodes

         else  
           weight = cost_funcB(DEM[i][j]-DEM[i][j+1]);
         addEdge(graph, i*size+j, i*size+(j+1), weight);
         //In the direction West - East
         if (option == 'd')
            weight = cost_funcA(DEM[i][j+1]-DEM[i][j]); //weight of the arch of origin to the destination
         else 
            weight = cost_funcB(DEM[i][j+1]-DEM[i][j]);
         addEdge(graph, i*size+(j+1), i*size+j, weight);
         if (i<size-1) {
           //In the North-South direction
           if (option == 'd')
              weight = cost_funcA(DEM[i][j]-DEM[i+1][j]);
           else
              weight = cost_funcB(DEM[i][j]-DEM[i+1][j]);             
           addEdge(graph,i*size+j,(i+1)*size+j,weight);
           //In the South-North direction
           if (option == 'd')
              weight = cost_funcA(DEM[i+1][j]-DEM[i][j]);
           else
              weight = cost_funcB(DEM[i+1][j]-DEM[i][j]);   
           addEdge(graph,(i+1)*size+j,i*size+j,weight);
         }
      } //for interno j
      //The link in the last column is missing j = size-1 at the address N-S, S-N
      //j has the size-1 value when exiting the loop
      if(i!= size-1){
      //In the North-South direction
         if (option)
            weight = cost_funcA(DEM[i][j]-DEM[i+1][j]);
         else
            weight = cost_funcB(DEM[i][j]-DEM[i+1][j]);
      addEdge(graph,i*size+j,(i+1)*size+j,weight);
      //In the South-North direction
      if (option)
         weight = cost_funcA(DEM[i+1][j]-DEM[i][j]);
      else
         weight = cost_funcB(DEM[i+1][j]-DEM[i][j]);   
      addEdge(graph,(i+1)*size+j,i*size+j,weight);
    }
   } //for external i
  }//end of the function setNodosAdy
  
//////////////////////////////////////////////////////////////////////
//copy of the DEM with the heights changed to -1 for any vertex on the path
//Print the path on the DEM
///////////////////////////////////////////////////////////////////////
void printPath (int size, int source, int** D, int* prev)
{
    int prev_node = size*size-1; //End node;
    int i, j;
    
    int** D = malloc(size * sizeof *D);
    for (i = 0; i < size; i++) 
	 D[i] = malloc(size * sizeof *D[i]);
    for (i=0; i<size; i++)
      for (j=0; j<size; j++)
        D[i][j] = DEM[i][j];
    do {
      i = prev_node/size;
      j = prev_node%size;
      D[i][j] = -1;
      prev_node = prev[prev_node];
    } while (prev_node != source);
    //prev_node is the source
    i = prev_node/size;
    j = prev_node%size;
    D[i][j] = -1;
    print_2D_ascii(D, size);
    for (i = 0; i < size; i++) 
	free (D[i]);
    free (D);	
}//End printPath

//function printPath2D floyd-warshall
//creates a copy of the DEM with the heights changed to any vertex on the path.
//prints the DEM to show the path of node source = 0 at the last node V   
void printPath2D (int size,int source, int** D, int** next2D){
    int prev_node = size*size-1; //End node;
    int i, j;
    int** DEM;
    DEM = D;
    do {
      i = prev_node/size;
      j = prev_node%size;
      DEM[i][j] = -1;
      prev_node = next2D[source][prev_node];
    } while (prev_node != source);
    //prev_node is the source
    i = prev_node/size;
    j = prev_node%size;
    DEM[i][j] = -1;
    print_2D_ascii(DEM, size);
}//End function printPath2D           
/////////////////////////////////////////////////////////////////////
  
/* free all space used by graph */
  /*void graph_destroy(Graph* g)
    {
       int i;

       for(i = 0; i < g->n; i++) free( );
       free(g);
    }*/

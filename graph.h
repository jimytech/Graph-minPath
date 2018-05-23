//Version 16.05-5:00 PM
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)

#include <stdio.h>
#include <stdlib.h>

typedef struct edge{
  int to_vertex;
  int weight;
} Edge;
// A structure to represent an adjacency list node
typedef struct edgeNode {
    Edge *edge;
    struct edgeNode *next;
}*EdgeNodePtr;

typedef struct AdjList {
    EdgeNodePtr head; // pointer to head node of list
}EdgeList;

typedef struct graph {
    int V;
    EdgeList *edges;
}Graph;

// A utility function to create a new adjacency list node
EdgeNodePtr newAdjListNode(int dest, int weight) {
    EdgeNodePtr newNode = (EdgeNodePtr) malloc(
            sizeof(EdgeNodePtr));
    // Create an edge of adjacency lists.
    newNode->edge = (Edge*) malloc(sizeof(Edge));//
    newNode->edge->to_vertex = dest;
    newNode->edge->weight = weight; 
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of array will be V
    graph->edges = (EdgeList*) malloc(V * sizeof(EdgeList));

    // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->edges[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest,
             int weight) {
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    EdgeNodePtr newNode = newAdjListNode(dest, weight);
    newNode->next = graph->edges[src].head;
    graph->edges[src].head = newNode;

}

// A utility function to print the adjacenncy list representation of graph
void printGraph(Graph* graph) {
    int v;
    for (v = 0; v < graph->V; ++v) {
        EdgeNodePtr pCrawl = graph->edges[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->edge->to_vertex);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

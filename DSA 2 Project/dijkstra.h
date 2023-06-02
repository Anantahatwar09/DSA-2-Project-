#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "Heaps.h"

typedef struct PathNode *PathNode;                                                             

struct PathNode                                                                         // Struct to implement a linked list
{
    Vertex VertexID;                                                                    // Data stored in a node 
    PathNode NextNode;                                                                  // Pointer to the struct 
};

#define TIME_CONSTANT_AB 5                                                                 
#define TIME_CONSTANT_BE 2
#define PROPORTION_AB 80
#define PROPORTION_BE 50
#define VEHICLE_CONS_IN 5.7
#define VEHICLE_CONS_OUT 20.2
#define LOAD_FACTOR_IN 8.1
#define LOAD_FACTOR_OUT 1.2

int GetWeight(Graph G, Node Current, Node Destination, int time);                       // Finds the weight (time) of an edge using the given inputs
void dijkstra(Graph G, Vertex S, Vertex E, int time);                                   // Finds the path which takes the least time to travel from S to E  

// Prints the duration, estimated arrival time, distance and the path which takes the least time 
void PrintPath(Vertex S, Vertex E, int *time, int *Path, int start_time, float *distance);
int take_forshort(PathNode x, Vertex S, float* distance, int* time);

#endif

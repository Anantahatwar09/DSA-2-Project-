// An Efficient Graph ADT based on adjacency linked lists
// Used for implementing the map consisting of roads (Edges) and intersections (Vertices) 

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <stdio.h>                      // All header files added here
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <wchar.h>
#include <locale.h>

#define PRESENT 1
#define ABSENT 0

#define UNI_CROSSING_TIME 15;

typedef struct GraphInfo *Graph;
typedef struct NodeInfo *Node;
typedef int Vertex;

struct GraphInfo                            // Graph Structure  
{
    int NumVertex;                          // Number of Vertices in the graph
    int NumEdge;                            // Number of Edges in the graph
    Node *VertexList;                       // Adjacency List array
};

struct NodeInfo                             // Graph Node 
{
    // If node is a Vertex
    Vertex VertexID;                        // Vertex ID
    int NumHalls;                           // Number of Marriage Halls at that vertex
    int NumEdge;                            // Number of Outgoing Edges from the vertex    
    float IncTraff;                         // Total Incoming Traffic density at the vertex

    // If Node is an Edge
    int EdgeID;                             // Edge ID
    float traf_density;                     // Traffic density of the road
    float distance;                         // Length of the road
    int SpeedLim;                           // Speed Limit of the road

    // Pointer to Next node
    Node NextNode;                          // Pointer to the graph node, used in the adjacency linked list for a vertex
};

// Functions

Node MakeNode();                                                                                    // Allocate memory to the Graph Node and initialise it
Graph CreateGraph(int NumVertex);                                                                   // Allocate memory to the Graph structure and initialise it
void InsertEdge(Graph G, Vertex Start, Vertex End, float distance, int speed, float traf_density);  // Insert an Edge to the graph
void DeleteEdge(Graph G, Vertex u, Vertex v);                                                       // Delete an Edge from the graph
void PrintGraph(Graph G);                                                                           // Print Graph G in adjacency list form
int take_file(Graph t);

Graph getmap();                                                                                     // Generates map based on the dataset in graphinput.txt

#endif

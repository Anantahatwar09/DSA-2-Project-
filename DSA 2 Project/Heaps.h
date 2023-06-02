#ifndef HEAPS_H
#define HEAPS_H

#include "graph.h"

typedef struct MinHeap* MinHeap;
typedef struct HeapNode* HeapNode;

// Structure to store the MinHeap data
struct MinHeap {
    int size;               // Current size of MinHeap
    int capacity;           // Maximum capacity of MinHeap
    int* IDK;               // Array to store the position of each Key
    HeapNode* Array;        // Array to store the Key-Value pair
};

// Structure to store the Key-Value pair
struct HeapNode {
    Vertex VertexID;        // Stores the VertexID of the vertex
    int Weight;             // Stores the weight of to reach the vertex from source vertex 
};

HeapNode newMinHeapNode(Vertex To, int weight);
int IsEmpty(MinHeap PriorityQueue);
void SwapNode(HeapNode* a, HeapNode* b);
MinHeap BuildHeap(int V);
void DownHeap(MinHeap PriorityQueue, int in);
HeapNode ExtractMin(MinHeap PriorityQueue);
void RelaxEdge(MinHeap PriorityQueue, Vertex v, int weight);
int isInMinHeap(MinHeap PriorityQueue, int v);

#endif

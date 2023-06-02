#include "Heaps.h"

// Creates a new HeapNode and returns it's pointer
HeapNode newMinHeapNode(Vertex To, int weight)
{
	HeapNode MinHeapNode = (HeapNode)malloc(sizeof(struct HeapNode));       // Allocating memory to the HeapNode

	MinHeapNode->VertexID = To;                                             // Setting up the values
	MinHeapNode->Weight = weight;

	return MinHeapNode;                                                     // Returning the pointer to the HeapNode
}

// To check if the Priority Queue is empty or not
int IsEmpty(MinHeap PriorityQueue)
{
    if (PriorityQueue->size == 0)                                           
        return 1;
    else
        return 0;
}

// Swaps the position of two HeapNodes using their pointers during DownHeap
void SwapNode(HeapNode* a, HeapNode* b)
{
    HeapNode t = *a;                                                           // Temporary HeapNode to store 
    *a = *b;                                                                   // contents of one of the HeapNodes
    *b = t;                                                                    // to be swapped
}

// Builds a MinHeap of maximun capacity of V
MinHeap BuildHeap(int V)
{
    MinHeap PriorityQueue = (MinHeap)malloc(sizeof(struct MinHeap));

    PriorityQueue->size = 0;
    PriorityQueue->capacity = V;
    PriorityQueue->IDK = (int*)malloc(V*sizeof(int));                           // Allocationg memory to the position array
    PriorityQueue->Array = (HeapNode*)malloc(V*sizeof(struct HeapNode));        // Allocating memory to the HeapNode array (Priority Queue)

    return PriorityQueue;                                                       // Returning pointer to the MinHeap
}

// Heapify the MinHeap
void DownHeap(MinHeap PriorityQueue, int in)
{
    int smallest, left, right;

    smallest = in;
    left = (2*in) + 1;                                                           // index of left child
    right = (2*in) + 2;                                                          // index of right child
 
    // Checks the key of the smallest with the key of its left child
    if (left < PriorityQueue->size && PriorityQueue->Array[left]->Weight < PriorityQueue->Array[smallest]->Weight)
      smallest = left;    
    
    // Checks the key of the smallest with the key of its right child
    if (right < PriorityQueue->size && PriorityQueue->Array[right]->Weight < PriorityQueue->Array[smallest]->Weight)
      smallest = right;
 
    // if smallest is not the root node
    if (smallest != in)
    {
        // Gets the pointer to the HeapNodes to be swapped
        HeapNode smallestNode = PriorityQueue->Array[smallest];
        HeapNode inNode = PriorityQueue->Array[in];
 
        // Updates the position of vertex in the position array
        PriorityQueue->IDK[smallestNode->VertexID] = in;
        PriorityQueue->IDK[inNode->VertexID] = smallest;

        // Swaps the two HeapNodes
        SwapNode(&PriorityQueue->Array[smallest], &PriorityQueue->Array[in]);

        // Recursively heapify rest of the tree
        DownHeap(PriorityQueue, smallest);
    }
}

// Extracts the pointer to the HeapNode with minimum key value
HeapNode ExtractMin(MinHeap PriorityQueue)
{
    // Checks if Priority Queue is empty or not
    if (IsEmpty(PriorityQueue))
        return NULL;
    
    // Stores the pointer to root node as it contains the smallest key
    HeapNode Root_Node = PriorityQueue->Array[0];
 
    // Replace root node with last node
    HeapNode Last_Node = PriorityQueue->Array[PriorityQueue->size - 1];
    PriorityQueue->Array[0] = Last_Node;

    // Update position of root node and last node
    PriorityQueue->IDK[Root_Node->VertexID] = PriorityQueue->size - 1;
    PriorityQueue->IDK[Last_Node->VertexID] = 0;
 
    // Decreases the size of the Priority Queue and heapify it
    PriorityQueue->size -= 1;
    DownHeap(PriorityQueue, 0);
 
    // Returns the pointer to root node
    return Root_Node;
}

// Relaxes the edge weight if required
void RelaxEdge(MinHeap PriorityQueue, Vertex v, int weight)
{
    // Finds the position of the required vertex
    int i = PriorityQueue->IDK[v];
 
    // Update the weight of the vertex with new weight
    PriorityQueue->Array[i]->Weight = weight;
 
    // Heapify the Priority Queue at vertex i by moving upwards in the tree
    while (i && PriorityQueue->Array[i]->Weight < PriorityQueue->Array[(i - 1) / 2]->Weight)
    {
        PriorityQueue->IDK[PriorityQueue->Array[i]->VertexID] = (i-1)/2;

        PriorityQueue->IDK[PriorityQueue->Array[(i-1)/2]->VertexID] = i;

        SwapNode(&PriorityQueue->Array[i], &PriorityQueue->Array[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}

// Checks if the vertex is in the MinHeap or not
int isInMinHeap(MinHeap PriorityQueue, int v)
{
   if (PriorityQueue->IDK[v] < PriorityQueue->size)
    return 1;

   return 0;
}

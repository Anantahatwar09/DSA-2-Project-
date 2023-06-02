#include "dijkstra.h"
#include <math.h>
int GetWeight(Graph G, Node Current, Node Destination, int time)                   // Finds the weight (time) of an edge using the given inputs
{
    float weight;

    float LOAD_FCT;                                                                // Load factor is a constant that depends on time we are at the node
    if (time <= 22 * 60 && time >= 18 * 60)                                        // Load factor = LOAD_FACTOR_IN if it is in the interval of 6PM to 10PM
    {                                                                                 
        LOAD_FCT = LOAD_FACTOR_IN;
    }
    else                                                                           // Load factor = LOAD_FACTOR_OUT for any other time 
    {
        LOAD_FCT = LOAD_FACTOR_OUT;
    }

    int TIME_CST;                                                                  // Constant that denotes estimated time to cross the road
    int PROP_CST;                                                                  // Constant that denotes fraction of total incoming traffic entering the node                                                                  
    if (G->VertexList[Destination->VertexID]->IncTraff > 40)                       // If the total incoming traffic density for a node is greater than 40, 
    {                                                                               
        TIME_CST = TIME_CONSTANT_AB;                                               // The values of time and proportionality constant change accordingly
        PROP_CST = PROPORTION_AB;
    }
    else
    {
        TIME_CST = TIME_CONSTANT_BE;
        PROP_CST = PROPORTION_BE;
    }
    
    float VEHICLE_CST;                                                              // Constant to denote estimated traffic density due to marriage
    if (Destination->traf_density > 70)                                             // If the traffic density for an edge is greater than 70, 
    {
        VEHICLE_CST = VEHICLE_CONS_OUT;                                             // The value of vehicle constant changes accordingly
    }
    else
    {
        VEHICLE_CST = VEHICLE_CONS_IN;
    }

    // Calculating the weight according to the formula
    // Here k = 0.01 which is a constant accounting to the marriage processions 
    float Traf_New = (Destination->traf_density) + (VEHICLE_CST * LOAD_FCT) * (((float)Current->NumHalls) / ((float)Current->NumEdge) + 0.01);
    weight = ((Destination->distance) * (Traf_New)) / ((Destination->SpeedLim) * (Destination->traf_density));
    weight = weight * 60;
    weight += (TIME_CST) * ((G->VertexList[Destination->VertexID]->IncTraff) / PROP_CST);

    return weight+1;                                                            // Returns the weight in terms of minutes 
}

void dijkstra(Graph G, Vertex S, Vertex E, int start_time)                          // Finds the path which takes the least time to travel from S to E 
{
    int V = G->NumVertex;                                                           // Number of nodes or intersections 

    MinHeap PriorityQueue = BuildHeap(V);                                           // Creates a min heap of size V

    int time[V];
    float distance[V];
    for (int i = 0; i < V; ++i)                                                     // Assigning the time and distance for each vertex as infinity initially
    {
        time[i] = INT_MAX;
        distance[i] = INT_MAX;
    }

    for (int i = 0; i < V; ++i)
    {
        PriorityQueue->Array[i] = newMinHeapNode(i, time[i]);                       // Initialize min heap with all nodes, time values of all vertices
        PriorityQueue->IDK[i] = i;                                                  
    }

    Vertex Path[V];
    for (int i = 0; i < V; ++i)
    {
        Path[i] = i;
    }

    PriorityQueue->Array[S] = newMinHeapNode(S, time[S]);
    PriorityQueue->IDK[S] = S;
    time[S] = 0;                                                                    // Making time of source vertex as 0 so that it is extracted first
    RelaxEdge(PriorityQueue, S, time[S]);                                           // Function to decrease the time value of a given vertex S. 
 
    PriorityQueue->size = V;                                                        // Size of priority queue is equal to the number of vertices 
                                                                                    // The min heap now contains all nodes whose minimum time is not yet finalized
    while (!(IsEmpty(PriorityQueue)))
    {
        HeapNode Current = ExtractMin(PriorityQueue);                                // Extracts the vertex with minimum time value

        Vertex CurrentID = Current->VertexID;                                        // Stores the VertexID of the extracted vertex
        float CurrentWeight = Current->Weight;                                       // Stores the weight of the extracted vertex 

        Node temp = G->VertexList[CurrentID]->NextNode;
        while (temp != NULL)                                                         // Traversing through the adjacent vertices of the extracted vertex
        {                                                                            
            int time_travel = time[CurrentID] + start_time;                          
            int temp_weight = GetWeight(G, G->VertexList[CurrentID], temp, time_travel);
            Vertex Destination = temp->VertexID;
            
            // Updating the time values of the adjacent vertices if it's not finalised yet and if it's less than the previously calculated value
            if (isInMinHeap(PriorityQueue, Destination) && time[CurrentID] != INT_MAX && temp_weight + time[CurrentID] < time[Destination])
            {

                Path[Destination] = CurrentID;
                distance[Destination] = temp->distance;
                time[Destination] = time[CurrentID] + temp_weight;

                RelaxEdge(PriorityQueue, Destination, time[Destination]);            // Updating the new value in the minheap 
            }

            temp = temp->NextNode;
        }

        if (CurrentID == E)                                                          // Break from the loop if the vertex with minimum time value is end vertex
            break;
    }

    PrintPath(S, E, time, Path, start_time, distance);                               // Prints the path which takes the least time to travel
}

void PrintPath(Vertex S, Vertex E, int *time, int *Path, int start_time, float *distance)
{
    printf("Estimated Travel Duration: %d mins\n", time[E]);                         // Prints the time taken for the travel 

    int H = (start_time + time[E]) / 60;
    int M = (start_time + time[E]) % 60;

    printf("Estimated Arrival Time: %2d:%2d\n", H, M);                               // Prints the estimated time of arrival based on the duration 

    PathNode NewPath = (PathNode)malloc(sizeof(struct PathNode));                    
    NewPath->VertexID = S;
    NewPath->NextNode = NULL;             

    Vertex in = E;
    while (in != S)                                                                  // Reversing the linked list to print it in the correct order
    {
        PathNode temp = (PathNode)malloc(sizeof(struct PathNode));

        temp->VertexID = in;
        temp->NextNode = NewPath->NextNode;
        NewPath->NextNode = temp;

        in = Path[in];                                                                
    }
    take_forshort(NewPath, S, distance, time);
    printf("%d ", S);
    int CurrentTime = 0;
    PathNode temp = NewPath->NextNode;
    float total_distance = 0;

    while (temp != NULL)                                                            // Traversing the linked list to find the distance to be travelled 
    {
        total_distance += distance[temp->VertexID];
                                                                                    // Prints the time takes to travel from one node to another 
        printf("-- %d mins --> %d ", time[temp->VertexID] - CurrentTime, temp->VertexID);
        CurrentTime = time[temp->VertexID];
        temp = temp->NextNode;
    }

    printf("\nTotal Distance to be travelled: %g Km\n", total_distance);            // Prints the total distance of the path which takes the least time
}

int take_forshort(PathNode x, Vertex S, float* distance, int* time){
    FILE* file = fopen("shortpath.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.");
        return 1;
    }
    int mid = S;
    PathNode temp = x->NextNode;
    float dis = 0;
    int curr_time = 0;
    int total_time = 0;
    float total_distance = 0;
    while(temp){
        fprintf(file ,"%i ", mid);
        dis = distance[temp->VertexID];
        fprintf(file, "%i\n", temp->VertexID);
         fprintf(file, "%f ",dis);
         fprintf(file, "%i\n",time[temp->VertexID] - curr_time);

        curr_time = time[temp->VertexID];
        total_distance += dis;
        mid = temp->VertexID;
        temp = temp->NextNode;
    } 
     fprintf(file, "\n%i ", curr_time);
     fprintf(file, "%g", total_distance);
    fclose(file);
    return 0;
}

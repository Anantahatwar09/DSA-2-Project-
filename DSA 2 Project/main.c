#include <stdio.h>
#include <time.h>
#include "graph.h"
#include "Heaps.h"
#include "dijkstra.h"

int main()
{
    setlocale(LC_ALL, "en_US.utf8"); // Just an emoji :D

    Graph G = getmap(); // Generates map based on the dataset in graphinput.txt

    printf("Operation Codes:\n");
    printf("0. Exit\n");               // Exit from the program
    printf("1. Find Shortest Path\n"); // Find Shortest Path using Dijkstra's Algorithm
    printf("2. Add Edge\n");           // Add Edge to the graph (a road on the map)
    printf("3. Delete Edge\n");        // Remove an Edge from the graph
    printf("4. Print Graph\n");        // Display the graph/map
    printf("5. Get Weight\n");         // Display the weightage(time taken) between 2 nodes

    printf("\n");

    int Operation;
    printf("Operation Code: ");
    scanf("%d", &Operation);

    while (Operation != 0) // Exits if Operation = 0
    {
        if (Operation == 1) // Find Shortest Path
        {
            Vertex S, E;
            time_t current_time;
            struct tm *time_info;
            int H, M;

            printf("Enter Starting Vertex: "); // Taking Inputs
            scanf("%d", &S);
            printf("Enter Destination Vertex: ");
            scanf("%d", &E);

            // Get current time
            current_time = time(NULL);
            time_info = localtime(&current_time);

            H = time_info->tm_hour;
            M = time_info->tm_min;

            int time = (H * 60) + M; // Converts time from hours and minutes to just minutes

            printf("\n");
            if (S >= G->NumVertex || S < 0) // Source Vertex id is greater than the maximum vertex id of the graph, i.e. the source does not exist
            {
                printf("Vertex %d does not exist!!\n", S);
            }

            if (E >= G->NumVertex || E < 0)
            {
                printf("Vertex %d does not exist!!\n", E); // Destination Vertex id is greater than the maximum vertex id of the graph, i.e. the destination does not exist
            }

            if (S < G->NumVertex && S >= 0 && E < G->NumVertex && E >= 0)
            {
                dijkstra(G, S, E, time); // Calling Dijkstra function to calculate and display the shortest path from source to destination vertex
            }
        }
        else if (Operation == 2) // Add Edge
        {
            int S, E;
            float distance, traf_density;
            int speed;

            printf("Enter Starting Vertex: ");
            scanf("%d", &S);
            printf("Enter Destination Vertex: "); // Taking Inputs
            scanf("%d", &E);
            printf("Enter length of the road (Km): ");
            scanf("%f", &distance);
            printf("Enter speed limit of the road (Km/hr): ");
            scanf("%d", &speed);
            printf("Enter traffic density of the road: ");
            scanf("%f", &traf_density);

            printf("\n");
            if (S >= G->NumVertex || S < 0) // Source Vertex id is greater than the maximum vertex id of the graph, i.e. the source does not exist
            {
                printf("Vertex %d does not exists!!\n", S);
            }

            if (E >= G->NumVertex || E < 0)
            {
                printf("Vertex %d does not exists!!\n", E); // Destination Vertex id is greater than the maximum vertex id of the graph, i.e. the destination does not exist
            }

            if (S < G->NumVertex && S >= 0 && E < G->NumVertex && E >= 0)
            {
                InsertEdge(G, S, E, distance, speed, traf_density); // Calling the InsertEdge function to insert an edge node into the graph/map
                printf("Done!!\n");
            }
        }
        else if (Operation == 3) // Delete Edge
        {
            Vertex S, E;
            printf("Enter Starting Vertex: "); // Taking Inputs
            scanf("%d", &S);
            printf("Enter Destination Vertex: ");
            scanf("%d", &E);

            printf("\n");
            if (S >= G->NumVertex || S < 0) // Source Vertex id is greater than the maximum vertex id of the graph, i.e. the source does not exist
            {
                printf("Vertex %d does not exists!!\n", S);
            }

            if (E >= G->NumVertex || E < 0) // Destination Vertex id is greater than the maximum vertex id of the graph, i.e. the destination does not exist
            {
                printf("Vertex %d does not exists!!\n", E);
            }

            if (S < G->NumVertex && S >= 0 && E < G->NumVertex && E >= 0)
            {
                DeleteEdge(G, S, E); // Calling the DeleteEdge function to delete an edge node from the graph/map
            }
        }
        else if (Operation == 4) // Print Graph
        {
            printf("\n");
            PrintGraph(G); // Calling the PrintGraph function to print the graph G in adjacency list form
        }
        else if (Operation == 5) // Get weight
        {
            Vertex S, E;
            int H, M;

            printf("Enter Starting Vertex: "); // Taking Inputs
            scanf("%d", &S);
            printf("Enter Destination Vertex: ");
            scanf("%d", &E);
            printf("Enter time of travel (HH:MM): ");
            scanf("%d:%d", &H, &M);

            int time = (H * 60) + M;

            if (S >= G->NumVertex || S < 0) // Source Vertex id is greater than the maximum vertex id of the graph, i.e. the source does not exist
            {
                printf("Vertex %d does not exists!!\n", S);
            }

            if (E >= G->NumVertex || E < 0)
            {
                printf("Vertex %d does not exists!!\n", E); // Destination Vertex id is greater than the maximum vertex id of the graph, i.e. the destination does not exist
            }

            if (S < G->NumVertex && S >= 0 && E < G->NumVertex && E >= 0)
            {
                Node temp = G->VertexList[S]->NextNode; // Pointer to the adjacency list for vertex S (source vertex)
                while (temp != NULL)                    // Traversing through the list
                {
                    if (temp->VertexID == E) // If the vertex id in the adjacency list of source vertex matches the destination vertex
                        break;               // That means an edge from S to E is found

                    temp = temp->NextNode;
                }

                if (temp != NULL) // If edge is found temp != NULL
                {
                    float weight = GetWeight(G, G->VertexList[S], temp, time);
                    printf("%g mins\n", weight); // Calling the GetWeight function to calculate the weight of that edge
                }
                else if (temp == NULL) // If edge doesn't exist, temp == NULL
                {
                    printf("No such road exists!!\n");
                }
            }
        }

        printf("\n"); // Continuing the program execution
        printf("Operation Code: ");
        scanf("%d", &Operation);
    }

    take_file(G);
    printf("\n");
    printf("Thank you for using our program %lc\n", 0x1F603); // This is the emoji :D

    return 0;
}

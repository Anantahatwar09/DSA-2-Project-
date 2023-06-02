#include "graph.h"

Graph CreateGraph(int NumVertex)                                                                    // Allocate memory to the Graph structure and initialise it
{
    Graph G;
    G = (Graph)malloc(sizeof(struct GraphInfo));                                                    // Allocated memory to Graph G
    assert(G != NULL);                                      

    G->NumVertex = NumVertex;                                                                       // Initialising values
    G->NumEdge = 0;

    G->VertexList = (Node *)malloc(NumVertex * sizeof(Node));                                       // Allocating memory to the nodes of the adjacency linked list array
    assert(G->VertexList != NULL);

    for (int i = 0; i < NumVertex; ++i)                                                             // For each element of adjacency linked list array,
    {
        G->VertexList[i] = (Node)malloc(sizeof(struct NodeInfo));                                   // Allocating memory to each node of the array
        assert(G->VertexList[i] != NULL);

        if (i < NumVertex)                                                                          // The vertex ID of the array element is lesser than the maximum vertex IS of the graph
            G->VertexList[i]->VertexID = i;                                                         // i.e. it exists in the graph
        else
            G->VertexList[i]->VertexID = -1;                                                        // The vertex ID does not exist in the graph

        G->VertexList[i]->NumHalls = 0;                                                             // Initialising the rest of the values of each array node of the adjacency list
        G->VertexList[i]->NumEdge = 0;
        G->VertexList[i]->IncTraff = 0;

        G->VertexList[i]->EdgeID = -1;
        G->VertexList[i]->traf_density = 0;
        G->VertexList[i]->distance = 0;
        G->VertexList[i]->SpeedLim = 0;

        G->VertexList[i]->NextNode = NULL;                                                          // The next pointer of all array nodes of the adjacency list array point to NULL, i.e. No adjacent vertices as of now
    }

    return G;
}

Node MakeNode()                                                                                     // Allocate memory to the Graph Node and initialise it
{
    Node N = (Node)malloc(sizeof(struct NodeInfo));                                                 // Allocate memory to the Vertex Node of the graph
    assert(N != NULL);

    N->NumHalls = 0;                                                                                // Initialising values of the Vertex Node
    N->NumEdge = 0;

    N->NextNode = NULL;

    return N;
}

void InsertEdge(Graph G, Vertex Start, Vertex End, float distance, int speed, float traf_density)   // Insert an Edge to the graph
{
    G->NumEdge += 1;                                                                                // Incrementing total edges present in the Graph

    Node N = MakeNode();                                                                            // Allocating memory to the edge node

    N->VertexID = End;                                                                              // Storing the values of the edge into the edge node
    N->EdgeID = G->NumEdge;
    N->distance = distance;
    N->traf_density = traf_density;
    N->SpeedLim = speed;

    Node Temp = G->VertexList[Start]->NextNode;                                                     // Linking the edge node to the vertex in the adjacency list at the front of the list
    N->NextNode = Temp;
    G->VertexList[Start]->NextNode = N;

    G->VertexList[Start]->NumEdge += 1;                                                             // Number of outgoing edges from Start Vertex is incremented 

    G->VertexList[End]->IncTraff += traf_density;                                                   // The traffic density of the edge is added to the incoming traffic density at the End vertex
}

void DeleteEdge(Graph G, Vertex u, Vertex v)                                                        // Delete an Edge from the graph
{
    Node temp = G->VertexList[u];                                                                   // Pointer to the adjacency list of the Source Vertex (u)

    while (temp->NextNode != NULL)                                                                  // Traversing through the list
    {
        if (temp->NextNode->VertexID == v)                                                          // The vertex v (destination vertex) is in the adjacency list of u
        {                                                                                           // Edge exists from u to v
            Node N = temp->NextNode->NextNode;                                                      // Removing the edge
            free(temp->NextNode);                                                                   // Freeing its memory
            temp->NextNode = N;

            break;
        }

        temp = temp->NextNode;
    }
}

Graph getmap()                                                                                      // Generates map based on the dataset in graphinput.txt
{
    int V;                                                                                          // V = Total number of Vertices in the graph
    int E;                                                                                          // E = Total number of Edges in the graph 
    FILE *fp = fopen("graphinput.txt", "r");                                                        // Opens the file graphinput.txt to read data from it
    fscanf(fp, "%d", &V); 

    Graph G = CreateGraph(V);                                                                       // Allocate memory to the Graph structure with V vertices and initialise it

    int NumHalls;                                                                                   // Number of Marriage halls
    for (int i = 0; i < V; ++i)
    {
        fscanf(fp, "%d", &NumHalls);                                                                // Scanning V space separated integers which are the number of halls at their respective vertex ID from 0 to V-1
        G->VertexList[i]->NumHalls = NumHalls;                                                      // Storing the scanned value into the Vertex Data
    }

    fscanf(fp, "%d", &E);

    int Start, End;                                                                                 // Start and end vertex of an edge
    float distance, traf_density;                                                                   // Length of the road and its traffic density
    int speed;                                                                                      // Speed Limit of the Road/edge

    for (int i = 0; i < E; ++i)                                                                     
    {

        fscanf(fp, "%d %d", &Start, &End);                                                          // Scanning 2 space separated integers, Start and End vertices
        fscanf(fp, "%f %d %f", &distance, &speed, &traf_density);                                   // Scanning 3 space separated values of distance , speed limit and traffic density                           

        InsertEdge(G, Start, End, distance, speed, traf_density);                                   // Inserting an edge with those values to the graph
    }

    return G;
}

void PrintGraph(Graph G)                                                                            // Print Graph G in adjacency list form
{
    Node temp;
    for (int i = 0; i < G->NumVertex; ++i)                                                          // For each vertex id of the vertices in the graph
    {
        temp = G->VertexList[i]->NextNode;                                                          // Pointer to the adjacency list of the graph for the vertex ID i

        printf("%d --> {", G->VertexList[i]->VertexID);                                             // Printing the vertex ID

        while (temp != NULL)                                                                        // Traversing through the linked list
        {
            printf(" %d", temp->VertexID);                                                          // Printing the Vertex ID of the vertices adjacent to the vertex ID i
            temp = temp->NextNode;
        }

        printf("}\n");
    }
}

int take_file(Graph t){
    FILE* file = fopen("graph_data.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.");
        return 1;
    }
    Node temp = NULL;
    for(int i=0; i<t->NumVertex; i++){
        temp = t->VertexList[i];
        while(temp){
            fprintf(file, "%i ", temp->VertexID);
            temp = temp->NextNode;
        }
        fprintf(file, "%s", "\n");
        
    }
    fclose(file); 
    return 0;
}

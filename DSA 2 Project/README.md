# Routing - Mini Project

## Objective
---
   Implemented Dijkstra's algorithm in C to traverse the shortest path on a custom map with revised weights to consider indeterminable events during execution.


## Calculating weightages
---
### Dataset Provided:

     1. Intersections (nodes)
     2. Roads (edges)
     3. Length of the road
     4. Traffic Density/Flow
     5. Marraige Season - depicts the presence of function halls 
     6. Speed limits

### User Input Data:
    To find quickest path
     1. Start(vertex ID -integer)
     2. Destination(vertex ID -integer)
     3. Time(24-hour format -HH:MM)
     
    To find weight of an edge
     1. Start(vertex ID -integer)
     2. Destination(vertex ID -integer)
     3. Time(24-hour format -HH:MM)
     
    To add a new edge
     1. Start(vertex ID -integer)
     2. Destination(vertex ID -integer)
     3. Length of the road (km -float)
     4. Speed limit (kmph -integer)
     5. Traffic Density/Flow (number of cars per kilometer -float)
     
    To delete an edge
     1. Start(vertex ID -integer)
     2. Destination(vertex ID -integer)

### Graphinput Text File format:

- The first line contains an integer |V| denoting the number of intersection(nodes). The ID of each intersection is between 0 and |V| - 1.
- The next line contains |V| space seperated integers denoting the number of function halls at each node (0 in case there are none).
- The next line contains an integer |E| denoting the number of roads(edges). 
- The next |E| lines contains the following data for each edge:
   - The first line of each set contains 2 space seperated integers denoting the start and end vertices of the road.
   - The next line contains 3 space seperated values denoting the length (in kilometers), the speed limit (in kmph) and the traffic density (number of cars per kilometer) of the given road.


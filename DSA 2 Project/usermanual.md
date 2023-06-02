# Instructions for compilation 
```

```
# How to run the testcases 

After compiling, a set of operations list appears which prompts you to enter an operation code of your choice. 

On choosing an operation code:

## 0 - Exit 
```
This operation exits the program. 
```
## 1 - Find the shortest path
```
This operation is used to find the shortest path from the start to the end vertex. 

INPUT:
The following information must be entered:

a)The starting vertex:
  - This is the starting point of the travel from where you'd like to begin. Enter an integer ranging from 0 to 19. 
b)The destination vertex:
  - This is the final destination of the travel where you'd like to end. Enter an integer ranging from 0 to 19. 
c)Time of travel:
  - Enter the time at which you begin your journey from the starting point in 24 hour format (ie hours:minutes).

OUTPUT:

```
## 2 - Add egde
```
This operation is used to add an edge to the graph. 

INPUT:
The following information must be entered:

a)Starting Vertex:
  - Enter the starting point of the edge to be added. 
b)Destination Vertex:
  - Enter the end point of the edge to be added. 
c)Distance:
  - Enter the length of the edge/road in kilometers. 
d)Speed limit:
  - Enter the speed limit of the road in kmph. 
e)Traffic density:
  - Enter the traffic density of the road(number of cars per km).
  
OUTPUT:
- Prints "Done" once the edge has been successfully added. 
```
## 3 - Delete edge
```
This operation is used to delete an edge from the graph. 

INPUT:
The following information must be entered:

a)Starting Vertex:
  - Enter the starting point of the edge to be deleted. 
b)Destination Vertex:
  - Enter the end point of the edge to be deleted.
  - 
OUTPUT:
 - Prints "Done" once the edge has been successfully deleted. 
```
## 4 - Print Graph 
```
This operation prints the graph using adjacency list implementation. 
  For example 1->{2,3,5}, means 1 is the starting vertex and 2,3,5 are three different end vertices containing an edge starting from 1. 
```
## 5 - Get weight 

#include <stdio.h>
#include "common.h"
#define INFINITY 999
#define VERTEX 4
#define EDGES 16
//Create an edge structure 
struct Edge {
	int src, dest, weight;
};
//Bellman Ford algorithm partially taken from https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
//Graph is not directional therefore there cannot be any negative cycles, every edge is also counted twice for example (0, 1) and (1, 0) 
//A matrix to store content to be printed
int matrix[4][4] = {0};
int bellman(struct distance_table *dataptr, int source, int *buf) {
	int v = VERTEX;
	int e = EDGES;
	//Create a list of edges
	struct Edge edge[e];
	//Fill the list of edges with values from matrix
	int index = 0;
	for(int i = 0;i < VERTEX;i++) {
		for(int j = 0;j < VERTEX;j++) {
			edge[index].src = j;
			edge[index].dest = i;
			edge[index].weight = dataptr->costs[i][j];
			index++;
		}
	}	
	//Array for minimum distances
	int dist[VERTEX];
	//Initialize list to 999
	for(int i = 0;i < VERTEX;i++)
		dist[i] = INFINITY;
	//Set source distance to 0
	dist[source] = 0;
	//Bellman Ford algorithm, finds shortest path from source to destination	
	for(int i = 1;i <= VERTEX-1;i++) {
		for(int j = 0;j < EDGES; j++) {
			int u = edge[j].src;
			int v = edge[j].dest;
			int weight = edge[j].weight;
			if(dist[u] != INFINITY && (dist[u] + weight) < dist[v])
				dist[v] = dist[u] + weight;
		}	
	}
	//Fill the provided buffer
	//Change = 1 if the values in buffer changed
	int change = 0;
	for(int i = 0;i < VERTEX;i++)
		if(buf[i] != dist[i]) {
			buf[i] = dist[i];
			matrix[i][source] = dist[i];
			change = 1;
		}
	//Prints the shortest path matrix
	printf("Shortest Path matrix\n");
	printf("   0  1  2  3\n");
	printf("-------------\n");
	for(int i = 0;i < VERTEX;i++) {
		printf("%d| ", i);
		for(int j = 0;j < VERTEX;j++) 
			printf("%d  ", matrix[i][j]);
		printf("\n");
		}	
	return change;
}


#include <stdio.h>
#include "common.h"
#include "sim_engine.h"
extern int TRACE;
extern int YES;
extern int NO;
//A buffer to store the minimum distances 
int buf0[4] = {0};
//Create a global distance table (matrix)
struct distance_table dt0;
//I dont understand this print function
void printdt0(struct distance_table *dtptr) {
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
  
}
/* Students to write the following two routines, and maybe some others */
void rtinit0() {
	//Set all values in matrix to 999
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			dt0.costs[i][j] = 999;
	//Change values to the ones from the graph
	dt0.costs[0][0] = 0;
	dt0.costs[1][0] = 1;
	dt0.costs[2][0] = 3;
	dt0.costs[3][0] = 7;
	//Create packets to send to neighbors	
	struct rtpkt packet1, packet2, packet3;
	//Set values in packets
	packet1.sourceid = 0;
	packet1.destid = 1;
	for(int x = 0; x < 4; x++) {
		packet1.mincost[x] = dt0.costs[x][0];	
		packet2.mincost[x] = dt0.costs[x][0];	
		packet3.mincost[x] = dt0.costs[x][0];	
	}
	packet2 = packet1;
	packet3 = packet1;
	packet2.destid = 2;
	packet3.destid = 3;
	tolayer2(packet1);
	tolayer2(packet2);
	tolayer2(packet3);
	printdt0(&dt0);
}

void rtupdate0(struct rtpkt *rcvdpkt) {
	//Update the matrix with new mincosts recieved from packet
	for(int i = 0;i < 4;i++)
		dt0.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i];
	//Run bellman ford algorithm
	int change = bellman(&dt0, 0, buf0);
	//If values changed create new packages and transmit to neighbors
	if(change == 1) {
		struct rtpkt packet1;
		struct rtpkt packet2;
		struct rtpkt packet3;
		packet1.sourceid = 0;
		packet1.destid = 1;
		for(int x = 0; x < 4; x++) {
			dt0.costs[x][0] = buf0[x];
			packet1.mincost[x] = buf0[x];	
			packet2.mincost[x] = buf0[x];	
			packet3.mincost[x] = buf0[x];	
		}
		packet2 = packet1;
		packet3 = packet1;
		packet2.destid = 2;
		packet3.destid = 3;
		tolayer2(packet1);
		tolayer2(packet2);
		tolayer2(packet3);
	}
	printdt0(&dt0);
}



void linkhandler0(int linkid, int newcost) {
  /* DON'T CHANGE */
}


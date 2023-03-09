#include <stdio.h>
#include "common.h"

#include "sim_engine.h"

extern int TRACE;
extern int YES;
extern int NO;

int buf2[4] = {0};
struct distance_table dt2;
void printdt2(struct distance_table *dtptr) {
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}

/* Students to write the following two routines, and maybe some others */

void rtinit2() {
 	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			dt2.costs[i][j] = 999;
	dt2.costs[0][2] = 3;
	dt2.costs[1][2] = 1;
	dt2.costs[2][2] = 0;
	dt2.costs[3][2] = 2;
	struct rtpkt packet0;
	struct rtpkt packet1;
	struct rtpkt packet3;
	packet0.sourceid = 2;
	packet0.destid = 0;
	packet1.sourceid = 2;
	packet1.destid = 1;
	packet3.sourceid = 2;
	packet3.destid = 3;
	for(int x = 0; x < 4; x++) {
		packet0.mincost[x] = dt2.costs[x][2];	
		packet1.mincost[x] = dt2.costs[x][2];	
		packet3.mincost[x] = dt2.costs[x][2];	
	}
	tolayer2(packet0);
	tolayer2(packet1);
	tolayer2(packet3);
}


void rtupdate2(struct rtpkt *rcvdpkt) {
  /* TODO */
	//Run bellman on data
	for(int i = 0;i < 4;i++)
		dt2.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i];
	int change = bellman(&dt2, 2, buf2);
	if(change == 1) {
		struct rtpkt packet0;
		struct rtpkt packet1;
		struct rtpkt packet3;
		packet0.sourceid = 2;
		packet0.destid = 0;
		packet1.sourceid = 2;
		packet1.destid = 1;
		packet3.sourceid = 2;
		packet3.destid = 3;
		for(int x = 0; x < 4; x++) {
			dt2.costs[x][2] = buf2[x];
			packet0.mincost[x] = buf2[x];	
			packet1.mincost[x] = buf2[x];	
			packet3.mincost[x] = buf2[x];	
		}
		tolayer2(packet0);
		tolayer2(packet1);
		tolayer2(packet3);
	}
	printdt2(&dt2);
}










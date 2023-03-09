#include <stdio.h>
#include "common.h"

#include "sim_engine.h"

extern int TRACE;
extern int YES;
extern int NO;
int buf3[4] = {0};
struct distance_table dt3;
void printdt3(struct distance_table *dtptr) {
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
}

/* Students to write the following two routines, and maybe some others */

void rtinit3() {
 /* TODO */
 for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			dt3.costs[i][j] = 999;
	dt3.costs[0][3] = 7;
	dt3.costs[1][3] = 999;
	dt3.costs[2][3] = 2;
	dt3.costs[3][3] = 0;
	struct rtpkt packet0;
	struct rtpkt packet2;
	packet0.sourceid = 3;
	packet0.destid = 0;
	packet2.sourceid = 3;
	packet2.destid = 2;
	for(int x = 0; x < 4; x++) {
		packet0.mincost[x] = dt3.costs[x][3];	
		packet2.mincost[x] = dt3.costs[x][3];	
	}
	tolayer2(packet0);
	tolayer2(packet2);
}


void rtupdate3(struct rtpkt *rcvdpkt) {
  /* TODO */
	for(int i = 0;i < 4;i++)
		dt3.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i];
	int change = bellman(&dt3, 3, buf3);
	if(change == 1) {
		struct rtpkt packet0;
		struct rtpkt packet2;
		packet0.sourceid = 3;
		packet0.destid = 0;
		packet2.sourceid = 3;
		packet2.destid = 2;

		for(int x = 0; x < 4; x++) {
			dt3.costs[x][3] = buf3[x];
			packet0.mincost[x] = buf3[x];	
			packet2.mincost[x] = buf3[x];	
		}
		tolayer2(packet0);
		tolayer2(packet2);
		}
	printdt3(&dt3);
}









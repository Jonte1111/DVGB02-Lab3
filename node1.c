#include <stdio.h>
#include "common.h"
#include "sim_engine.h"

extern int TRACE;
extern int YES;
extern int NO;
int buf1[4] = {0};
struct distance_table dt1;
void printdt1(struct distance_table *dtptr) {
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);
}

/* Students to write the following two routines, and maybe some others */

void rtinit1() {
  /* TODO */
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			dt1.costs[i][j] = 999;
	dt1.costs[0][1] = 1;
	dt1.costs[1][1] = 0;
	dt1.costs[2][1] = 1;
	dt1.costs[3][1] = 999;
	struct rtpkt packet0;
	struct rtpkt packet2;
	packet0.sourceid = 1;
	packet0.destid = 0;
	packet2.sourceid = 1;
	packet2.destid = 2;
	for(int x = 0; x < 4; x++) {
		packet0.mincost[x] = dt1.costs[x][1];	
		packet2.mincost[x] = dt1.costs[x][1];	
	}
	tolayer2(packet0);
	tolayer2(packet2);
}

void rtupdate1(struct rtpkt *rcvdpkt) {
    /* TODO */
	for(int i = 0;i < 4;i++)
		dt1.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i];
	int change = bellman(&dt1, 1, buf1);
	if(change == 1) {
		struct rtpkt packet0;
		struct rtpkt packet2;
		packet0.sourceid = 1;
		packet0.destid = 0;
		packet2.sourceid = 1;
		packet2.destid = 2;
		for(int x = 0; x < 4; x++) {
			dt1.costs[x][1] = buf1[x];
			packet0.mincost[x] = buf1[x];	
			packet2.mincost[x] = buf1[x];	
		}
		tolayer2(packet0);
		tolayer2(packet2);
	}
	printdt1(&dt1);
}



void linkhandler1(int linkid, int newcost) {
  /* DON'T CHANGE */
}



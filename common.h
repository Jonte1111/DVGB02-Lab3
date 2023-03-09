struct distance_table {
	int costs[4][4];
};
int bellman(struct distance_table *dataptr, int source, int *buf);

#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

typedef struct {
	int row;
	int col;
	int parent;
} Node;

static int in_bounds(int row, int col)
{
	return row >= 0 && row < MAX_ROW && col >= 0 && col < MAX_COL;
}

int main(void)
{
	Node nodes[MAX_ROW * MAX_COL];
	int queue[MAX_ROW * MAX_COL];
	int visited[MAX_ROW][MAX_COL] = {0};
	int node_count = 0;
	int head = 0;
	int tail = 0;
	int found = -1;

	const int dr[4] = {1, 0, -1, 0};
	const int dc[4] = {0, 1, 0, -1};

	nodes[node_count] = (Node){0, 0, -1};
	visited[0][0] = 1;
	queue[tail++] = node_count;
	node_count++;

	while (head < tail) {
		int idx = queue[head++];
		int row = nodes[idx].row;
		int col = nodes[idx].col;

		if (row == MAX_ROW - 1 && col == MAX_COL - 1) {
			found = idx;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int nr = row + dr[i];
			int nc = col + dc[i];

			if (!in_bounds(nr, nc)) {
				continue;
			}
			if (maze[nr][nc] == 1 || visited[nr][nc]) {
				continue;
			}

			visited[nr][nc] = 1;
			nodes[node_count] = (Node){nr, nc, idx};
			queue[tail++] = node_count;
			node_count++;
		}
	}

	if (found == -1) {
		printf("No path!\n");
		return 0;
	}

	for (int idx = found; idx != -1; idx = nodes[idx].parent) {
		printf("(%d, %d)\n", nodes[idx].row, nodes[idx].col);
	}

	return 0;
}
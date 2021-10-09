// mazeBFSqueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "queue.h"
/*
->start and end -> index row, col
 ALGORITHM:
1.Modify the queue class.
2.Implement BFS for our case
->start from source ->push in	queue
->boolean array ->visited flag (beginning- false)
->bfs:
    loop until queue is not empty
	dequeue->current
	check if current == destination? return pathLength ;
	for eachadjacent cell, if !visited -> add  to queue with pathLnegth of current +1
3. call bfs with source and destination
*/
const int COL = 10;
const int ROWS = 10;
const int helperRow[] = { -1, 1, 0, 0 };
const int helperCol[] = { 0, 0, -1, 1 };

bool isValidCell(int r, int c) {
	return(r < ROWS && r >= 0 && c < COL&&c >= 0);
}
int bfs(bool maze[][COL],
	int sRow, int sCol,
	int eRow, int eCol) {
	//if the way is impossible
	if (maze[sRow][sCol] || maze[eRow][eCol]) {
		return -1;
	}

	//init vidited matrix
	bool visited[ROWS][COL];
	memset(visited, false, sizeof(visited));

	//mark the source cell az visited
	visited[sRow][sCol] = true;

	//create the queue
	Queue queue = Queue();
	queue.enqueue(sRow, sCol, 0);
	int length = 0;
	
	while (!queue.empty()) {
		QNode *current = queue.front();
		current->pathLength = length;
		int cRow = current->row, cCol = current->col;

		if (cRow == eRow && cCol == eCol)
		{
			return current->pathLength;
		}

		queue.dequeue();
		for (int i = 0; i < 4; i++) {
			int nextRow = cRow + helperRow[i];
			int nextCol = cCol + helperCol[i];

			if (isValidCell(nextRow, nextCol) && 
				!visited[nextRow][nextCol] &&
				!maze[nextRow][nextCol]) {
				visited[nextRow][nextCol] = true;
				queue.enqueue(nextRow, nextCol, ++length);

			}
		}
	}
	return -1;

}
int main()

{
	bool maze[ROWS][COL];
	int M, N, T;
	std::cin >> M >> N >> T;
	int sRow = 0, sCol = 0, eRow = 1, eCol = 1;
	int distance = bfs(maze, sRow, sCol, eRow, eCol);
	if (distance == -1) {
		std::cout << "Shortest path doesn't exist" << std::endl;
	}
	std::cout << "Shortest path is: " << distance << std::endl;
    return 0;
}


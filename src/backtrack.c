#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <wchar.h>
#include <sys/time.h>

#define CELL_UP 0b00000001;
#define CELL_DOWN 0b00000010;
#define CELL_LEFT 0b00000100;
#define CELL_RIGHT 0b00001000;


#define CORNER_UP 0b00010000;
#define CORNER_DOWN 0b00100000;
#define CORNER_LEFT 0b01000000;
#define CORNER_RIGHT 0b10000000;
#define DIRECTIONS_SIZE 4

#define	N 1
#define	S 2
#define	E 4
#define	W 8

struct Maze {
	union {
		struct {
			int width;
			int height;
			int start_x; // -1 if unset
			int start_y; // -1 if unset
			int end_x; // -1 if unset
			int end_y; // -1 if unset
			double bias;
		};
		FILE* source;
	};
	struct Tile_Set* tile_set;
	struct Solution* solution;
	//byte** data; // more memory dense than an array of cells
};

struct Solution {
	//byte** map;
};

struct Tile_Set {
	bool unicode;
	union {
		struct {
			char tiles[16]; // vertical, horizontal, ne, nw, sw, se, swn, wne, nes, esw, full
		};

		struct {
			wchar_t* u_tiles[16]; // array of pointers to unicode strings
		};
	};
};

/*
struct Point{
	union{
		uint_8_t mask;
		struct{
			uint_8_t
				corner_right :1,
				corner_left :1,
				corner_down :1,
				corner_up :1,
				cell_right :1,
				cell_left :1,
				cell_down :1,
				cell_up :1;
		};
	};
};
*/

int move_x(int direction) {
	int moved_x;
	switch (direction) {
	case 1 :
		moved_x = 0;
		break;
	case 2 :
		moved_x = 0;
		break;
	case 4 :
		moved_x = 1;
		break;
	case 8 :
		moved_x = -1;
		break;
	}
	return moved_x;
}

int move_y(int direction) {
	int moved_y;
	switch (direction) {
	case 1 :
		moved_y = 1;
		break;
	case 2 :
		moved_y = -1;
		break;
	case 4 :
		moved_y = 0;
		break;
	case 8 :
		moved_y = 0;
		break;
	}
	return moved_y;
}

int opposite_direction(int direction) {
	int opposed_direction;
	switch (direction) {
	case 1 :
		opposed_direction = 2;
		break;
	case 2 :
		opposed_direction = 1;
		break;
	case 4 :
		opposed_direction = 8;
		break;
	case 8 :
		opposed_direction = 4;
		break;
	}
	return opposed_direction;
}

void shuffle(int *array, size_t n)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int usec = tv.tv_usec;
	srand48(usec);


	if (n > 1) {
		size_t i;
		for (i = n - 1; i > 0; i--) {
			size_t j = (unsigned int) (drand48() * (i + 1));
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}

bool inRange(unsigned low, unsigned high, unsigned x)
{
	return (low <= x && x <= high);
}

void carve_passages_from(int x, int y, int maze[4][4]) {

	//Displaying array elements
	printf("STARTING 2-D array elements:\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", maze[i][j]);
			if (j == (4 - 1)) {
				printf("\n");
			}
		}
	}
	//int DXe = 1;
	//int DXw = -1;
	//int DXn = 0;
	//int DXs = 0;
	//int DYe = 0;
	int nx;
	int ny;

	// list of directions
	int directions[DIRECTIONS_SIZE] = {N, S, E, W};

	// shuffle the list
	shuffle(directions, DIRECTIONS_SIZE);

	// for each direction
	for (int i = 0; i < DIRECTIONS_SIZE; i++) {

		nx = move_x(directions[i]) + x;
		ny = move_y(directions[i]) + y;

		//printf("ITERATION %d: plan to move %d steps in X direction\n", i, nx);
		//printf("ITERATION %d: plan to move %d steps in Y direction\n", i, ny);

		bool y_in_range = inRange(0, 4 - 1, ny);
		bool x_in_range = inRange(0, 4 - 1, nx);
		bool is_zero = maze[nx][y] == 0;

		//printf("ITERATION %d: Y in range %d\n", i, y_in_range);
		//printf("ITERATION %d: X in range %d\n", i, x_in_range);
		//printf("ITERATION %d: cell is zero %d\n", i, is_zero);

		if (y_in_range && x_in_range && is_zero) {
			maze[y][x] = maze[y][x] || directions[i];
			//printf("ITERATION %d: maze[%d][%d] %d\n", i, y,x,maze[y][x]);
			maze[ny][nx] = maze[ny][nx] || opposite_direction(directions[i]);
			//printf("ITERATION %d: maze[%d][%d] %d\n", i, ny,nx, maze[ny][nx]);
			carve_passages_from(nx, ny, maze);
		}
	}

}

void gen_backtrack(int maze[4][4]) {

	//Displaying array elements
	printf("STARTING 2-D array elements:\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", maze[i][j]);
			if (j == (4 - 1)) {
				printf("\n");
			}
		}
	}

	carve_passages_from(0, 0, maze);

	//Displaying array elements
	printf("ENDING 2-D array elements:\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", maze[i][j]);
			if (j == (4 - 1)) {
				printf("\n");
			}
		}
	}
}

int main()
{
	printf("Hello world\n");

	struct Maze maze;
	maze.width = 4;
	maze.height = 4;

	int disp[maze.width][maze.height];
	int i, j;
	for (i = 0; i < maze.width; i++) {
		for (j = 0; j < maze.height; j++) {
			disp[i][j] = 0;
		}
	}

	gen_backtrack(disp);
	return 0;
}

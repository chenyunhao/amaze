/*
 * =====================================================================================
 *
 *       Filename:  amaze.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/19 11:35:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cyher (), cyher.net A~T gmail.com
 *        Company:  cyher.net
 *
 * =====================================================================================
 */
#ifndef AMAZE_H
#define AMAZE_H

#include <stdint.h>

#define INITIAL_POS 0
#define UP 3
#define DOWN 4
#define LEFT 2
#define RIGHT 1

#define HAS_VISITED -1

#define MAX_ARRAY 500000
#define MAX_STEPS 100
#define MAX_AXIS 20

extern char amaze_print_buffer[1024];

struct position {
	uint8_t x;
	uint8_t y;
};

struct visited_record {
	uint8_t visited_count;
	uint8_t steps;
};

struct path {
	struct position start;
	struct position end;
	uint8_t direction; // 1= right, 2= left, 3= up, 4= down, 0 = initial position
	uint16_t left_free_square;
	uint8_t steps;
	int8_t *visited_array;
	struct path *parent_path;
	struct visited_record *visited_records;
};


int find_the_shortest_path (int8_t maze_array[], int width, int height);
void display_maze(int8_t maze_array[], int width, int height);

#endif           /* AMAZE_H */

/*
 * =====================================================================================
 *
 *       Filename:  amaze.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/19 10:32:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cyher (), cyher.net A~T gmail.com
 *        Company:  cyher.net
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"

int array_width;
int array_height;

struct path *path_array[MAX_ARRAY];
int path_count;


static int get_multi_array_index(int a, int b, int c, int d)
{
	int index = a +
		b * MAX_AXIS +
		c * MAX_AXIS * MAX_AXIS +
		d * MAX_AXIS * MAX_AXIS * MAX_AXIS;
	return index;
}

static int count_free_square(int array[], int size)
{
	int free_squares = 0;
	for (int i = 0; i < size; i++) {
		if (array[i] > 0) {
			free_squares++;
		}
	}

	return free_squares;
}

void display_maze(int maze_array[], int width, int height)
{

#define CLEAR() printf("\033[2J")
	//CLEAR();
	for (int i = 0; i < width * height; i++) {
		if (i % width == 0) {
			printf("\n");
		}
		if (maze_array[i] < 0) {
			printf("%2s", " #");
		} else if (maze_array[i] == 0) {
			printf("%2s", " 0");
		} else {
			printf("%2s", "  ");
		}
	}
	printf("\n");
}

static int is_dead_end(struct path *path)
{
	int count = 0;
	if (path->visited_array[path->start.y * array_width + path->start.x + 1] == 0) {
		count++;
	}

	if (path->visited_array[path->start.y * array_width + path->start.x - 1] == 0) {
		count++;
	}

	if (path->visited_array[(path->start.y + 1) * array_width + path->start.x] == 0) {
		count++;
	}

	if (path->visited_array[(path->start.y - 1) * array_width + path->start.x] == 0) {
		count++;
	}

	if (count == 3) {
		return 1;
	}

	return 0;
}

static void reversed_print_list(struct path *path)
{
	int direction = path->direction;

	if(path->parent_path != NULL) {
		reversed_print_list(path->parent_path);
	}
#if 0

	if (direction == UP) {
		printf("%s ", "UP");
	} else if (direction == DOWN) {
		printf("%s ","DOWN");
	} else if (direction == LEFT) {
		printf("%s ","LEFT");
	} else if (direction == RIGHT) {
		printf("%s ","RIGHT");
	}
#else
	if (path->parent_path != NULL)
		sprintf(amaze_print_buffer, "%s%d, ",amaze_print_buffer, direction);
#endif

	return;
}


static int move_to_next(struct queue *queue, struct path *parent_path, int direction)
{
	int visited_count = 0;
	struct path *path = (struct path *)malloc(sizeof(struct path));

	path->parent_path = parent_path;
	path->left_free_square = parent_path->left_free_square;


	path->start.x = parent_path->end.x;
	path->start.y = parent_path->end.y;

	path->direction = direction;
	path->steps = parent_path->steps+1;

	if (path->steps > MAX_STEPS) {
		free(path);
		return -1;
	}

#if 0
	if (path_array[path->start.x + path->start.y * array_width] != NULL) {
		free(path);
		return -1;
	}
#endif

	path->visited_array = (int *)calloc(array_width * array_height, sizeof(int));
	memcpy(path->visited_array, parent_path->visited_array, sizeof(int) * array_width * array_height);

	if (path->visited_array[path->start.y * array_width + path->start.x] == 0) {
		free(path->visited_array);
		free(path);
		return -1;
	}

	int i;

	if (direction == UP) {
		for (i = 0; i < (path->start.y - 0); i++) {
			if (path->visited_array[(path->start.y - i) * array_width + path->start.x] != 0) {
				if (path->visited_array[(path->start.y - i) * array_width + path->start.x] != HAS_VISITED) {
					path->visited_array[(path->start.y - i) * array_width + path->start.x] = HAS_VISITED;
					visited_count++;
				}
			} else {
				break;
			}
		}
	} else if (direction == DOWN) {
		for (i = 0; i < (array_height - path->start.y); i++) {
			if (path->visited_array[(path->start.y + i) * array_width + path->start.x] != 0) {
				if (path->visited_array[(path->start.y + i) * array_width + path->start.x] != HAS_VISITED) {
					path->visited_array[(path->start.y + i) * array_width + path->start.x] = HAS_VISITED;
					visited_count++;
				}
			} else {
				break;
			}
		}
	} else if (direction == LEFT) {
		for (i = 0; i < (path->start.x - 0); i++) {
			if (path->visited_array[path->start.y * array_width + path->start.x - i] != 0) {
				if (path->visited_array[path->start.y * array_width + path->start.x - i] != HAS_VISITED) {
					path->visited_array[path->start.y * array_width + path->start.x - i] = HAS_VISITED;
					visited_count++;
				}
			} else {
				break;
			}
		}
	} else if (direction == RIGHT) {
		for (i = 0; i < (array_width - path->start.x); i++) {
			if (path->visited_array[path->start.y * array_width + path->start.x + i] != 0) {
				if (path->visited_array[path->start.y * array_width + path->start.x + i] != HAS_VISITED) {
					path->visited_array[path->start.y * array_width + path->start.x + i] = HAS_VISITED;
					visited_count++;
				}
			} else {
				break;
			}
		}
	}

	int steps = i - 1;

	if (steps == 0) {
		free(path->visited_array);
		free(path);
		return -1;
	}

	if (direction == UP) {
		path->end.x = path->start.x;
		path->end.y = path->start.y - steps;
	} else if (direction == DOWN) {
		path->end.x = path->start.x;
		path->end.y = path->start.y + steps;
	} else if (direction == LEFT) {
		path->end.x = path->start.x - steps;
		path->end.y = path->start.y;
	} else if (direction == RIGHT) {
		path->end.x = path->start.x + steps;
		path->end.y = path->start.y;
	}

	path->left_free_square -= visited_count;

	//path_array[path->start.x + path->start.y * array_width] = path;
	if (path->end.x == parent_path->start.x && path->end.y == parent_path->start.y && !is_dead_end(path)) {
		free(path->visited_array);
		free(path);
		return -1;
		//repeat path except dead end
	}

	// to avoid the recursion situation;
	//
	//
#if 0
	if (path->steps > 3) {
		struct path *three_steps = parent_path;

		for (int i = 0; i < 3; i++) {
			three_steps = three_steps->parent_path;
		}

		if (path->start.x == three_steps->start.x &&
				path->start.y == three_steps->start.y &&
				path->end.x == three_steps->end.x &&
				path->end.y == three_steps->end.y) {
			free(path->visited_array);
			free(path);
			return -1;
		}
	}
#endif

	
#if 0
	uint8_t path_visited_count = parent_path->visited_records[get_multi_array_index(path->start.x, path->start.y, path->end.x, path->end.y)].visited_count;
	uint8_t path_visited_steps = parent_path->visited_records[get_multi_array_index(path->start.x, path->start.y, path->end.x, path->end.y)].steps;

	//path->visited_records = (struct visited_record *)calloc(MAX_AXIS * MAX_AXIS * MAX_AXIS * MAX_AXIS, sizeof(struct visited_record));
	path->visited_records = parent_path->visited_records;
	path->visited_records[get_multi_array_index(path->start.x, path->start.y, path->end.x, path->end.y)].visited_count = path_visited_count + 1;
	path->visited_records[get_multi_array_index(path->start.x, path->start.y, path->end.x, path->end.y)].steps = path->steps;
	path_count++;

	if (path_visited_count > 1 && (path->steps - path_visited_steps) < 3) {
	parent_path->visited_records[get_multi_array_index(path->start.x, path->start.y, path->end.x, path->end.y)].visited_count = 1;
		free(path->visited_array);
		free(path);
		return -1;

	}
#endif

#if 1
	uint8_t path_visited_count = parent_path->visited_records[get_multi_array_index(path->start.x, path->start.y, path->end.x, path->end.y)].visited_count;
	uint8_t path_visited_steps = parent_path->visited_records[get_multi_array_index(path->start.x, path->start.y, path->end.x, path->end.y)].steps;

	//path->visited_records = (struct visited_record *)calloc(MAX_AXIS * MAX_AXIS * MAX_AXIS * MAX_AXIS, sizeof(struct visited_record));
	path->visited_records = parent_path->visited_records;
	path->visited_records[get_multi_array_index(path->start.x, path->start.y, path->end.x, path->end.y)].visited_count = path_visited_count + 1;
	path->visited_records[get_multi_array_index(path->start.x, path->start.y, path->end.x, path->end.y)].steps = path->steps;

	if (path_visited_count == 2 && (path->steps - path_visited_steps) < 2) {
		parent_path->visited_records[get_multi_array_index(path->start.x, path->start.y, path->end.x, path->end.y)].visited_count = 1;
		free(path->visited_array);
		free(path);
		return -1;

	}
#endif


#if 0
	display_maze(path->visited_array, array_width, array_height);
	usleep(10000);

#endif
	enqueue(queue, path);
	
	if (path->left_free_square <= 0) {
		return 0;
	}
	
	return 1;
}

static struct position find_start_left_bottom(int maze_array[], int width, int height)
{
	struct position pos = {0, 0};
	unsigned int x = 0;
	unsigned int y = 0;

	for (x = 0; x < width; x++) {
		for (y = height - 1; y > 0; y--) {
			if (maze_array[y * width + x] > 0) {
				pos.x = x;
				pos.y = y;
				return pos;
			}
		}
	}

	return pos;
}

static struct position find_start_left_up(int maze_array[], int width, int height)
{
	struct position pos = {0, 0};
	unsigned int x = 0;
	unsigned int y = 0;

	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			if (maze_array[y * width + x] > 0) {
				pos.x = x;
				pos.y = y;
				return pos;
			}
		}
	}

	return pos;
}


int find_the_shortest_path (int maze_array[], int width, int height) {
	array_width = width;
	array_height = height;
	int visited_count = 0;
	int free_squares_count = count_free_square(maze_array, array_width * array_height);


	memset(path_array, 0, sizeof(struct path *) * MAX_ARRAY);

	struct position pos = find_start_left_bottom(maze_array, width, height);
	//struct position pos = find_start_left_up(maze_array, width, height);
	struct path initial_path = {
		.start = pos,
		.end = pos,
		.steps = 0,
		.direction = INITIAL_POS,
		.parent_path = NULL,
	};
	initial_path.visited_array = (int *)calloc(array_width * array_height, sizeof(int));
	memcpy(initial_path.visited_array, maze_array, sizeof(int) * array_width * array_height);
	initial_path.visited_array[initial_path.start.y * array_width + initial_path.start.x] = HAS_VISITED;
	initial_path.left_free_square = free_squares_count - 1;

#if 1 
	initial_path.visited_records = (struct visited_record *)calloc(MAX_AXIS * MAX_AXIS * MAX_AXIS * MAX_AXIS, sizeof(struct visited_record));
	initial_path.visited_records[get_multi_array_index(pos.x, pos.y, pos.x,pos.y)].steps = initial_path.steps;
	initial_path.visited_records[get_multi_array_index(pos.x, pos.y, pos.x,pos.y)].visited_count = 1;
	path_count = 0;
#endif
	struct queue *queue = init_queue();

	enqueue(queue, &initial_path);

	struct path *path;
	while (!is_queue_empty(queue)) {
		path = dequeue(queue);

		// UP
		if (move_to_next(queue, path, UP) == 0) {
			reversed_print_list(path);
			//printf("UP\n");
			sprintf(amaze_print_buffer, "%s%d", amaze_print_buffer, UP);
			break;
		}

		// DOWN
		if (move_to_next(queue, path, DOWN) == 0) {
			reversed_print_list(path);
			//printf("DOWN\n");
			sprintf(amaze_print_buffer, "%s%d", amaze_print_buffer, DOWN);
			break;
		}

		// LEFT
		if (move_to_next(queue, path, LEFT) == 0) {
			reversed_print_list(path);
			sprintf(amaze_print_buffer, "%s%d",amaze_print_buffer, LEFT);
			//printf("LEFT\n");
			break;
		}
		// RIGHT
		if (move_to_next(queue, path, RIGHT) == 0) {
			reversed_print_list(path);
			sprintf(amaze_print_buffer, "%s%d ",amaze_print_buffer, RIGHT);
			//printf("RIGHT\n");
			break;
		}
		
		//display_maze(path->visited_array, array_width, array_height);
		free(path->visited_array);
		//free(path->visited_records);
	}

	return 0;
}

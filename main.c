/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/19 00:16:22
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
#include <time.h>
#include <libgen.h>
#include "amaze.h"
#include "libmxml/mxml.h"
#include "filenames.h"

//#define USE_FILENAME_H

clock_t start, finish;
double  duration;
char amaze_print_buffer[];

int main(int argc, char **argv)
{
	char *filename;
#ifdef USE_FILENAME_H
	for (int i = 0; i < sizeof(filenames)/sizeof(filenames[0]); i++) {
		filename = filenames[i];
#else
		filename = argv[1];
#endif
		start = clock();
		FILE* fp = fopen(filename,"r");
		mxml_node_t* xml = mxmlLoadFile(NULL,fp,MXML_NO_CALLBACK);
		mxml_node_t* layer = NULL;
		mxml_node_t* data = NULL;

		// find note
		layer = mxmlFindElement(xml, xml,"layer",NULL,NULL,MXML_DESCEND);
		//get attr
		data = mxmlFindElement(layer, xml,"data",NULL,NULL,MXML_DESCEND);
		int width = atoi(mxmlElementGetAttr(layer,"width"));
		int height = atoi(mxmlElementGetAttr(layer,"height"));
		//printf("width = %d, height = %d\n", width, height);


		mxmlDelete(xml);
		fclose(fp);

		char line[2000];
		char *result = NULL;
		int8_t maze_array[5000];
		int count = 0;

		fp = fopen(filename,"r");

		int j = 0;
		while(fgets(line, 2000, fp) != NULL) {
			j++;
			if (j > 5 && (j - 5 <= height)) {
				result = strtok(line, ",");
				int i = 0;
				while( result != NULL ) {
					if (i < width) {
						maze_array[count++] = atoi(result);
						result = strtok(NULL, ",");
						i++;
					} else {
						break;
					}
				}
			}
		}
		fclose(fp);

		//printf("width = %d, height = %d\n", width, height);
		//display_maze(maze_array, width, height);

		find_the_shortest_path(maze_array, width, height);

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;

		printf("%s, ",basename(filename));
		printf("%f, ", duration );
		if (strlen(amaze_print_buffer) != 0) {
			printf("%s\n", amaze_print_buffer);
		} else {
			printf("No path to finish\n");
		}
		memset(amaze_print_buffer, 0, 1024);
#ifdef USE_FILENAME_H
	}
#endif

	return 0;
}

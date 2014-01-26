#ifndef STRUCT_H
#define	STRUCT_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {LEFT, RIGHT, UP, DOWN} direction;
typedef char* color;

/* List of colors, to be used for matching, random generation, etc */
typedef struct colors {
	color*	colors;
	short	length;
} colors;

typedef struct maskgrid {
	short**		mask;
	short		xdim;
	short		ydim;
} maskgrid;

#endif
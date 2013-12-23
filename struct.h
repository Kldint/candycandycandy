#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct direction {LEFT, RIGHT, UP, DOWN} direction;

/* Single color -- Might need to be replaced with the SDL definition */
typedef struct color {
	int		R;
	int		G;
	int		B;
} color;

/* List of colors, to be used for matching, random generation, etc */
typedef struct colors {
	color*	colors;
	short	length;
}

typedef struct maskgrid {
	short**		mask;
	short		xdim;
	short		ydim;
} maskgrid;

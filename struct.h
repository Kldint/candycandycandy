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

/* Types of every chip */
typedef enum chiptype {
	NONE,		// Empty cell
	NORMAL,
	SUPERH, 	// Horizontal
	SUPERV,		// Vertical
	EXPLO,		// Explosive
	JOKER		// Multicoloured joker
} chiptype;

/* Definition of a single chip */
typedef struct chip {
	short		flavour;		// Corresponds to a color id
	chiptype	type;	
} chip;

typedef struct chippos {
	short 		x;
	short		y;
} chippos;
	
typedef struct chipgrid {
	chip** 		chips;
	short		xdim;
	short		ydim;
} chipgrid;

typedef struct maskgrid {
	short**		mask;
	short		xdim;
	short		ydim;
} maskgrid;

/* Types of possible matchings */
typedef enum combitype {
	MATCH3,
	MATCH4,
	MATCH5,
	MATCHCROSS,
	MATCHJOKER
} combitype;

/*	Definition of a single combination 
	To be used as a chained list */
typedef struct combi {
	short			flavour;
	combitype		type;
	short			length;
	chippos*		matched;
	struct combi*	next;
} combi;
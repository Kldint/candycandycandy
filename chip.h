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
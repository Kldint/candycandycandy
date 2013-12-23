#include "chip.h"
#include "struct.h"

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

void appendCombiList(combi** list, combi* element);
void removeCombiList(combi** list, combi* element);
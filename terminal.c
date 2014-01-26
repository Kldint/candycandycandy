#include "terminal.h"

colors initColors() {
	color str;
	colors set;
	set=malloc(sizeof(colors));
	
	str=malloc(10);
	strcpy(str, TermColor_Red);
	colors.colors[0] = str;
	
	str=malloc(10);
	strcpy(str, TermColor_Green);
	colors.colors[1] = str;
	
	str=malloc(10);
	strcpy(str, TermColor_Yellow);
	colors.colors[2] = str;
	
	str=malloc(10);
	strcpy(str, TermColor_Blue);
	colors.colors[3] = str;
	
	return colors;
}

void displayGrid(chipgrid grid, colors colorset) {
	int x, y;
	
	for(y=0; y < grid->ylen; y++) {
		for(x=0; x < grid->xlen; x++) {
			printf(colorset.colors[grid->chips[x][y].flavour] "@");
		}
		printf("\n");
	}
}
#include "terminal.c"

void main() {
	colors colorset = initColors();
	
	chipgrid gamegrid = malloc(sizeof(chipgrid));
	gamegrid.xdim = 9;
	gamegrid.ydim = 9;
	
	initChipGrid(&gamegrid, colorset);
	displayGrid(gamegrid, colorset);
}
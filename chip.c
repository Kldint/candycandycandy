#include "chip.h"

chip* newChipRandom(colors colorset) {
	chip* newchip = malloc(sizeof(chip));
	newchip->type = NORMAL;
	newchip->flavour = rand()%(colorset->length);
	return newchip;
}

void initChipGrid(chipgrid *grid, colors colorset) {
	int x, y;
	grid->chips = malloc(sizeof(chip*)*grid->xdim);
	for(x=0; x<grid->xdim; x++) {
		grid->chips[x] = malloc(sizeof(chip)*grid->ydim);
		for(y=0; y<grid->ydim; y++)
			grid->chips[x][y] = newChipRandom(colorset);
	}
}
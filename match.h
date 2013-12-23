#include "struct.h"
#include "combi.h"
#include "chip.h"

int seekMatchStep(chipgrid *grid, chippos *current, direction dir, int *flavour);
combi* seekMatch(chipgrid *grid, maskgrid *mask, colors *colors);
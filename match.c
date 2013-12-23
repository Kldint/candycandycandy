// Check if a neighbouring chip is part of a combination
int seekMatchStep(chipgrid *grid, chippos *current, direction dir, int flavour) {
	// Represents target chip position 
	int nx=current.x, ny=current.y;
	if(dir == LEFT) nx--;
	if(dir == RIGHT) nx++;
	if(dir == UP) ny--;
	if(dir == DOWN) ny++;

	// Check the target is not out of bounds
	if(nx<0 || nx>=grid->xlen || ny<0 || ny>= grid->ylen) return 0;

	// Check the next chip is of a valid type for a match
	if(		(grid->chips[nx][ny].flavour == flavour) 
		||	(grid->chips[x][y].type	== JOKER)
		||	(grid->chips[nx][ny].type == JOKER)
	) {
		// Progress in that direction and indicates the match
		current->x = nx;
		current->y = ny;
		return 1;
	}
	
	return 0;
}

//	Returns all possible combinations in the grid
//	The search is done based on the potentially changed items in the grid mask
combi* seekMatch(chipgrid *grid, maskgrid *mask, colors *colors) {
	// The mask is a bitwise, indicates which chips needs to be checked (0x01)
	// if the chip is part of an existing horizontal match (0x02)
	// or part of a vertical match (0x04)
	
	int i, j, c, ci;
	chippos[20]	matched;
	chippos cursor;
	combi* combilist;
	combi* combilisth;
	combi* combilistv;
	combi* newcombi;
	combi* combicursor;
	int flavour;
	int jokercombi;
	
	//	Iterate through the mask of chips to check
	for(i=0; i < mask.xdim; i++) {
		for(j=0; j < mask.ydim; j++) {
			if(!(mask.mask[i][j] & 0x01)) continue;		// Doesn't need to be checked
			
			// Search horizontally
			if(!(mask.mask[i][j] & 0x02)) {
				c=1; jokercombi = 0;
				cursor.x=i; cursor.y=j; flavour=grid->chips[i][j].flavour;
				while(seekMatchStep(grid, &cursor, RIGHT, flavour)) {
					// Learn the flavour of the combination if applicable, and add the chip to the list of matched ones
					if(grid->chips[cursor.x][cursor.y].type == JOKER) { jokercombi = 1;
					} else { flavour=grid->chips[cursor.x][cursor.y].flavour; }
					matched[c] = cursor;
					c++;
				}
				// Search backwards
				cursor.x=i; cursor.y=j;
				while(seekMatchStep(grid, &cursor, LEFT, flavour)) {
					if(grid->chips[cursor.x][cursor.y].type == JOKER) { jokercombi = 1;
					} else { flavour=grid->chips[cursor.x][cursor.y].flavour; }
					matched[c] = cursor;
					c++;
				}
				
				if(c>=3) {
					// If the match is long enough, add it to the list of combinations
					newcombi = malloc(sizeof(combi));
					newcombi->matched = malloc(sizeof(chippos)*c);
						
					newcombi->flavour = flavour;
					newcombi->length = c;
					newcombi->next = NULL;
						
					if(jokercombi) newcombi->type = MATCHJOKER;
					else if(c==3) newcombi->type = MATCH3;
					else if(c==4) newcombi->type = MATCH4;
					else newcombi->type = MATCH5;
					
					for(ci=0; ci<c; ci++) {
						// Mark the chips as part of a match so they're not checked again
						mask.mask[matched[ci].x][matched[ci].y] |= 0x02;
						// Copy matches to the combination
						newcombi->matched[ci] = matched[ci];
					}
					
					appendCombiList(&combilisth, newcombi);
				}
			}
		}
	}
}
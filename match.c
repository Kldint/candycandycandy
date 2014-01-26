#include "match.h"

// Check if a neighbouring chip is part of a combination
int seekMatchStep(chipgrid *grid, chippos *current, direction dir, int *flavour) {
	// Represents target chip position 
	int nx=current.x, ny=current.y;
	if(dir == LEFT) nx--;
	if(dir == RIGHT) nx++;
	if(dir == UP) ny--;
	if(dir == DOWN) ny++;

	// Check the target is not out of bounds
	if(nx<0 || nx>=grid->xlen || ny<0 || ny>= grid->ylen) return 0;

	// Check the next chip is of a valid type for a match
	if(		(grid->chips[nx][ny].flavour == *flavour) 
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
	
	int i, j, ch, cv, ci, cj, cc;
	chippos	matchh[10];
	chippos matchv[10];
	chippos *match;
	chippos cursor;
	combi* combilist;
	combi* combicursor;
	combi* newcombi;
	int jokercombih, jokercombiv, flavour, crossed, foundcombi;
	
	//	Iterate through the grid chips, matching on chips indicated by the mask
	for(i=0; i < mask.xdim; i++) {
		for(j=0; j < mask.ydim; j++) {
			if(!(mask.mask[i][j] & 0x01)) continue;			// Doesn't need to be checked
			if(grid->chips[i][j].type == JOKER) continue;	// Skip jokers as origin chip for convenience
			
			flavour=grid->chips[i][j].flavour;
			crossed=0;
			
			// Search horizontally
			if(!(mask.mask[i][j] & 0x02)) {
				ch=1; jokercombih=0; 
				
				cursor.x=i; cursor.y=j; 
				while(seekMatchStep(grid, &cursor, RIGHT, flavour)) {
					if(grid->chips[cursor.x][cursor.y].type == JOKER) jokercombih = 1;
					matchh[ch++] = cursor;
				}
				
				// Reset position and search backwards
				cursor.x=i; cursor.y=j;
				while(seekMatchStep(grid, &cursor, LEFT, flavour)) {
					if(grid->chips[cursor.x][cursor.y].type == JOKER) jokercombih = 1;
					matchh[ch++] = cursor;
				}
			}
			
			// Search vertically
			if(!(mask.mask[i][j] & 0x04)) {
				ch=1; jokercombiv=0;
				
				cursor.x=i; cursor.y=j; 
				while(seekMatchStep(grid, &cursor, DOWN, flavour)) {
					if(grid->chips[cursor.x][cursor.y].type == JOKER) jokercombiv = 1;
					matchv[cv++] = cursor;
				}
				
				// Reset position and search backwards
				cursor.x=i; cursor.y=j;
				while(seekMatchStep(grid, &cursor, UP, flavour)) {
					if(grid->chips[cursor.x][cursor.y].type == JOKER) jokercombiv = 1;
					matchv[cv++] = cursor;
				}
			}
			if(ch<3 && cv<3) continue;
			
			// If we have a valid combination, tag chips as part of them so we don't have to look them up again
			if(ch>=3) for(ci=0; ci<ch; ci++) mask.mask[matchh[ci].x][matchh[ci].y] |= 0x02;
			if(cv>=3) for(ci=0; ci<cv; ci++) mask.mask[matchv[ci].x][matchv[ci].y] |= 0x04;
			
			// If this chip happens to be part of horizontal and vertical combinations,
			// find and retrieve the opposite pair so we can join them in a crossed combination
			if((ch<3 || cv<3) && (mask.mask[i][j] & 0x06)) {
				combicursor = combilist; foundcombi = 0;
				while(combicursor && !foundcombi) {
					for(ci=0; ci<combicursor->length; ci++) 
						if(		(combicursor->matched[ci].x == i)
							&&	(combicursor->matched[ci].y == j))
							foundcombi=1;
					if(!foundcombi) combicursor = combicursor->next;
				}
				
				// Get the match pair, and remove the other combination from the list
				if(ch<3) { 
					cv=combicursor->matched;
					removeCombiList(&combi, combicursor);
					free(combicursor);
				} else if(cv<3) { 
					ch=combicursor->matched;
					removeCombiList(&combi, combicursor);
					free(combicursor);
				}

				crossed=1;
			// If we already found both right here, there's nothing more to do
			} else if(ch>=3 && cv>=3) crossed=1;
			
			// If we have a cross-match, merge matched chips
			if(crossed) {
				cc = ch;
				match = malloc(sizeof(chippos)*(cv+ch-1));
				memcpy(match, matchh, sizeof(chippos)*(ch-1));
				// Copy chip positions one by one and only keep unique ones
				for(ci=0; ci<cv; ci++) {
					foundcombi=0;
					for(cj=0; cj<cc; cj++) {
						if(	(matchv[ci].x == match[cj].x)
						&&	(matchv[ci].y == match[cj].y) )	foundcombi=1;
					}
					if(!foundcombi) match[cc++] = matchv[ci];
				}
			} else if(ch >= 3) {
				match = malloc(sizeof(chippos)*(ch));
				memcpy(match, matchh, sizeof(chippos)*ch);
			} else if(cv >= 3) {
				match = malloc(sizeof(chippos)*(cv));
				memcpy(match, matchv, sizeof(chippos)*cv);
			}
						
			newcombi = malloc(sizeof(combi));
			newcombi->flavour = flavour;
			newcombi->next = NULL;
			newcombi->matched = match;
			
			if(crossed) {
				newcombi->length = cc;
				newcombi->type = MATCHCROSS;
			} else if(ch >= 3) {
				newcombi->length = ch;
			} else if(cv >= 3) {
				newcombi->length = cv;
			}
			
			if(!crossed) {
				if(newcombi->length == 3)		newcombi->type = MATCH3;
				else if(newcombi->length == 4)	newcombi->type = MATCH4;
				else 							newcombi->type = MATCH5;
			} 
			
			if(	(jokercombih && ch >= 3)
			 ||	(jokercombiv && cv >= 3) )		newcombi->type = MATCHJOKER;
			 
			appendCombiList(&combilist, newcombi);
		}
	}
	
	return *combilist;
}
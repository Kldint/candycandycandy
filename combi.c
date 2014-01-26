#include "combi.h"

void appendCombiList(combi** list, combi* element) {
	combi* cursor;
	if(!list) { 
		*list=element;
		return;
	}
	cursor = (*list);
	while(cursor->next) { cursor = cursor->next; }
	cursor->next = element;
}
	
void removeCombiList(combi** list, combi* element) {
	combi* cursor;
	
	if(!list) return;
	cursor = (*list);
	while(cursor->next && cursor->next != element) {}
	if(cursor->next == element) {
		cursor->next = element->next;
		element->next = NULL;
	}
	
	return;
}
void appendCombiList(combi** list, combi* element) {
	combi* cursor;
	if(!list) { 
		*list=element;
		return;
	}
	cursor = (*list);
	while(cursor->next) {}
	cursor->next = element;
}
	
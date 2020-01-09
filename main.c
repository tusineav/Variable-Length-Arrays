#include <stdio.h>
#include <stdlib.h>

//A row contains a list of elements, and an array contains a list of rows

struct row {
	char element;

	struct row * next;
};

struct array {
	struct row * data;

	struct array * next;
};

typedef struct row Row;
typedef struct array Array;

//Functions for freeing list-related data
void freeRow(Row *r);
void freeArray(Array *list);

//Functions for adding data to the lists
void addElement(Row **r, char element);
void addRow(Array **list, Row *r);

//Functions for printing
void printRow(Row *r);
void printList(Array *list);

int main(void) {
	char c;
	Array *list;
	Row *tempRow;

	while (scanf("%c", &c) > 0) {
		if (c == '\n') {
			addRow(&list, tempRow);
		}
		else {
			addElement(&tempRow, c);
		}
	}

	printList(list);	

	freeRow(tempRow);
}

void freeRow(Row *r) {
	if (r == NULL) {
		return;
	}
	else {
		freeRow(r->next);
		free(r);
	}
}

void addElement(Row **r, char element) {
	//Create the actual data element to be inserted...
	Row *toInsert = (Row *) malloc(sizeof(Row));
	toInsert->element = element;
	toInsert->next = NULL;

	//...Then insert it into the row
	if (*r == NULL) {
		*r = toInsert;
	}
	else {
		Row *current = *r;
		while (current->next != NULL) {
			current = current->next;
		}

		current->next = toInsert;
	}
}

void addRow(Array **list, Row *r) {
	Array *toInsert = (Array *) malloc(sizeof(Array));
	toInsert->data = r;
	toInsert->next = NULL;

	if (*list == NULL) {
		*list = toInsert;
	}
	else {
		Array *current = *list;
		while (current->next != NULL) {
			current = current->next;
		}
		
		current->next = toInsert;
	}
}

void printRow(Row *r) {
	Row *current = r;

	while (current != NULL) {
		printf("%c ", current->element);
		
		current = current->next;
	}
}

void printList(Array *list) {
	Array *current = list;

	while (current != NULL) {
		printRow(current->data);

		current = current->next;
	}
}

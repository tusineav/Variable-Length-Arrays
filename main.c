#include <stdio.h>
#include <stdlib.h>

//A row contains a list of elements, and an array contains a list of rows

struct row {
	char element;

	struct row * next;
};

struct array {
	struct row data;

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

int main(void) {
	char c;
	Array *list;
	Row *tempRow;

	while (scanf("%c", &c) > 0) {
		addElement(&tempRow, c);
	}

	

	freeRow(tempRow);
}

void freeRow(Row *r) {
	if (r == NULL) {
		return;
	}
	else {
		//The print is currently here because it's easier to test
		printf("%c", r->element);
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

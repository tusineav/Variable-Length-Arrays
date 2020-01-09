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
void freeList(Array *list);

//Functions for adding data to the lists
void addElement(Row **r, char element);
void addRow(Array **list, Row *r);

//Functions for printing
void printRow(Row *r);
void printList(Array *list);

int main(void) {
	char c;
	Array *list = NULL;
	Row *tempRow = NULL;

	while (scanf("%c", &c) > 0) {
		if (c == '\n') {
			addRow(&list, tempRow);
			tempRow = NULL;
		}
		else {
			if (c != ' ') {
				addElement(&tempRow, c);
			}
		}
	}

	printList(list);	

	freeList(list);
}

void freeRow(Row *r) {
	if (r == NULL) {
		return;
	}
	else {
		freeRow(r->next);
		free(r);
		r = NULL;
	}
}

void freeList(Array *list) {
	if (list == NULL) {
		return;
	}
	else {
		freeList(list->next);
		freeRow(list->data);
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
	//Create the actual array element to be inserted...
	Array *toInsert = (Array *) malloc(sizeof(Array));
	toInsert->data = r;
	toInsert->next = NULL;

	//...Then insert it into the list
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

//Both functions loop through the row or array, respectively, and call their respective prints.
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
		printf("\n");

		current = current->next;
	}
}

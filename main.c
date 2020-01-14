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

void countElements(Array *list, int *rows, int *cols);

//Functions for printing
void printRow(Row *r);
void printList(Array *list);

int main(void) {
	//Prepare to read all input data
	char c;
	Array *list = NULL;
	Row *tempRow = NULL;

	//Loop over all input data
	while (scanf("%c", &c) > 0) {
		//Newline indicates a new row, add the current row to the list
		if (c == '\n') {
			addRow(&list, tempRow);
			tempRow = NULL;
		}
		else {
			//Otherwise, add the read element. Skip whitespace
			if (c != ' ') {
				addElement(&tempRow, c);
			}
		}
	}
	
	//printList(list);

	//Prepare to convert the list into an array
	int rows, cols;
	
	countElements(list, &rows, &cols);

	int array[rows][cols];

	Array *current = list;

	for(int i = 0; i < rows; i++) {
		tempRow = current->data;

		for(int j = 0; j < cols; j++) {
			if (tempRow == NULL) {
				array[i][j] = '*';
				continue;
			}

			array[i][j] = tempRow->element;

			tempRow = tempRow->next;
		}

		current = current->next;
	}

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			printf("%c ", array[i][j]);
		}

		printf("\n");
	}

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

void countElements(Array *list, int *rows, int *cols) {

	//Since jagged arrays don't exist in C, we will keep track of the max number of columns. This will reduce error due to user input
	int maxCols = 0;
	Array *current = list;
	Row *tempRow;

	*rows = 0;
	//If the list exists, loop through the list
	while (current != NULL) {
		(*rows)++;

		//If the row exists, loop through all elements
		if (current->data != NULL) {
			*cols = 0;
			tempRow = current->data;

			//Count the number of elements in the row
			while (tempRow != NULL) {
				(*cols)++;
			
				tempRow = tempRow->next;
			}
			
			//Update the max number of columns if needed
			if (*cols > maxCols) {
				maxCols = *cols;
			}

		}

		current = current->next;
	}

	*cols = maxCols;
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

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

int main(void) {

}

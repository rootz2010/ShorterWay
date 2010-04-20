#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define FILLING 0.3
#define INFI_LOCAL 20

int nb_summit = 10;

/* simple data structure : chained-list containing the number of the summit */
struct chained_list {
	unsigned long int number;
	int value;
	struct chained_list * next;
};

/* function to save the datas in a file */

/* function to convert a matrix into a chained list */
struct chained_list ** convert_matrix(int ** tab) {
	unsigned long int i, j;
	struct chained_list * pointer;
	
	/* we allocate nb_summit cells for the chained list tab */
	struct chained_list **list = (struct chained_list **) calloc(nb_summit, sizeof(struct chained_list *));
	
	for (i=0; i<nb_summit; i++) {
		list[i]= NULL;
		for (j=0; j<nb_summit; j++) {
			/* to convert the matrix we want to take only the cells set */
			if (j != i && tab[i][j] != INFI_LOCAL) {
				/* if list[i] is NULL, it means we have to allocate a struct in it */
				if (list[i] == NULL) {
					list[i] = (struct chained_list *) malloc(sizeof(struct chained_list));
					/* we copy the address of the new struct in the pointer */
					pointer = list[i];
				}
				/* else it means we already filled the cell with at least one value, and we have
				 * created a pointer */
				else {
					pointer->next = (struct chained_list *) malloc(sizeof(struct chained_list));
					pointer = pointer->next;
				}
				/* storing time ! */
				pointer->number = j;
				pointer->value = tab[i][j];
			}
		}
		pointer->next = NULL;
	}
	
	return &list[0];
}

/* function to convert from chained_list to matrix ? is there a need for it ? */

/* function to print the matrix in the terminal ... simple displaying method */
void print_matrix(int ** tab) {
	
	unsigned long int i, j;
	
	for (i=0; i<nb_summit; i++) {
		for (j=0; j<nb_summit; j++) {
			printf("%d ", tab[i][j]);
		}
		printf("\n");
	}
}

/* function to print a chained_list */
void print_chained_list(struct chained_list ** list) {
	unsigned long int i;
	struct chained_list * pointer;
	
	for (i=0; i<nb_summit; i++) {
		printf("summit %ld\t", i + 1);
		pointer = list[i];
		/* while we have something to display, we just display it ...*/
		while (pointer != NULL) {
			printf("d(%ld,%ld)=%d\t", i + 1, (pointer->number) + 1, pointer->value);
			pointer = pointer->next;
		}
		printf("\n");
	}
}


/* function to generate a random graph */
int ** random_graph() {
	
	unsigned long int i, j;
	
	int **tab = (int **) calloc(nb_summit, sizeof(unsigned long int *));
	
	/* allocate space for our little matrix */
	for (i=0; i<nb_summit; i++) {
		tab[i] = (int *) calloc(nb_summit, sizeof(unsigned long int));
	}
	
	/* generate random arc with its value */
	for (i=0;i<nb_summit;i++){
		/* generate the cost of the arc */
		for (j=0; j<nb_summit; j++) {
			if (j != i) {
				/* we fill the value only if we are under the FILLING percentage */
				if (rand()/(RAND_MAX + 1.) < FILLING) {
					tab[i][j] = (int) (1 + round(rand()/(RAND_MAX + 1.) * (INFI_LOCAL -1 )));
				}
				else {
					tab[i][j] = INFI_LOCAL;
				}

			}
			else {
				tab[i][i] = 0;
			}
		}
	}
	
	return tab;
}

/* function to free a chained_list */
void free_list(struct chained_list ** list) {
	unsigned long int i;
	
	struct chained_list * pointer;
	struct chained_list * tmp;
	
	for (i=0; i<nb_summit; i++) {
		pointer = list[i];
		/* to suppress the case of an empty row */
		if (pointer != NULL) {
			/* then we free as we go further in the graph */
			while (pointer->next != NULL) {
				tmp = pointer->next;
				free(pointer);
				pointer = tmp;
			}
		}
	}
	free(list);
	printf("list memory free\n");
}

/* function to free a matrix, not so complicated */
void free_matrix(int ** matrix) {
	unsigned long int i;
	for (i=0; i<nb_summit; i++) {
		free(matrix[i]);
	}
	free(matrix);
	printf("matrix memory free\n");
}

int main (int argc, const char * argv[]) {
	
	/* just to have a different configuration each time  */
    srand(time((time_t *)0));
	
	/* first we use a matrix to generate the graph. then we will have a function
	 to make the conversion to the struct */
	
	int ** tab;
	struct chained_list ** liste;
	tab = random_graph();
	print_matrix(tab);
	liste = convert_matrix(tab);
	print_chained_list(liste);
	free_list(liste);
	free_matrix(tab);
    return 0;
}

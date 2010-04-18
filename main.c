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
	unsigned long int numero;
	int value;
	struct chained_list * next;
};

/* function to save the datas in a file */

/* function to convert a matrix into a chained list */
struct chained_list * convert_matrix(int ** tab) {
	unsigned long int i, j;
	struct chained_list * pointer;
	
	struct chained_list **list = (struct chained_list **) calloc(nb_summit, sizeof(struct chained_list *));
	
	for (i=0; i<nb_summit; i++) {
		for (j=0; j<nb_summit; j++) {
			if (j != i && tab[i][j] != 0) {
				pointer->numero = j;
				/* have a pointer to the current editing struct, as done in a stack ? */
				
			}
		}
	}
	
	return NULL;
}

/* function to convert from chained_list to matrix ? is there a need for it ? */

/* function to print the matrix in the terminal ... simple displaying method */
void print_matrix(int ** tableau) {
	
	int i, j;
	
	for (i=0; i<nb_summit; i++) {
		for (j=0; j<nb_summit; j++) {
			printf("%d ", tableau[i][j]);
		}
		printf("\n");
	}
}

/* function to print a chained_list, maybe as a tab ? */

/* function to generate a random graph */
int ** random_graph() {
	
	unsigned long int i, j;
	
	int **tableau = (int **) calloc(nb_summit, sizeof(unsigned long int *));
	
	/* allocate space for our little matrix */
	for (i=0; i<nb_summit; i++) {
		tableau[i] = (int *) calloc(nb_summit, sizeof(unsigned long int));
	}
	
	/* generate random arc with its value */
	for (i=0;i<nb_summit;i++){
		/* generate the cost of the arc */
		for (j=0; j<nb_summit; j++) {
			if (j != i) {
				/* we fill the value only if we are under the FILLING percentage */
				if (rand()/(RAND_MAX + 1.) < FILLING) {
					tableau[i][j] = (int) (1 + round(rand()/(RAND_MAX + 1.) * (INFI_LOCAL -1 )));
				}
				else {
					tableau[i][j] = INFI_LOCAL;
				}

			}
			else {
				tableau[i][i] = 0;
			}
		}
	}
	
	return tableau;
}

int main (int argc, const char * argv[]) {
	
	/* just to have a different configuration each time  */
    srand(time((time_t *)0));
	
	/* first we use a matrix to generate the graph. then we will have a function
	 to make the conversion to the struct */
	
	print_matrix(random_graph());
	
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define REMPLISSAGE 0.3
#define INFI_LOCAL 20

int nb_summit = 10;

/* simple data structure : chained-list containing the number of the summit */
struct chained_list {
	unsigned long int numero;
	struct chained_list * next;
};

/* function to save the datas in a file */

/* function to convert a matrix into a chained list */

/* function to print the matrix */
void print_matrix(unsigned long int ** tableau) {
	
	int i, j;
	
	for (i=0; i<nb_summit; i++) {
		for (j=0; j<nb_summit; j++) {
			printf("%ld ", tableau[i][j]);
		}
		printf("\n");
	}
}

/* function to generate a random graph */
unsigned long int ** random_graph(unsigned long int ** tableau) {
	
	unsigned long int i, j, nb_followers, value, sommet;
	tableau = (unsigned long int **) calloc(nb_summit, sizeof(unsigned long int *));
	
	/* allocate space for our little matrix, and initialize the diagonal */
	for (i=0; i<nb_summit; i++) {
		tableau[i] = (unsigned long int *) calloc(nb_summit, sizeof(unsigned long int));
		tableau[i][i] = INFI_LOCAL;
	}
	
	/* generate random arc with its value*/
	for (i=0;i<nb_summit;i++){
		/* generate a random number of followers */
		nb_followers = (int) round(rand()/(RAND_MAX + 1.) * nb_summit * REMPLISSAGE);
		j=0;
		/* generate the cost of the arc */
		while (j<nb_followers) {
			sommet = (int) round(rand()/(RAND_MAX + 1.) * nb_summit);
			/* if tableau !=0 it means we already used this summit, as calloc initialize
			 * to zero the cells of the matrix */
			if (tableau[i][sommet] == 0) {
				value = (unsigned long int) (1 + round(rand()/(RAND_MAX + 1.) * (INFI_LOCAL -1 )));
				tableau[i][sommet] = value;
				printf("%ld\n", tableau[i][sommet]);
				j++;
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
	unsigned long int **adj_mat;
	
	adj_mat = random_graph(adj_mat);
	print_matrix(adj_mat);
	
    return 0;
}

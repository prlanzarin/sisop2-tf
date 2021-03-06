#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/matrix.h"

/* Matrix allocator. New matrix of sizes rows x cols */
MATRIX *MATRIX_new(int rows, int cols) { 
	int i;
	MATRIX *new_mat = (MATRIX *)malloc(sizeof(MATRIX));
	new_mat->r = rows;
	new_mat->c = cols;
	if((new_mat->matrix = malloc(rows * sizeof(int *))) == NULL)
		return NULL;
	for(i = 0; i < rows; i++) {
		if((new_mat->matrix[i] = malloc(cols * sizeof(int))) == NULL)
			return NULL;
	}
	return new_mat;
}

/* Matrix deallocator */
void MATRIX_free(MATRIX *matrix) {
	int i;
	for(i = 0; i < matrix->r; i++)
			free((void *) matrix->matrix[i]);
	free((void *) matrix->matrix);
	free((void *) matrix);
}

/* Sequential matrix multiplier; debugging subroutine */
MATRIX *MATRIX_sequential_multiply(MATRIX *m1, MATRIX *m2) {
	int i, j, k, sum;
	if(!MATRIX_is_multipliable(m1, m2)) {
		fprintf(stderr, "ERROR: invalid matrixes sizes.\n");
		return NULL;
	}
	
	MATRIX *result = MATRIX_new(m1->r, m2->c);
	for(i = 0; i < m1->r; i++) {
		for(j = 0; j < m2->c; j++) {
			sum = 0;
			for(k = 0; k < m2->r; k++)
				sum = sum + (m1->matrix[i][k] * m2->matrix[k][j]); 
			result->matrix[i][j] = sum;
		}
	}
	return result;	
}
/* Matrix line multiplier. Multiplies line 'row' of MATRIX m1 to m2 */
void MATRIX_line_multiply(MATRIX *mout, MATRIX *m1, MATRIX *m2, int row) {
	int sum, j, k;
	for(j = 0; j < m2->c; j++) {
		sum = 0;
		for(k = 0; k < m2->r; k++) {
			sum = sum + (m1->matrix[row][k] * m2->matrix[k][j]); 
		}
		mout->matrix[row][j] = sum;
	}
}
/* Checks if m1 and m2 are multipliable matrixes based on their sizes */
int MATRIX_is_multipliable(MATRIX *m1, MATRIX *m2) {
	return (m1->c == m2->r);
}
/* Checks if m1 and m2 are equal, element-by-element. m1 and m2 of equal sizes*/
int MATRIX_is_equal(MATRIX *m1, MATRIX  *m2) {
	int i, j;

	if((m1->r != m2->r) || (m1->c != m2->c))
		return 0;
	for(i = 0; i < m1->r; i++) {
		for(j = 0; j < m2->c; j++) {
			if(m1->matrix[i][j] != m2->matrix[i][j])
				return 0;
		}
	}
	
	return 1;
}

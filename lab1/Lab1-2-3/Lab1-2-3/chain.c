#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()
#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:
int power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

// implementation
matrix *create_matrix(int num_rows, int num_cols)
{
    // TODO
    matrix *Matrix = (matrix *)malloc(sizeof(Matrix));

    if (Matrix == NULL) { //check whether the allocation was successful
        return NULL;
    }

    Matrix->num_rows = num_rows;
    Matrix->num_colm = num_cols;

    Matrix->data = (int **)malloc(num_rows * sizeof(int *));
    if (Matrix->data == NULL) { //checks whether memory allocation for the row pointers
        free(Matrix);
        return NULL;
    }

    for (int i = 0; i < num_rows; i++) { // allocates memory for row
        Matrix->data[i] = (int *)calloc(num_cols, sizeof(int));
        if (Matrix->data[i] == NULL) {
            // Memory allocation failed
            for (int j = 0; j < i; j++) {
                free(Matrix->data[j]);
            }
            free(Matrix->data);
            free(Matrix);
            return NULL;
        }
    }

    return Matrix;
}

void add_row(matrix *mat, int *row)
{
    // TODO
    //allocate memory for a newD array
    int **newD = (int **)realloc(mat->data, (mat->num_rows + 1) * sizeof(int *));
    mat->data = newD;
    mat->data[mat->num_rows] = (int *)malloc(mat->num_colm * sizeof(int));
    for (int i = 0; i < mat->num_colm; i++) {
        mat->data[mat->num_rows][i] = row[i];
    }
    mat->num_rows++;
}

void add_col(matrix *mat, int *col)
{
    // TODO
    for (int i = 0; i < mat->num_rows; i++) {
        int *new_row = (int *)realloc(mat->data[i], (mat->num_colm + 1) * sizeof(int));
        mat->data[i] = new_row;
        mat->data[i][mat->num_colm] = col[i];
    }
    mat->num_colm++; //// Update the number of columns in the matrix
}

void increment(matrix *mat, int num)
{
    // TODO
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_colm; j++) {
            mat->data[i][j] += num;
        }
    }
}

void scalar_multiply(matrix *mat, int num)
{
    // TODO
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_colm; j++) {
            mat->data[i][j] *= num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    // TODO
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_colm; j++) {
            mat->data[i][j] /= num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    // TODO
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_colm; j++) {
            mat->data[i][j] = power(mat->data[i][j], num);
        }
    }
}

void delete_matrix(matrix *mat)
{
    // TODO
    if (mat == NULL) {
        return;
    }

    for (int i = 0; i < mat->num_rows; i++) {
        free(mat->data[i]);
    }

    free(mat->data);
    free(mat);
}


/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat)
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_colm; ++col_idx) {
            if (col_idx == mat->num_colm - 1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

//Add the rest of the functions needed for the chain below

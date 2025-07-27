// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#define MAX_TEMP_SIZE 300
// user-defined header files
#include "chain.h"

// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);
matrix * getCopymatrix(matrix * mat){
    matrix * copy = malloc(sizeof(mat));
    copy->num_rows = mat->num_rows;
    copy->num_colm= mat->num_colm;

    int num_rows = mat->num_rows;
    int num_colm= mat->num_colm;

    int **row = malloc(sizeof(int *)*num_rows);
    int *col;
    for(int i = 0; i < num_rows; i++){
        col = malloc(sizeof(int) * num_colm);
        for(int j = 0; j < num_colm; j++){
            col[j] = mat->data[i][j];
        }
        row[i] = col;
    }
    copy->data = row;
    return copy;
}
void processCommands(matrix *mat, node **currentNode, chain *chn, int command)
{
    switch (command)
    {
        case 2: //adding a new row to the matrix
        {
            int nrow[mat->num_colm];
            for (int i = 0; i < mat->num_colm; i++)
            {
                int in_1 = 0;
                scanf("%i", &in_1);
                nrow[i] = in_1;
            }
            add_row(mat, nrow);
            break;
        }
        case 3: //adding a new column to the matrix
        {
            int ncols[mat->num_rows];
            for (int i = 0; i < mat->num_rows; i++)
            {
                int in_1 = 0;
                scanf("%i", &in_1);
                ncols[i] = in_1;
            }
            add_col(mat, ncols);
            break;
        }

        case 4: //incrementing all elements of the matrix
        {
            int factor = 0;
            scanf("%i", &factor);
            increment(mat, factor);
            break;
        }

        case 5: //scalar multiplication of the matrix
        {
            int factor = 0;
            scanf("%i", &factor);
            scalar_multiply(mat, factor);
            break;
        }

        case 6: //scalar division of the matrix
        {
            int factor = 0;
            scanf("%i", &factor);
            scalar_divide(mat, factor);
            break;
        }

        case 7: //raising the matrix to a certain power
        {
            int factor = 0;
            scanf("%i", &factor);
            scalar_power(mat, factor);
            break;
        }

        default:
            // Handle unknown command or exit
            return;
    }

    node *node1 = malloc(sizeof(node));
    node1->prev = *currentNode;
    node1->next = NULL;
    node1->mat = getCopymatrix(mat);
    (*currentNode)->next = node1;
    *currentNode = (*currentNode)->next;
}
void processFirstRow(char temp[], int *num_columns) {
    if (fgets(temp, MAX_TEMP_SIZE, stdin) != NULL) {
        fgets(temp, MAX_TEMP_SIZE, stdin);
    }

    *num_columns = 0;
    for (int i = 0; i < 29; i++) {
        if ((temp[i] == ' ' && temp[i + 1] == ' ') || (((int)(temp[i]) < 48) || ((int)(temp[i]) > 57))) {
            break;
        }
        i += 1;
        (*num_columns)++;
    }
}
void populateDataArray(char temp[], int num_columns, int inp, int num[]) {
    int tempidx = 0;
    for (int i = 0; i < num_columns * 2; i++) {
        num[tempidx] = (int)(temp[i]) - 48;
        tempidx++;
        i++;
        if (tempidx > num_columns) {
            break;
        }
    }

    for (int i = 0; i < num_columns * (inp - 1); i++) {
        int inputs;
        scanf("%i", &inputs);
        num[num_columns + i] = inputs;
    }
}
void incrementMatrixValues(matrix *mat, int num[], int num_columns, int inp) {
    int point = 0;
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_colm; j++) {
            mat->data[i][j] += num[point];
            point++;
        }
    }
}
void processCommandsLoop(chain *chn, matrix *mat) {
    node *currentNode = chn->head;

    int in_0 = 0;
    scanf("%i", &in_0);

    while (in_0 != 0) {
        processCommands(mat, &currentNode, chn, in_0);

        scanf("%i", &in_0);
    }
}
int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}

void run(chain *chn) {
    //get No.of raws
    int inp;
    scanf("%i", &inp);

    char temp[300];
    int num_columns;

    processFirstRow(temp, &num_columns);

    int num[num_columns * inp];
    populateDataArray(temp, num_columns, inp, num);

    matrix *mat = create_matrix(inp, num_columns);
    incrementMatrixValues(mat, num, num_columns, inp);

    node *node1 = malloc(sizeof(node));
    node1->prev = NULL;
    node1->next = NULL;
    node1->mat = getCopymatrix(mat);
    chn->head = node1;

    processCommandsLoop(chn, mat);
}

//Print the chain
void print_chain(chain * chn)
{
    node * current = chn->head;
    while(current != NULL){
        print_matrix(current->mat);
        printf("\n");
        current = current->next;
    }
    printf("\n");
}

//---------------------------------------

// Function to process commands using switch cases




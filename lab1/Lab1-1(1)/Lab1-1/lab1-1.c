// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <stdbool.h>
#include <string.h>

// user-defined header files
#include "node.h"

// macros
#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list * lst);
void run(list * lst);


int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
}

// parse the input
// parse the input
void run(list* lst) {
    //to get input
    char inputArr[100]; // Assuming a maximum input length of 100 characters
    scanf("%s", inputArr);

    // Tokenize the input string based on commas
    char* Seperate = strtok(inputArr, ",");
    int count = -1;
    while (Seperate != NULL) {
        insert_node_after(lst, count, Seperate);
        Seperate = strtok(NULL, ",");
        count++;
    }


    while (true) {
        int type;
        scanf("%d", &type);

        if (type == 0) {
            break;
        }
        else if (type == 1 || type == 2) {
            int position;
            char word[50];
            scanf("%d %s", &position, word);

            if (type == 1) {
                insert_node_before(lst, position, word);
            }
            else {
                insert_node_after(lst, position, word);
            }
        }
        else if (type == 3) {
            int position;
            scanf("%d", &position);
            delete_node(lst, position);
        }
        else if(type == 4)
            delete_list(lst);
    }
}

//Print the list contents
void print_list(list * lst)
{
    if (lst == NULL || lst->head == NULL) {
        return;
    }

    node *current = lst->head;
    do {
        printf("%s ", current->word);
        current = current->next;
    } while (current != lst->head);
    printf("\n");
}






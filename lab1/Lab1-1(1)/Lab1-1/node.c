// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
void insert_node_before(list *lst, int index, char *word)
{	
	// TODO
    if (lst == NULL || word == NULL) {
        // Handle invalid inputs
        return;
    }

    int list_size = 0;
    node *current = lst->head;
    do {
        list_size++;
        current = current->next;
    } while (current != lst->head);

    if (index < 0) {
        index = (list_size + index) % (list_size + 1); // Convert negative index to positive
    }

    if (index > list_size || index < 0) {
        return; // Invalid index
    }

    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL) {
        // Handle memory allocation failure
        return;
    }

    new_node->word = (char *)malloc(strlen(word) + 1); // +1 for null terminator
    if (new_node->word != NULL) {
        strcpy(new_node->word, word);
    } else {
        // Handle memory allocation failure
        free(new_node);
        return;
    }

    if (index == 0 || lst->head == NULL) {
        // Inserting at the beginning or if the list is empty
        new_node->next = lst->head;
        lst->head = new_node;
        return;
    }

    current = lst->head;
    node *previous = NULL;
    int currentIndex = 0;

    while (currentIndex < index) {
        previous = current;
        current = current->next;
        currentIndex++;
    }

    // Insert the new node before the node at index
    new_node->next = current;
    previous->next = new_node;
}

void insert_node_after(list *lst, int index, char *word)
{
	// TODO
    if (lst == NULL || word == NULL || index < -1) {
        // Handle invalid inputs
        return;
    }

    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL) {
        // Handle memory allocation failure
        return;
    }

    new_node->word = (char *)malloc(strlen(word) + 1); // +1 for null terminator
    if (new_node->word != NULL) {
        strcpy(new_node->word, word);
    } else {
        // Handle memory allocation failure
        free(new_node);
        return;
    }

    if (index == -1 || lst->head == NULL) {
        // Inserting at the end or if the list is empty
        new_node->next = lst->head;
        if (lst->head == NULL) {
            lst->head = new_node;
            new_node->next = new_node; // Circular link for the first node
        } else {
            node *last = lst->head;
            while (last->next != lst->head) {
                last = last->next;
            }
            last->next = new_node;
        }
        return;
    }

    node *current = lst->head;
    int currentIndex = 0;

    // Traverse the list to find the node at index
    while (current->next != lst->head && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    // Insert the new node after the node at index
    new_node->next = current->next;
    current->next = new_node;
}

char *list_to_sentence(list *lst)
{
	// TODO
    return NULL; // Change this line accordingly
}

void delete_node(list *lst, int index)
{
	// TODO
    if (lst == NULL || lst->head == NULL) {
        return;
    }

    int list_size = 0;
    node *current = lst->head;
    do {
        list_size++;
        current = current->next;
    } while (current != lst->head);

    if (index < 0) {
        index = list_size + index; // Convert negative index to positive
    }

    if (index >= list_size || index < 0) {
        return; // Invalid index
    }

    current = lst->head;
    node *previous = NULL;
    int currentIndex = 0;

    while (currentIndex < index) {
        previous = current;
        current = current->next;
        currentIndex++;
    }

    if (previous == NULL) {
        // Deleting the head node
        node *last = lst->head;
        while (last->next != lst->head) {
            last = last->next;
        }
        last->next = lst->head->next;
        lst->head = lst->head->next;
    } else {
        previous->next = current->next;
    }

    free(current->word);
    free(current);
}

void delete_list(list *lst)
{
	// TODO
    if (lst == NULL || lst->head == NULL) {
        return;
    }

    node *current = lst->head;
    while (current->next != lst->head) {
        node *temp = current;
        current = current->next;
        free(temp->word);
        free(temp);
    }
    free(current->word);
    free(current);
    lst->head = NULL; // Reset the head pointer
}

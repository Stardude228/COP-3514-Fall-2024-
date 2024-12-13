#include <stdio.h>
#include <stdlib.h>  // for malloc

// Define the structure of a node
struct node {
    int number;
    struct node *next;
};

// Function to count the number of nodes with the value n
int count_nodes(struct node *list, int n) {
    int count = 0;
    struct node *current = list;  // Start from the head of the list
    
    // Traverse through the list
    while (current != NULL) {
        if (current->number == n) {
            count++;  // Increment count if current node's value is equal to n
        }
        current = current->next;  // Move to the next node
    }
    return count;  // Return the total count of nodes with value n
}

void search_node(struct node *list, int n) {
    int index = 0;
    struct node *current = list;

    while (current != NULL) {
        if (current->number == n) {
            printf("The number %d appears on %d index.\n", n, index);
        }
        index++;
        current = current->next;
    }
}

struct node *add_to_list(struct node *list, int n) { 
    struct node *new_node;
    new_node = malloc(sizeof(struct node));

    if (new_node == NULL) {
        printf("malloc failed in add_to_list\n");
        return list;
    }
    
    // new_node->value = n;
    new_node->next = list;
    return new_node;
}

int main() {
    // Example linked list: 5 -> 10 -> 20 -> 10 -> 30 -> 10
    struct node *head = malloc(sizeof(struct node));
    struct node *first = NULL;
    int number, count = 0;
    

    head->number = 5;
    head->next = malloc(sizeof(struct node));
    head->next->number = 10;
    head->next->next = malloc(sizeof(struct node));
    head->next->next->number = 20;
    head->next->next->next = malloc(sizeof(struct node));
    head->next->next->next->number = 10;
    head->next->next->next->next = malloc(sizeof(struct node));
    head->next->next->next->next->number = 30;
    head->next->next->next->next->next = malloc(sizeof(struct node));
    head->next->next->next->next->next->number = 10;
    head->next->next->next->next->next->next = NULL;

    // Count the nodes containing the value 10
    int count = count_nodes(head, 10);
    printf("The number 10 appears %d times in the list.\n", count);

    // Search for number 10
    search_node(head, 30);

    // Inserting nodes
    first = add_to_list(first, 35);
    first = add_to_list(first, 6);
    first = add_to_list(first, 98);
    return 0;
}

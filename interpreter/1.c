#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *data;        // pointer to store string
    struct Node *prev; // pointer to store prev string
    struct Node *next; // pointer to store next string
} Node;

void insert(Node **head, const char *str)
{
    // create a new node and allocated memory
    Node *new_node = (Node *)malloc(sizeof(Node));

    if (!new_node)
    {
        perror("failed to allocate memory");
        return;
    }

    new_node->data = strdup(str);
    if (!new_node->data)
    {
        perror("failed to allocate memory for a string");
        free(new_node);
        return;
    }

    new_node->next = *head;
    new_node->prev = NULL;

    if (*head)
    {
        (*head)->prev = new_node;
    }
    *head = new_node;
}

Node *find(Node *head, const char *str)
{
    Node *current = head;
    while (current)
    {
        if (strcmp(current->data, str) == 0)
        {
            return current; // Found the node
        }
        current = current->next;
    }
    return NULL; // Not found
}

void delete(Node **head, const char *str)
{
    Node *node_to_delete = find(*head, str);
    if (!node_to_delete)
        return;

    if (node_to_delete->prev)
    {
        node_to_delete->prev->next = node_to_delete->next;
    }
    else
    {
        *head = node_to_delete->next; // If deleting the head
    }

    if (node_to_delete->next)
    {
        node_to_delete->next->prev = node_to_delete->prev;
    }

    free(node_to_delete->data); // Free string
    free(node_to_delete);       // Free node
}

void free_list(Node *head)
{
    Node *current = head;
    while (current)
    {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main()
{
    Node *head = NULL;
    insert(&head, "ye");
    Node *temp = head;
    while (temp)
    {
        printf("%s -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    return 0;
}
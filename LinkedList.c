#include <stdio.h>
#include <stdlib.h>


//MACRO
#define NEW_INT_NODE(val) new_int_linked_node(val)

typedef struct int_linked_node
{
    struct int_linked_node* next;
    int value;

} int_linked_node;

typedef struct linked_list
{
    int_linked_node* head;

} linked_list;



linked_list* new_linked_list()
{
    linked_list* list = (linked_list*)malloc(sizeof(linked_list));
    list->head = NULL;
    return list;
}

void free_linked_node(int_linked_node* node)
{
    free(node);
}

void delete_linked_list(linked_list* list)
{
    while (list->head)
    {
        int_linked_node* node = list->head;
        list->head = node->next;
        free_linked_node(node);
    }
    free(list);
}

int_linked_node* add_linked_list(linked_list* list, int_linked_node* node)
{
    node->next = list->head;
    list->head = node;
    return node;
}

int_linked_node* new_int_linked_node(int val)
{
    int_linked_node* node = (int_linked_node*)malloc(sizeof(int_linked_node));
    node->next = NULL;
    node->value = val;
    return node;
}

void remove_value(linked_list* list, int value)
{
    int_linked_node* current = list->head;
    int_linked_node* prev = NULL;

    while (current != NULL)
    {
        if (current->value == value)
        {
            if (prev == NULL)
            {
                // If the node to remove is the first 
                list->head = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            free_linked_node(current);
            return;  
        }

        prev = current;
        current = current->next;
    }
}

int main(int argc, char* argv[])
{
    //INIT
    linked_list* int_list = new_linked_list();

    // ADD
    add_linked_list(int_list, NEW_INT_NODE(10));
    add_linked_list(int_list, NEW_INT_NODE(6));
    add_linked_list(int_list, NEW_INT_NODE(1));

    printf("Linked List before removal:\n");
    for (int_linked_node* current = int_list->head; current; current = current->next)
    {
        printf("%d\n", current->value);
    }

    // REMOVE
    remove_value(int_list, 6);

    printf("\nLinked List after removal:\n");
    for (int_linked_node* current = int_list->head; current; current = current->next)
    {
        printf("%d\n", current->value);
    }

    //DELETE
    delete_linked_list(int_list);

    return 0;
}

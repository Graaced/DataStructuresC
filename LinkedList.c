#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define LINKED_LIST(x) &(x)->list_item 

struct list_node
{
    struct list_node *next;      
};

struct list_data_int
{
    struct list_node list_item;
    int item;       
};


struct list_node *list_get_tail(struct list_node **head)
{
    struct list_node *current_node = *head;
    struct list_node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    
    return last_node;
}


struct list_node *list_append(struct list_node **head, struct list_node *item)  
    {
        struct list_node *tail = list_get_tail(head);

        if (!tail)
        {
            *head = item;
        }
        else
        {
            tail->next = item;
        }

        item->next = NULL;

        return item;
        
    }

struct list_node *list_remove(struct list_node **head, struct list_node *target)
{
    if (*head == NULL)
    {
        return NULL;
    }
    
    struct list_node *current = *head;

    while (current->next !=NULL && current->next != target)
    {
        current = current->next;
    } 
    

    if (current->next == NULL)
    {
        return NULL;
    }

    current->next = target->next;
    
    return target;
}


void printList(struct list_node* head) 
{
        struct list_data_int *current_item = (struct list_data_int* )head;

        while (current_item) 
        {
            printf("%d ", current_item->item);
            current_item = (struct list_data_int* )current_item->list_item.next;
        }

        printf("\n");
}

int main()
{
    struct list_node *head = NULL;

    // APPEND
    struct list_data_int *list_value = (struct list_data_int *)malloc(sizeof(struct list_data_int));
    list_value->item = 1;
    list_append(&head, LINKED_LIST(list_value));

    struct list_data_int *list_value1 = (struct list_data_int *)malloc(sizeof(struct list_data_int));
    list_value1->item = 2;
    list_append(&head, LINKED_LIST(list_value1));

    struct list_data_int *list_value2 = (struct list_data_int *)malloc(sizeof(struct list_data_int));
    list_value2->item = 3;
    list_append(&head, LINKED_LIST(list_value2));

    struct list_data_int *list_value3 = (struct list_data_int *)malloc(sizeof(struct list_data_int));
    list_value3->item = 4;
    list_append(&head, LINKED_LIST(list_value3));

    printf("Linked List: ");
    printList(head);


    // REMOVE
    list_remove(&head, LINKED_LIST(list_value1)); 

    printList(head);

    // Memory deallocation
    free(list_value);
    free(list_value1);
    free(list_value2);
    free(list_value3);

    return 0;
}
    

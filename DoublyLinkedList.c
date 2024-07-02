#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define DOUBLY_LIST(x) &(x.list_item)

typedef struct doubly_list
{
    struct doubly_list* prev;
    struct doubly_list* next;

}doubly_list; 

typedef struct doubly_data_int
{
    doubly_list list_item;
    int item;

}doubly_data_int;


doubly_list *list_get_tail(doubly_list **head)
{
    doubly_list *current_node = *head;
    doubly_list *last_node = NULL;

    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
}


doubly_list *list_append (doubly_list **head, doubly_list *item)
{
    doubly_list *tail = list_get_tail (head);

    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    
    item->prev = tail;
    item->next = NULL;

    return item;
}



doubly_list *list_remove(doubly_list **head, doubly_list* target)
{
    if (*head == NULL)
    {
        return NULL;
    }

    doubly_list *current = *head;

    while (current->next != target)
    {
        current = current->next;
    }
    
    current->next = target->next;

    (target->next)->prev = current; 
    
    return target;
}

doubly_list *insert_item_after(doubly_list **head, doubly_list *base_item, doubly_list *new_item)
{
    if (*head == NULL || base_item == NULL)
    {
        return NULL;
    }

    doubly_list *next_item = base_item->next;

    new_item->prev = base_item;
    new_item->next = next_item;

    base_item->next = new_item;

    if (next_item != NULL)
    {
        next_item->prev = new_item;
    }

    return new_item;
}

doubly_list *insert_item_before(doubly_list **head, doubly_list *base_item, doubly_list *new_item)
{
    if (*head == NULL)
    {
        return NULL;
    }

    doubly_list *prev_item = base_item->prev;

    new_item->next = base_item;

    new_item->prev = prev_item;

    base_item->prev = new_item;

    prev_item->next = new_item;

    return new_item;

}

void printList(struct doubly_list* head) 
{
        struct doubly_data_int *current_item = (struct doubly_data_int* )head;

        while (current_item) 
        {
            printf("%d ", current_item->item);
            current_item = (struct doubly_data_int* )current_item->list_item.next;
        }

        printf("\n");
}


int main()
{
    // INIT
    doubly_list *head =  NULL;
    
    //APPEND

    doubly_data_int doubly_value0;
    doubly_value0.item = 1;
    list_append(&head, DOUBLY_LIST(doubly_value0));

    doubly_data_int doubly_value1;
    doubly_value1.item = 2;
    list_append(&head, DOUBLY_LIST(doubly_value1));

    doubly_data_int doubly_value2;
    doubly_value2.item = 3;
    list_append(&head, DOUBLY_LIST(doubly_value2));

    doubly_data_int doubly_value3;
    doubly_value3.item = 4;
    list_append(&head, DOUBLY_LIST(doubly_value3));


    printf("Doubly List: ");
    printList(head);

    //REMOVE
    list_remove(&head, DOUBLY_LIST(doubly_value2));

    // INSERT AFTER
    insert_item_after(&head,DOUBLY_LIST(doubly_value3), DOUBLY_LIST(doubly_value1)); 

    // INSERT BEFORE
    insert_item_before(&head,DOUBLY_LIST(doubly_value3), DOUBLY_LIST(doubly_value1));


    printList(head);

}


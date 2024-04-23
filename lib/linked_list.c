/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** linked_list.c
*/

#include <stdlib.h>
#include "include/my.h"

linked_list_t *new_linked_list(void *data, linked_list_t *previous, int i)
{
    linked_list_t *list = malloc(sizeof(linked_list_t));

    list->next = NULL;
    list->prev = previous;
    list->i = i;
    list->data = data;
    return list;
}

void push(linked_list_t *list, void *data)
{
    int i = 0;

    while (list->next != NULL)
        list = list->next;
    list->next = new_linked_list(data, list, i + 1);
}

/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** my_strdup
*/
#include "my.h"
#include <stdlib.h>
#include <stddef.h>

char *my_strdup(const char *src)
{
    char *new_str;

    if (src == NULL) {
        return NULL;
    }
    new_str = (char *)malloc(sizeof(char) * my_strlen(src) + 1);
    if (new_str == NULL) {
        return NULL;
    }
    my_strcpy(new_str, src);
    return new_str;
}

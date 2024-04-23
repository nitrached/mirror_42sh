/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** my_strrchr
*/
#include "my.h"
#include <stdlib.h>
#include <stddef.h>

char *my_strrchr(const char *str, int ch)
{
    const char *last_occurrence = NULL;

    while (*str != '\0') {
        if (*str == ch) {
            last_occurrence = str;
        }
        str++;
    }
    return (char *)last_occurrence;
}

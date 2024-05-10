/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** remove_last_char.c
*/

#include <stdlib.h>

void remove_last_char(char **buffer, const size_t buffer_size)
{
    if (buffer_size == 0) {
        (*buffer)[0] = 0;
        return;
    }
    (*buffer)[buffer_size] = 0;
}

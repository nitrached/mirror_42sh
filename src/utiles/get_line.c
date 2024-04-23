/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** get_line
*/
#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <stdlib.h>
#include "my.h"

char *get_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, stdin);
    if (read == -1) {
        free(line);
        return NULL;
    }
    line[read - 1] = '\0';
    return line;
}

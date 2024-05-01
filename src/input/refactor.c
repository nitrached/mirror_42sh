/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** refactor.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../../include/minishell.h"
#include "../../include/my.h"

static void handle_index(input_t *input)
{
    input->cursor_position++;
    input->buffer_size++;
}

static int new_str(input_t *input)
{
    char *tmp = realloc(input->buffer, input->buffer_size + 1);

    if (tmp != NULL) {
        input->buffer = tmp;
    } else {
        fprintf(stderr, "Error: realloc failed\n");
        return 84;
    }
    return 0;
}

static void refactor(input_t *input)
{
    input->buffer[input->buffer_size - 1] = input->c;
    input->buffer[input->buffer_size] = 0;
}

int add_char(input_t *input)
{
    my_putchar(input->c);
    handle_index(input);
    if (new_str(input) == 84)
        return 84;
    refactor(input);
    return 0;
}

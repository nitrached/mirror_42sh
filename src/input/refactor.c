/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** refactor.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../../include/minishell.h"
#include "../../include/my.h"

static void handle_index(input_t *input)
{
    input->cursor_position++;
    input->buffer_size++;
}

static int new_str(input_t *input)
{
    char *tmp = realloc(input->buffer, input->buffer_size + 2);

    if (tmp != NULL) {
        input->buffer = tmp;
    } else {
        free(tmp);
        fprintf(stderr, "Error: realloc failed\n");
        return 84;
    }
    return 0;
}

void middle(input_t *input)
{
    bool isSpe = false;

    my_putstr("\033[K");
    my_putstr(input->buffer + (int) input->cursor_position);
    for (int i = 0; i < (int) strlen(input->buffer) -
        (int) input->cursor_position; i++) {
        if (input->buffer[(int) strlen(input->buffer) - i] < 0 && !isSpe) {
            isSpe = true;
            continue;
        }
        isSpe = false;
        my_putstr("\033[D");
    }
}

static void refactor(input_t *input)
{
    if (input->buffer_size != input->cursor_position)
        memmove(input->buffer + (int)input->cursor_position + 1,
            input->buffer + (int)input->cursor_position,
        input->buffer_size - (int)input->cursor_position + 1);
    input->buffer[(int)input->cursor_position] = input->c;
    input->buffer[input->buffer_size + 1] = 0;
}

int add_char(input_t *input, bool *isSpe)
{
    if (isatty(STDIN_FILENO))
        my_putchar(input->c);
    if (new_str(input) == 84)
        return 84;
    if (((*isSpe) == true || input->c > 0) &&
    (int)input->buffer_size != input->cursor_position) {
        middle(input);
        (*isSpe) = false;
    } else
        (*isSpe) = true;
    refactor(input);
    handle_index(input);
    return 0;
}

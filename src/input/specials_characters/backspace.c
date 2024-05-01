/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** backspace.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "../../../include/my.h"
#include "../../../include/minishell.h"
#include <string.h>

void remove_char_from_str(input_t *input)
{
    char *tmp = 0;

    if (input->buffer_size <= 0 || ((int)input->cursor_position) <= 0)
        return;
    (input->buffer_size)--;
    (input->cursor_position)--;
    memmove(input->buffer + (int)input->cursor_position,
    input->buffer + (int)input->cursor_position + 1,
    input->buffer_size - (int)input->cursor_position);
    tmp = realloc(input->buffer, input->buffer_size + 1);
    if (tmp != NULL)
        input->buffer = tmp;
    else
        fprintf(stderr, "Error: realloc failed\n");
    (input->buffer)[input->buffer_size] = 0;
}

static void middle(input_t *input)
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

void delete(input_t *input)
{
    if (input->buffer_size > 0 && ((int)input->cursor_position) > 0) {
        my_putstr("\b \b");
        middle(input);
    }
    if (input->cursor_position >= 1 &&
    input->buffer[(int)input->cursor_position - 1] < 0)
        remove_char_from_str(input);
    remove_char_from_str(input);
}

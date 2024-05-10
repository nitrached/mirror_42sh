/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** erase.c
*/

#include "../../../include/my.h"
#include "../../../include/minishell.h"

void erase(input_t *input, minishell_t *minishell)
{
    if (input->buffer_size > 0 && (input->cursor_position)
    < input->buffer_size) {
        my_putstr("\033[C");
        input->cursor_position++;
        if (input->buffer[(int)input->cursor_position] < 0)
            input->cursor_position++;
        delete(input, minishell);
    }
}

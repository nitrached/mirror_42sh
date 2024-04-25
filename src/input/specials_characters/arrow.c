/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** arrow.c
*/

#include <unistd.h>
#include "../../../include/minishell.h"
#include "../../../include/my.h"

void arrow(input_t *input)
{
    read(STDIN_FILENO, &input->c, 1);
    read(STDIN_FILENO, &input->c, 1);
    if (input->c == 'A' || input->c == 'B') {
        return;
    }
    if (input->c == 'C' &&
    input->cursor_position < strlen_special_char(input->buffer)) {
        input->cursor_position++;
        my_putstr("\033[C");
        return;
    }
    if (input->c == 'D' && input->cursor_position > 0) {
        input->cursor_position--;
        my_putstr("\033[D");
    }
}

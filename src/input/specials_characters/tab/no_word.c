/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** no_word.c
*/

#include "minishell.h"
#include "my.h"

static void display_all(char **buffer)
{
    my_putchar('\n');
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i][0] == '.')
            continue;
        my_putstr(buffer[i]);
        if (buffer[i + 1])
            my_putchar('\t');
    }
    my_putstr("\n$> ");
}

int no_word(input_t *input, char **buffer)
{
    if (input->buffer_size == 0) {
        display_all(buffer);
        return 1;
    }
    return 0;
}

/*
** EPITECH PROJECT, 2024
** 42shMAIN
** File description:
** read.c
*/

#include <termios.h>
#include <unistd.h>
#include "minishell.h"
#include "my.h"
#include <string.h>
#include <stdlib.h>

static int check_special_characters(input_t *input, minishell_t *minishell)
{
    for (int i = 0; tab_keybinds[i].key != 0; i++) {
        if (tab_keybinds[i].key == input->c) {
            tab_keybinds[i].ptr(input, minishell);
            return 1;
        }
    }
    return 0;
}

char *parse_input(minishell_t *minishell)
{
    struct termios old;
    input_t input = {malloc(sizeof(char)), 0, 0, 0};
    bool isSpe = false;

    set_non_canonical(&old);
    while (read(STDIN_FILENO, &input.c, 1) != -1 && input.c != '\n') {
        if (input.c == 4 || input.c == 0) {
            reset_term(&old);
            return NULL;
        }
        if (check_special_characters(&input, minishell) == 1)
            continue;
        if (add_char(&input, &isSpe) == 84)
            return NULL;
    }
    reset_term(&old);
    remove_last_char(&input.buffer, input.buffer_size);
    return input.buffer;
}

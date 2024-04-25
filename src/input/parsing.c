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

static int check_special_characters(input_t *input)
{
    for (int i = 0; tab_keybinds[i].key != 0; i++) {
        if (tab_keybinds[i].key == input->c) {
            tab_keybinds[i].ptr(input);
            return 1;
        }
    }
    return 0;
}

char *parse_input(void)
{
    struct termios old;
    input_t input = {NULL, 0, 0, 0};

    set_non_canonical(&old);
    while (read(STDIN_FILENO, &input.c, 1) != -1 && input.c != '\n') {
        if (check_special_characters(&input) == 1)
            continue;
        if (add_char(&input) == 84)
            return NULL;
    }
    reset_term(&old);
    remove_last_char(&input.buffer, input.buffer_size);
    return input.buffer;
}

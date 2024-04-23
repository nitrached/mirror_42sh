/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** my_unsetenv
*/
#include <stddef.h>
#include "my.h"
#include "minishell.h"
#include <stdlib.h>

int my_unsetenv(minishell_t *minishell)
{
    int line_to_del = 0;
    int len = 0;

    if (USER_INPUT[1] == NULL) {
        my_putstr_fd("unsetenv: Too few arguments.\n", 2);
        return 1;
    }
    for (; ENV[len] != NULL; len++);
    for (; ENV[line_to_del] != NULL; line_to_del++) {
        if (my_strncmp(ENV[line_to_del], USER_INPUT[1],
            my_strlen(USER_INPUT[1])) == 0
            && ENV[line_to_del][my_strlen(USER_INPUT[1])] == '=') {
            tab_delline(&ENV, len, line_to_del);
            ENV[len - 1] = NULL;
        }
    }
    return 1;
}

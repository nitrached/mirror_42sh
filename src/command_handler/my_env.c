/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** my_env
*/
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "minishell.h"
int my_env(minishell_t *minishell)
{
    for (int i = 0; ENV[i] != NULL; i++) {
        my_putstr_fd(ENV[i], 1);
        my_putstr_fd("\n", 1);
    }
    return 1;
}

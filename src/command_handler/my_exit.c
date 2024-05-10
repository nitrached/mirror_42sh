/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** exit
*/
#include <stdlib.h>
#include "minishell.h"

int my_exit(minishell_t *minishell)
{
    free_struc_minishell(minishell);
    exit(0);
}

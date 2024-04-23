/*
** EPITECH PROJECT, 2024
** minishell1_2
** File description:
** init_struct
*/
#include <stddef.h>
#include <stdlib.h>
#include "minishell.h"
minishell_t *init_struct(void)
{
    minishell_t *shell = malloc(sizeof(minishell_t));

    if (shell == NULL)
        return (NULL);
    shell->status = 0;
    shell->env = NULL;
    shell->old_cd = NULL;
    shell->user_input = NULL;
    shell->args = NULL;
    shell->is_piped = -1;
    shell->command_index = -1;
    shell->pipefd[0] = 0;
    shell->pipefd[1] = 0;
    return (shell);
}

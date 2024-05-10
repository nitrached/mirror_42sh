/*
** EPITECH PROJECT, 2024
** minishell1_2
** File description:
** init_struct
*/
#include <stddef.h>
#include <stdlib.h>
#include "minishell.h"
#include <stdio.h>

static void init_pipe_minishell(minishell_t *shell)
{
    shell->is_piped = -1;
    shell->command_index = -1;
    shell->last_stdout = -1;
    shell->pid = NULL;
    shell->pipefd[0] = 0;
    shell->pipefd[1] = 0;
}

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
    init_pipe_minishell(shell);
    shell->tab_history = malloc(sizeof(char *) * 1);
    shell->tab_history[0] = NULL;
    shell->tab_history_time = malloc(sizeof(char *) * 1);
    shell->tab_history_time[0] = NULL;
    shell->history_nav = -1;
    shell->alias = init_alias();
    return (shell);
}

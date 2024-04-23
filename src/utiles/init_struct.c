/*
** EPITECH PROJECT, 2024
** minishell1_2
** File description:
** init_struct
*/
#include <stddef.h>
#include <stdlib.h>
#include "../include/minishell.h"

static indexes_t *init_indexes(void)
{
    indexes_t *indexes = malloc(sizeof(indexes_t));

    if (indexes == NULL)
        return NULL;
    indexes->command_index = -1;
    indexes->cpt = 0;
    return (indexes);
}

static inputs_t *init_inputs(void)
{
    inputs_t *inputs = malloc(sizeof(inputs_t));

    if (inputs == NULL)
        return NULL;
    inputs->line = NULL;
    inputs->semicolon = NULL;
    inputs->exec = NULL;
    return (inputs);
}

static pipes_t *init_pipes(void)
{
    pipes_t *pipes = malloc(sizeof(pipes_t));

    if (pipes == NULL)
        return NULL;
    pipes->is_piped = -1;
    pipes->pid = 0;
    pipes->pipefd[0] = 0;
    pipes->pipefd[1] = 0;
    return (pipes);
}

static redirect_t *init_redirect(void)
{
    redirect_t *redirect = malloc(sizeof(redirect_t));

    if (redirect == NULL)
        return NULL;
    redirect->stdin_savior = 0;
    redirect->stdout_savior = 1;
    redirect->first_read = 1;
    redirect->last_write = 0;
    redirect->is_redirect = false;
    return (redirect);
}

static variables_t *init_variables(char **env)
{
    variables_t *variables = malloc(sizeof(variables_t));

    if (variables == NULL)
        return NULL;
    variables->env = my_tabdup(env);
    variables->old_cd = NULL;
    return (variables);
}

int check_return_value(minishell_t *shell)
{
    if (shell->indexes == NULL)
        return 0;
    if (shell->inputs == NULL)
        return 0;
    if (shell->pipes == NULL)
        return 0;
    if (shell->redirect == NULL)
        return 0;
    if (shell->variables == NULL)
        return 0;
    return 1;
}

minishell_t *init_struct(char **env)
{
    minishell_t *shell = malloc(sizeof(minishell_t));

    if (shell == NULL)
        return (NULL);
    shell->indexes = init_indexes();
    shell->inputs = init_inputs();
    shell->pipes = init_pipes();
    shell->redirect = init_redirect();
    shell->variables = init_variables(env);
    shell->status = 0;
    if (!check_return_value(shell))
        return NULL;
    return (shell);
}

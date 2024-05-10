/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** handle_pipe
*/
#include "my.h"
#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static
void set_struct_piped(minishell_t *minishell, char **args)
{
    int j = 0;

    INDEX = 0;
    minishell->stdin_savior = dup(STDIN_FILENO);
    minishell->stdout_savior = dup(STDOUT_FILENO);
    minishell->cpt = 0;
    minishell->last_stdout = -1;
    minishell->final_write = 1;
    minishell->is_piped = 1;
    minishell->pipe_status = 0;
    for (j = 0; args[j] != NULL; j++);
    minishell->cpt = j;
    minishell->pid = malloc(sizeof(int) * minishell->cpt);
    for (j = 0; args[j] != NULL; j++)
        minishell->pid[j] = -1;
}

static
void check_waitpid(minishell_t *minishell, int wait_status)
{
    for (int p = 0; p < minishell->cpt; p++) {
        waitpid(minishell->pid[p], &wait_status, 0);
        minishell->status = handle_signal(wait_status);
        P_STATUS = STATUS == 0 ? P_STATUS : STATUS;
    }
    dup2(minishell->stdin_savior, STDIN_FILENO);
    dup2(minishell->stdout_savior, STDOUT_FILENO);
    minishell->status = minishell->pipe_status;
}

static
void ambigious(minishell_t *minishell)
{
    my_putstr_fd("Ambiguous intput redirect.\n", 2);
    minishell->status = 1;
}

static void handle_pipe(minishell_t *minishell, char *command_line)
{
    char **args = my_str_to_wordarray(command_line, "|><");
    int wait_status = 0;

    set_struct_piped(minishell, args);
    if (pipe_error(args, command_line, minishell) == 84)
        return;
    if (!find_redirection(command_line, minishell))
        return ambigious(minishell);
    if (minishell->final_write != 1)
        args[get_last_line_tab(args)] = NULL;
    for (; args[INDEX] != NULL; INDEX++) {
        USER_INPUT = my_str_to_wordarray(args[INDEX], " \t><");
        minishell->args = args;
        command_handler(minishell);
        P_STATUS = STATUS == 0 ? P_STATUS : STATUS;
        if (P_STATUS != 0)
            break;
    }
    return check_waitpid(minishell, wait_status);
}

static int handle_no_pipe(minishell_t *minishell, char ***args, int i)
{
    USER_INPUT = my_str_to_wordarray((*args)[i], " \t<>");
    minishell->stdin_savior = dup(STDIN_FILENO);
    minishell->stdout_savior = dup(STDOUT_FILENO);
    find_redirection((*args)[i], minishell);
    if (minishell->final_write != 1 || minishell->first_read != 0)
        USER_INPUT[get_last_line_tab(USER_INPUT)] = NULL;
    minishell->is_piped = 0;
    command_handler(minishell);
    dup2(minishell->stdin_savior, STDIN_FILENO);
    dup2(minishell->stdout_savior, STDOUT_FILENO);
    return 1;
}

void cond(char ***args, int i, minishell_t *minishell)
{
    if (is_piped((*args)[i]))
        handle_pipe(minishell, (*args)[i]);
    else {
        handle_no_pipe(minishell, args, i);
    }
}

void handle_conditions(minishell_t *minishell, char ***args, int i)
{
    char *tab_delim[] = {"&&", "||", NULL};
    char **tab = my_str_to_wordarray_multi_delim((*args)[i], tab_delim);
    bool continue_cond = true;
    int tab_len = 0;

    if (tab == NULL)
        return cond(args, i, minishell);
    for (; tab[tab_len] != NULL; tab_len++);
    for (int j = 0; j < tab_len; j += 2) {
        if (j == 0 || (strstr(tab[j - 1], "||") && !continue_cond)
        || (strstr(tab[j - 1], "&&") && continue_cond)) {
            cond(&tab, j, minishell);
        }
        if (minishell->status != 0)
            continue_cond = false;
    }
}

int parse_pipe(minishell_t *minishell, char **line, char ***args)
{
    if (isatty(STDIN_FILENO))
        my_putstr("$> ");
    *line = parse_input(minishell);
    if (*line == NULL)
        return 84;
    else
        add_command_to_tab(*line, minishell);
    *args = my_str_to_wordarray(*line, ";");
    for (int i = 0; (*args)[i] != NULL; i++) {
        handle_conditions(minishell, args, i);
    }
    return 1;
}

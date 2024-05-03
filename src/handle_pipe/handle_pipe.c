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

void set_struct_piped(minishell_t *minishell, char **args)
{
    int j = 0;

    INDEX = 0;
    minishell->cpt = 0;
    minishell->last_stdout = -1;
    minishell->final_write = 1;
    minishell->is_piped = 1;
    for (j = 0; args[j] != NULL; j++);
    minishell->cpt = j;
    minishell->pid = malloc(sizeof(int) * minishell->cpt - 1);
    for (j = 0; args[j] != NULL; j++)
        minishell->pid[j] = -1;
}

static void handle_pipe(minishell_t *minishell, char *command_line)
{
    char **args = my_str_to_wordarray(command_line, "|><");
    int wait_status;

    set_struct_piped(minishell, args);
    if (pipe_error(args, command_line, minishell) == 84)
        return;
    if (!find_redirection(command_line, minishell)) {
        my_putstr_fd("Ambiguous intput redirect.\n", 2);
        minishell->status = 1;
        return;
    }
    if (minishell->final_write != 1)
        args[get_last_line_tab(args)] = NULL;
    for (; args[INDEX] != NULL; INDEX++) {
        USER_INPUT = my_str_to_wordarray(args[INDEX], " \t><");
        minishell->args = args;
        command_handler(minishell);
    }
    waitpid(minishell->pid[minishell->cpt - 1], &wait_status, 0);
    minishell->status = handle_signal(wait_status);
}

/* char **str_word_array_word_delim(char *string, char **tab_delim)
{

}

before_handle_no_pipe(minishell_t *minishell, char ***args, int i)
{
    char **tab_delim = {"&&", "||", NULL};
    char **tab = str_word_array_word_delim((*args)[i], tab_delim);

    for (int j = 0; tab[j] != NULL; j++) {
        handle_no_pipe(minishell, &tab, j);
    }
} */
static int handle_no_pipe(minishell_t *minishell, char ***args, int i)
{
    USER_INPUT = my_str_to_wordarray((*args)[i], " \t<>");
    find_redirection((*args)[i], minishell);
    if (minishell->final_write != 1 || minishell->first_read != 0)
        USER_INPUT[get_last_line_tab(USER_INPUT)] = NULL;
    minishell->is_piped = 0;
    command_handler(minishell);
    return 1;
}

int parse_pipe(minishell_t *minishell, char **line, char ***args)
{
    if (isatty(STDIN_FILENO))
        my_putstr("$> ");
    *line = get_line();
    if (*line == NULL)
        return 84;
    *args = my_str_to_wordarray(*line, ";");
    for (int i = 0; (*args)[i] != NULL; i++) {
        if (is_piped((*args)[i]))
            handle_pipe(minishell, (*args)[i]);
        else {
            handle_no_pipe(minishell, args, i);
        }
    }
    return 1;
}

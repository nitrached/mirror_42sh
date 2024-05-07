/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** handle_error_tab
*/
#include "my.h"
#include "minishell.h"
#include <errno.h>
#include <stddef.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

void handle_error_tab(int i, int num_sig)
{
    if (ERROR_MESSAGE[i].macro == num_sig)
        my_putstr_fd(ERROR_MESSAGE[i].error_message, 2);
    return;
}

int handle_signal(int wait_status)
{
    int num_sig = 0;

    if (WIFEXITED(wait_status)) {
        return WEXITSTATUS(wait_status);
    }
    if (WIFSIGNALED(wait_status)) {
        num_sig = WTERMSIG(wait_status);
        for (int i = 0; ERROR_MESSAGE[i].error_message != NULL; i++)
            handle_error_tab(i, num_sig);
        if (WCOREDUMP(wait_status))
            my_putstr_fd(" (core dumped)", 2);
        my_printf("\n");
    }
    return (wait_status);
}

int handle_error(char *command)
{
    if (errno == EACCES) {
        my_putstr_fd(command, 2);
        my_putstr_fd(": Permission denied.\n", 2);
    }
    if (errno == ENOEXEC) {
        my_putstr_fd(command, 2);
        my_putstr_fd(": Exec format error. Wrong Architecture.\n", 2);
    }
    return 0;
}

int pipe_error(char **args, char *command, minishell_t *minishell)
{
    int j = 0;
    int a = 0;
    int b = 0;

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '|')
            b = 1;
        if (b == 1 && (command[i] != '\n' || command[i] != ' '))
            a = 1;
    }
    for (; args[j] != NULL; j++);
    if (j < 2 || a == 0 || my_strcmp(command, " | ") == 0) {
        my_putstr_fd("Invalid null command.\n", 2);
        minishell->status = 1;
        return 84;
    }
    return 1;
}

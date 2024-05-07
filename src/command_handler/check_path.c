/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** check_path
*/
#include <stddef.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"
#include "my.h"
#include <stdio.h>

static int execute_command(char *full_path, minishell_t *minishell)
{
    pid_t pid;
    int wait_status;
    int status = 0;

    pid = fork();
    if (pid == 0) {
        dup2(minishell->final_write, STDOUT_FILENO);
        status = execve(full_path, USER_INPUT, ENV);
        if (status == -1)
            handle_error(USER_INPUT[0]);
        exit(0);
    } else {
        waitpid(pid, &wait_status, 0);
        minishell->status = handle_signal(wait_status);
        if (minishell->last_stdout)
            dup2(minishell->last_stdout, STDIN_FILENO);
    return 1;
    }
    return status;
}

static int exec_child_pipe(minishell_t *minishell, char *full_path)
{
    if (minishell->command_index != 0)
        dup2(minishell->last_stdout, STDIN_FILENO);
    if (minishell->args[minishell->command_index + 1] != NULL) {
        dup2(minishell->pipefd[1], STDOUT_FILENO);
        close(minishell->pipefd[0]);
    }
    if (minishell->args[minishell->command_index + 1] == NULL) {
        dup2(minishell->final_write, STDOUT_FILENO);
    }
    return execve(full_path, USER_INPUT, ENV);
}

void check_pid_tab(minishell_t *minishell, pid_t pid)
{
    for (int i = 0; i < minishell->cpt; i++) {
        if (minishell->pid[minishell->command_index] == -1) {
            minishell->pid[minishell->command_index] = pid;
            return;
        }
    }
}

static int exec_piped_command(minishell_t *minishell, char *full_path,
    pid_t pid, int status)
{
    if (pid == 0) {
        status = exec_child_pipe(minishell, full_path);
        if (status == -1)
            handle_error(USER_INPUT[0]);
    } else {
        close(minishell->pipefd[1]);
        minishell->last_stdout = minishell->pipefd[0];
        check_pid_tab(minishell, pid);
    }
    return status;
}

static int prepare_command_piped(char *full_path, minishell_t *minishell)
{
    pid_t pid;
    int status = 0;

    if (pipe(minishell->pipefd) == -1) {
        perror("pipe");
        return 84;
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 84;
    }
    status = exec_piped_command(minishell, full_path, pid, status);
    return status;
}

static char *check_acces(char *full_path, minishell_t *minishell, int *status)
{
    if (access(full_path, F_OK) == 0) {
        if (!minishell->is_piped)
            *status = execute_command(full_path, minishell);
        if (minishell->is_piped)
            *status = prepare_command_piped(full_path, minishell);
        return full_path;
    }
    return NULL;
}

int setup_command(char **tab_path, minishell_t *minishell)
{
    char *full_path = NULL;
    int status = 84;

    for (int j = 0; tab_path[j] != NULL; j++) {
        full_path = malloc(my_strlen(tab_path[j]) + 1
            + my_strlen(USER_INPUT[0]) + 1);
        my_strcpy(full_path, tab_path[j]);
        if (tab_path[j][my_strlen(tab_path[j]) - 1] != '/')
            my_strcat(full_path, "/");
        my_strcat(full_path, USER_INPUT[0]);
        if (check_acces(full_path, minishell, &status) != NULL)
            break;
    }
    return status;
}

int check_path(minishell_t *minishell)
{
    char **tab_path = NULL;
    int tmp = 84;

    if (access(USER_INPUT[0], F_OK) == 0)
        return execute_command(USER_INPUT[0], minishell);
    for (int i = 0; ENV[i] != NULL; i++) {
        if (!my_strncmp(ENV[i], "PATH=", 5)) {
            tab_path = my_str_to_wordarray(ENV[i] + 5, ":");
            tmp = setup_command(tab_path, minishell);
        }
    }
    if (tmp == 84) {
        my_printf("%s: Command not found.\n", USER_INPUT[0]);
        minishell->status = 1;
    }
    return tmp;
}

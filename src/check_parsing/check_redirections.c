/*
** EPITECH PROJECT, 2024
** B-PSU-200-REN-2-1-42sh-elie.stroun
** File description:
** redirection
*/

#include "../include/my.h"
#include "../include/minishell.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static reduce_line(char ***tab, int *len, int line)
{
    tab_delline(tab, *len, line);
    (*len)--;
}

static void read_fd(minishell_t *minishell)
{
    int pipefd[2];
    struct stat st;
    char *buffer = NULL;

        fstat(REDIRECT->first_read, &st);
        buffer = malloc(sizeof(char) * st.st_size + 1);
        read(REDIRECT->first_read, buffer, st.st_size);
        pipe(pipefd);
        REDIRECT->stdin_savior = dup(STDIN_FILENO);
        dup2(pipefd[0], STDIN_FILENO);
        write(pipefd[1], buffer, st.st_size);
        close(pipefd[1]);
}

int redirect_right(minishell_t *minishell, int i, int *len)
{
    if (!strcmp(INPUTS->exec[i], ">") && INPUTS->exec[i + 1] != NULL) {
        if (REDIRECT->is_redirect)
            return my_putstr_fd("error too much redirections\n", 2);
        REDIRECT->is_redirect = true;
        reduce_line(&INPUTS->exec, len, i);
        /* for (int j = 0; INPUTS->exec[j] != NULL; j++)
            printf("%s\n", INPUTS->exec[j]);
        return 0; */
        if (!strcmp(INPUTS->exec[i], ">") && INPUTS->exec[i + 1] != NULL) {
            reduce_line(&INPUTS->exec, len, i);
            REDIRECT->last_write = open(INPUTS->exec[i],
            O_WRONLY | O_CREAT | O_APPEND, 0600);
            reduce_line(&INPUTS->exec, len, i);
            return 1;
        }
        REDIRECT->last_write = open(INPUTS->exec[i],
        O_WRONLY | O_CREAT | O_TRUNC, 0600);
        reduce_line(&INPUTS->exec, len, i);
        return 1;
    }
    return 1;
}

int redirect_left(minishell_t *minishell, int i, int *len)
{
    if (!strcmp(INPUTS->exec[i], "<") && INPUTS->exec[i] != NULL) {
        if (REDIRECT->is_redirect)
            return my_putstr_fd("error too much redirections\n", 2);
        REDIRECT->is_redirect = true;
        reduce_line(&INPUTS->exec, len, i);
        if (!strcmp(INPUTS->exec[i], "<") && INPUTS->exec[i + 1] != NULL) {
        reduce_line(&INPUTS->exec, len, i);
        REDIRECT->first_read = open(INPUTS->exec[i], O_RDONLY);
        read_fd(minishell);
        reduce_line(&INPUTS->exec, len, i);
        return 1;
        }
        REDIRECT->first_read = open(INPUTS->exec[i], O_RDONLY);
        read_fd(minishell);
        reduce_line(&INPUTS->exec, len, i);
        return 1;
    }
    return 1;
}

int check_redirections(minishell_t *minishell, int i, int *len)
{
    if (redirect_right(minishell, i, len) != 1)
        return 0;
    if (redirect_left(minishell, i, len) != 1)
        return 0;
    return 1;
}

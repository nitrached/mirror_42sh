/*
** EPITECH PROJECT, 2024
** minishell_2
** File description:
** handle_right_redirection
*/
#include "my.h"
#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int open_redirection_right(char *command_line, int i)
{
    int fd;
    char **file_name_tab = NULL;

    if (command_line[i] == '>') {
        if (command_line[i + 1] == '>') {
            file_name_tab = my_str_to_wordarray(command_line + i, " \t>");
            fd = open(file_name_tab[0], O_WRONLY | O_CREAT | O_APPEND, 0600);
            return fd;
        }
        file_name_tab = my_str_to_wordarray(command_line + i, " \t>");
        fd = open(file_name_tab[0], O_WRONLY | O_CREAT | O_TRUNC, 0600);
        return fd;
    }
    return 1;
}

static void read_fd(int fd, minishell_t *minishell)
{
    int pipefd[2];
    struct stat st;
    char *buffer = NULL;

    if (minishell->is_piped != 1) {
        fstat(fd, &st);
        buffer = malloc(sizeof(char) * st.st_size + 1);
        read(fd, buffer, st.st_size);
        pipe(pipefd);
        minishell->last_stdout = dup(STDIN_FILENO);
        dup2(pipefd[0], STDIN_FILENO);
        write(pipefd[1], buffer, st.st_size);
        close(pipefd[1]);
    }
}

static int open_redirection_left(char *command_line, int i,
    minishell_t *minishell)
{
    int fd;
    char **file_name_tab = NULL;

    if (command_line[i] == '<') {
        if (command_line[i + 1] == '<') {
            file_name_tab = my_str_to_wordarray(command_line + i, " \t<");
            fd = open(file_name_tab[0], O_RDONLY);
            read_fd(fd, minishell);
            return fd;
        }
        file_name_tab = my_str_to_wordarray(command_line + i, " \t<");
        fd = open(file_name_tab[0], O_RDONLY);
        read_fd(fd, minishell);
        return fd;
    }
    return 0;
}

int find_redirection(char *command_line, minishell_t *minishell)
{
    for (int i = 0; command_line[i] != '\0'; i++) {
        minishell->final_write = open_redirection_right(command_line, i);
        minishell->first_read =
            open_redirection_left(command_line, i, minishell);
        if (minishell->final_write != 1 || minishell->first_read != 0)
            break;
    }
    if (minishell->first_read != 0)
        return 0;
    return 1;
}

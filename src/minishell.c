/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell
*/
#include "my.h"
#include "minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int my_minishell(char **env)
{
    char *line;
    char **args = NULL;
    minishell_t *minishell = NULL;

    minishell = init_struct();
    ENV = my_tabdup(env);
    while (1) {
        if (parse_pipe(minishell, &line, &args) == 84) {
            break;
        }
    }
    free(line);
    return (minishell->status);
}

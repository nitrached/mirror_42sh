/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell
*/
#include "../include/my.h"
#include "../include/minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void display_prompt(void)
{
    if (isatty(STDIN_FILENO))
        my_putstr("$> ");
}

int my_minishell(char **env)
{
    minishell_t *minishell = NULL;
    while (1) {
        minishell = init_struct(env);
        display_prompt();
        read_command(minishell);
        for (int i = 0; INPUTS->semicolon[i] != NULL; i++) {
            parse_pipe(minishell, i);
        }
    }
    return (minishell->status);
}

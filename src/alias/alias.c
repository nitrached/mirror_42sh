/*
** EPITECH PROJECT, 2024
** alias
** File description:
** alias
*/

#include "minishell.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static alias_t *init_line_alias(char *name, char **command)
{
    alias_t *line = malloc(sizeof(alias_t));

    line->command = my_tabdup(command);
    line->name = my_strdup(name);
    return line;
}

alias_t **add_first_alias(alias_t **alias, char **arg)
{
    int i = 3;
    char **command = malloc(sizeof(char *) * 3);

    command[0] = my_strdup(arg[2]);
    command[1] = NULL;
    while (arg[i] != NULL) {
        command = realloc(command, sizeof(char *) * (i));
        command[i - 2] = my_strdup(arg[i]);
        command[i - 1] = NULL;
        i++;
    }
    alias[0] = malloc(sizeof(alias_t));
    alias[0]->command = command;
    alias[0]->name = my_strdup(arg[1]);
    alias[1] = NULL;
    return alias;
}

static alias_t **add_alias(alias_t **alias, char **arg)
{
    int j = 3;
    int i = 0;
    char **command = malloc(sizeof(char *) * 3);
    alias_t *line = NULL;

    command[0] = my_strdup(arg[2]);
    command[1] = NULL;
    while (arg[j] != NULL) {
        command = realloc(command, sizeof(char *) * (j));
        command[j - 2] = my_strdup(arg[j]);
        command[j - 1] = NULL;
        j++;
    }
    for (; alias[i] != NULL; i++);
    line = init_line_alias(arg[1], command);
    alias = my_realloc(alias, line);
    alias[i + 1] = NULL;
    return alias;
}

alias_t **alias_cmd(char **arg, alias_t **alias)
{
    if (!alias[0])
        alias = add_first_alias(alias, arg);
    else
        alias = add_alias(alias, arg);
    return alias;
}

void free_alias(alias_t **alias)
{
    for (int i = 0; alias[i] != NULL; i++) {
        for (int j = 0; alias[i]->command[j] != NULL; j++)
            free(alias[i]->command[j]);
        free(alias[i]->name);
        free(alias[i]);
    }
    free(alias);
}

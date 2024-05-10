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

static alias_t *init_line_alias(char *name, char *command)
{
    alias_t *line = malloc(sizeof(alias_t));

    line->command = malloc(sizeof(char) * strlen(command));
    line->command = strcat(line->command, command);
    line->name = malloc(sizeof(char) * strlen(name));
    line->name = strcat(line->name, name);
    return line;
}

alias_t **add_first_alias(alias_t **alias, char **arg)
{
    alias[0] = malloc(sizeof(alias_t));
    alias[0]->command = my_strdup(arg[2]);
    alias[0]->name = my_strdup(arg[1]);
    alias[1] = NULL;
    return alias;
}

static alias_t **add_alias(alias_t **alias, char **arg)
{
    for (int i = 0; arg[i] != NULL; i++) {
        printf("arg = %s\n", arg[i]);
    }
    
    alias_t *line = init_line_alias(arg[1], arg[2]);
    int i;

    alias = my_realloc(alias, line);
    for (i = 0; alias[i] != NULL; i++);
    alias[i] = NULL;
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
        free(alias[i]->command);
        free(alias[i]->name);
        free(alias[i]);
    }
    free(alias);
}

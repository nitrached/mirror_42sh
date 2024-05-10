/*
** EPITECH PROJECT, 2023
** add_command_to_tab.c
** File description:
** PSU
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_command_to_tab(char *command, minishell_t *all)
{
    char **new_tab = NULL;
    int i = 0;

    for (; all->tab_history[i] != NULL; i++);
    new_tab = malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (all->tab_history[i] != NULL) {
        new_tab[i] = malloc(sizeof(char) * (strlen(all->tab_history[i]) + 1));
        strcpy(new_tab[i], all->tab_history[i]);
        i++;
    }
    if ((i >= 1 && strcmp(new_tab[i - 1], command) == 0)
        || strcmp(command, "\n") == 0 || strcmp(command, "\0") == 0)
        return;
    new_tab[i] = malloc(sizeof(char) * (strlen(command) + 1));
    strcpy(new_tab[i], command);
    new_tab[i + 1] = NULL;
    free_tab(all->tab_history);
    all->tab_history = new_tab;
    add_time_to_tab(all);
}

/*
** EPITECH PROJECT, 2023
** display_history.c
** File description:
** PSU
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>

int display_history(minishell_t *all)
{
    int i = 0;

    while (all->tab_history[i] != NULL)
        i++;
    if (i >= 100)
        i = i - 100;
    else
        i = 0;
    while (all->tab_history[i] != NULL) {
        printf("\t%d\t%s\t%s\n", i + 1, all->tab_history_time[i],
            all->tab_history[i]);
        i++;
    }
    return 0;
}

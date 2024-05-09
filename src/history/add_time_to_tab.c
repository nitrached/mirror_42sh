/*
** EPITECH PROJECT, 2023
** add_time_to_tab.c
** File description:
** PSU
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

static
char *inttostr(int number)
{
    int temp = number;
    int count = (number == 0) ? 1 : 0;
    char *str = (char *)malloc((count + 1) * sizeof(char));

    while (temp != 0) {
        temp /= 10;
        count++;
    }
    for (int i = count - 1; i >= 0; i--) {
        str[i] = (number % 10) + '0';
        number /= 10;
    }
    str[count] = '\0';
    return str;
}

static
void complete_line(minishell_t *all, char **new_tab, int i)
{
    time_t current_time;
    struct tm *local_time;

    current_time = time(NULL);
    local_time = localtime(&current_time);
    new_tab[i] = malloc(sizeof(char) * (strlen(inttostr(local_time->tm_hour))
        + 4));
    new_tab[i][0] = '\0';
    strcat(new_tab[i], inttostr(local_time->tm_hour));
    strcat(new_tab[i], ":");
    strcat(new_tab[i], inttostr(local_time->tm_min));
    new_tab[i + 1] = NULL;
    all->tab_history_time = new_tab;
}

void add_time_to_tab(minishell_t *all)
{
    char **new_tab = NULL;
    int i = 0;

    while (all->tab_history_time[i] != NULL)
        i++;
    new_tab = malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (all->tab_history_time[i] != NULL) {
    new_tab[i] = malloc(sizeof(char) * (strlen(all->tab_history_time[i]) + 1));
        strcpy(new_tab[i], all->tab_history_time[i]);
        i++;
    }
    complete_line(all, new_tab, i);
}

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
#include <sys/time.h>

static void get_current_time(struct timeval *temps, long int *secondes,
    long int *minutes, long int *heures)
{
    gettimeofday(temps, NULL);
    *secondes = temps->tv_sec;
    *minutes = (*secondes / 60) % 60;
    *heures = (*secondes / 3600) % 24;
    *heures += 2;
}

static void format_time_to_tab(char **new_tab, int i,
    long int heures, long int minutes)
{
    char *str = calloc(4, sizeof(char));

    new_tab[i] = calloc(6, sizeof(char));
    sprintf(str, "%02ld", heures);
    strcat(new_tab[i], str);
    strcat(new_tab[i], ":");
    free(str);
    str = malloc(sizeof(char) * 4);
    sprintf(str, "%02ld", minutes);
    strcat(new_tab[i], str);
    new_tab[i + 1] = NULL;
    free(str);
}

void complete_line(minishell_t *all, char **new_tab, int i)
{
    struct timeval temps;
    long int secondes = 0;
    long int minutes = 0;
    long int heures = 0;

    get_current_time(&temps, &secondes, &minutes, &heures);
    format_time_to_tab(new_tab, i, heures, minutes);
    free_tab(all->tab_history_time);
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
    all->history_nav = i + 1;
    complete_line(all, new_tab, i);
}

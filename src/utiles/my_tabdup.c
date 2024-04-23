/*
** EPITECH PROJECT, 2024
** minishell1_2
** File description:
** my_tabdup
*/
#include <stddef.h>
#include <stdlib.h>
#include "my.h"
char **my_tabdup(char **tab)
{
    int i = 0;
    char **new_tab = NULL;
    int len = 0;

    if (tab == NULL)
        return (NULL);
    for (; tab[len] != NULL; len++);
    new_tab = malloc(sizeof(char *) * (len + 1));
    if (new_tab == NULL)
        return (NULL);
    while (i < len) {
        new_tab[i] = my_strdup(tab[i]);
        i++;
    }
    new_tab[i] = NULL;
    return (new_tab);
}

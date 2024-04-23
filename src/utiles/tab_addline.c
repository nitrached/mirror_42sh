/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** tab_addline
*/
#include <stdlib.h>
#include <sys/types.h>
#include "my.h"

char **my_tab_addline(char **tab, size_t size, char *str)
{
    char **new_tab = malloc(sizeof(char *) * (size + 2));

    if (new_tab == NULL)
        return (NULL);
    for (size_t i = 0; i < size; i++)
        new_tab[i] = my_strdup(tab[i]);
    new_tab[size] = my_strdup(str);
    new_tab[size + 1] = NULL;
    free(tab);
    return (new_tab);
}
